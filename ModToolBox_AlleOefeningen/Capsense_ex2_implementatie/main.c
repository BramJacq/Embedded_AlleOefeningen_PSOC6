/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cycfg_capsense.h"
#include "cycfg.h"

/*******************************************************************************
* Macros
*******************************************************************************/
#define CAPSENSE_INTR_PRIORITY 7U
#define PWM_FREQ_HZ 100000

/*******************************************************************************
* Global Variables
*******************************************************************************/
bool scanComplete = false;
cyhal_pwm_t pwm_object;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/
cy_rslt_t initCapSense(void);
static void capsense_isr(void);
void endScanCallback(cy_stc_active_scan_sns_t * ptrActiveScan);
void processTouch(void);

/*******************************************************************************
* Function Name: main
********************************************************************************
* Summary:
*  System entrance point. This function performs
*  - initial setup of device
*  - initialize CapSense
*  - initialize tuner communication
*  - scan touch input continuously and update the LED accordingly.
*
* Return:
*  int
*
*******************************************************************************/
int main(void){
    cy_rslt_t result;

    /* Initialize the device and board peripherals */
    result = cybsp_init() ;
    if (result != CY_RSLT_SUCCESS){
        CY_ASSERT(0);
    }

    __enable_irq();

    // Initialize PWM
    result = cyhal_pwm_init(&pwm_object, CYBSP_USER_LED, NULL);
    if (result != CY_RSLT_SUCCESS){
		CY_ASSERT(0);
	}
    result = cyhal_pwm_set_duty_cycle(&pwm_object, 0, PWM_FREQ_HZ);
    if (result != CY_RSLT_SUCCESS){
		CY_ASSERT(0);
	}

    // Initialize capsense
    result = initCapSense();
    if (result != CY_RSLT_SUCCESS){
		CY_ASSERT(0);
	}

	// Start first scan
	Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

    for (;;){
    	// Wait for scan to complete
    	if(scanComplete == true){

    		// Process scan data
    		Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

    		// Update tuner
    		Cy_CapSense_RunTuner(&cy_capsense_context);

    		// Update LED according to any touches
    		processTouch();

    		// Start next scan
			Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
			scanComplete = false;
    	}
    }
}

/*******************************************************************************
* Function Name: initCapSense
********************************************************************************
* Summary:
* Initializes the CSD HW block for touch sensing
*
* Return:
*  cy_rslt_t
*
*******************************************************************************/
cy_rslt_t initCapSense(void){
	// Result to return
	cy_rslt_t result = CY_RSLT_SUCCESS;
	cy_status status = CY_RET_SUCCESS;

	const cy_stc_sysint_t CapSense_interrupt_config = {
			.intrSrc = CYBSP_CSD_IRQ,
			.intrPriority = CAPSENSE_INTR_PRIORITY
	};

	// Initialize CSD HW block
	status = Cy_CapSense_Init(&cy_capsense_context);
	if(status != CY_RET_SUCCESS){
		result = status;
		return result;
	}

	// Initialize CapSense interrupt
	Cy_SysInt_Init(&CapSense_interrupt_config, capsense_isr);
	NVIC_ClearPendingIRQ(CapSense_interrupt_config.intrSrc);
	NVIC_EnableIRQ(CapSense_interrupt_config.intrSrc);

	// Enable CapSense firmware modules
	status = Cy_CapSense_Enable(&cy_capsense_context);
	if(status != CY_RET_SUCCESS){
		result = status;
		return result;
	}

	// Initialize end of scan callback
	status = Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E, endScanCallback, &cy_capsense_context);
	if(status != CY_RET_SUCCESS){
		result = status;
		return result;
	}

	// Return success if nothing failed
	return result;
}

/*******************************************************************************
* Function Name: processTouch
********************************************************************************
* Summary:
* Check if CapSense buttons were pressed and update the LED state accordingly
*
* Return:
*  cy_rslt_t
*
*******************************************************************************/
void processTouch(void){
	// Vars to hold widget statuses
	uint32_t button0_status;
	uint32_t button1_status;
	cy_stc_capsense_touch_t *slider_touch_info;
	uint16_t slider_pos;
	uint8_t slider_touch_status;
	// Vars to hold previous widget statuses
	static uint32_t button0_status_prev;
	static uint32_t button1_status_prev;
	static uint16_t slider_pos_prev;

	// Get button0 status
	button0_status = Cy_CapSense_IsSensorActive(CY_CAPSENSE_BUTTON0_WDGT_ID, CY_CAPSENSE_BUTTON0_SNS0_ID, &cy_capsense_context);

	// Get button1 status
	button1_status = Cy_CapSense_IsSensorActive(CY_CAPSENSE_BUTTON1_WDGT_ID, CY_CAPSENSE_BUTTON1_SNS0_ID, &cy_capsense_context);

	/// Get slider status
	slider_touch_info = Cy_CapSense_GetTouchInfo(CY_CAPSENSE_LINEARSLIDER0_WDGT_ID, &cy_capsense_context);
	slider_touch_status = slider_touch_info->numPosition;
	slider_pos = slider_touch_info->ptrPosition->x;

	// If button0 is pressed turn the LED on
	if((button0_status != 0U) && (button0_status != button0_status_prev)){
		cyhal_pwm_start(&pwm_object);
	}

	// If button1 is pressed turn the LED off
	if((button1_status != 0U) && (button1_status != button1_status_prev)){
		cyhal_pwm_stop(&pwm_object);
	}

	// If slider position is updated, update LED brightness
	if((slider_touch_status != 0U) && (slider_pos != slider_pos_prev)){
		float dutyCycle = (1.0 - ((float)slider_pos / (float)cy_capsense_context.ptrWdConfig[CY_CAPSENSE_LINEARSLIDER0_WDGT_ID].xResolution)) * 100;
		cyhal_pwm_set_duty_cycle(&pwm_object, dutyCycle, PWM_FREQ_HZ);
	}

	/* Update previous touch status */
	button0_status_prev = button0_status;
	button1_status_prev = button1_status;
	slider_pos_prev = slider_pos;
}

/*******************************************************************************
* Interrupt Service Routines and Callbacks
*******************************************************************************/
static void capsense_isr(void){
	Cy_CapSense_InterruptHandler(CYBSP_CSD_HW, &cy_capsense_context);
}

void endScanCallback(cy_stc_active_scan_sns_t * ptrActiveScan){
	scanComplete = true;
}

/* [] END OF FILE */