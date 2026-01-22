#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "cycfg_capsense.h"
#include "cycfg.h"

#define CAPSENSE_INTR_PRIORITY     7U
#define PWM_FREQ_HZ                100000U

bool scanComplete = false;
cyhal_pwm_t pwm_object;
cyhal_ezi2c_t ezi2c_object;
uint32_t gestureStatus = 0U;

cy_rslt_t initCapSense(void);
cy_rslt_t initTuner(void);
void capsense_isr(void);
void endScanCallback(cy_stc_active_scan_sns_t * ptrActiveScan);
void processTouch(uint32_t gestureStatus);

int main(void)
{
    cy_rslt_t result;

    result = cybsp_init();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    __enable_irq();

    result = cyhal_pwm_init(&pwm_object, CYBSP_USER_LED, NULL);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }
    result = cyhal_pwm_set_duty_cycle(&pwm_object, 50.0f, PWM_FREQ_HZ);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    cyhal_pwm_stop(&pwm_object);  


    result = initCapSense();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }

    result = initTuner();
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }


    Cy_CapSense_ScanAllWidgets(&cy_capsense_context);

    for (;;)
    {
        if (scanComplete)
        {

            Cy_CapSense_IncrementGestureTimestamp(&cy_capsense_context);
            Cy_CapSense_ProcessAllWidgets(&cy_capsense_context);

            gestureStatus = Cy_CapSense_DecodeWidgetGestures(CY_CAPSENSE_LINEARSLIDER0_WDGT_ID,&cy_capsense_context);

            processTouch(gestureStatus);

            Cy_CapSense_RunTuner(&cy_capsense_context);

            Cy_CapSense_ScanAllWidgets(&cy_capsense_context);
            scanComplete = false;
        }
    }
}


void processTouch(uint32_t gestureStatus)
{
    static bool ledState = false;

    if ((gestureStatus & CY_CAPSENSE_GESTURE_ONE_FNGR_SINGLE_CLICK_MASK)
        != CY_CAPSENSE_GESTURE_NO_GESTURE)
    {
        ledState = !ledState;
        if (ledState)
            cyhal_pwm_start(&pwm_object);
        else
            cyhal_pwm_stop(&pwm_object);
    }

    if ((gestureStatus & CY_CAPSENSE_GESTURE_ONE_FNGR_FLICK_MASK)
        != CY_CAPSENSE_GESTURE_NO_GESTURE)
    {
        uint32_t direction = (gestureStatus >> CY_CAPSENSE_GESTURE_DIRECTION_OFFSET) &
                             CY_CAPSENSE_GESTURE_DIRECTION_MASK_ONE_FLICK;

        switch (direction >> CY_CAPSENSE_GESTURE_DIRECTION_OFFSET_ONE_FLICK)
        {
            case CY_CAPSENSE_GESTURE_DIRECTION_LEFT:
                cyhal_pwm_start(&pwm_object);
                ledState = true;
                break;

            case CY_CAPSENSE_GESTURE_DIRECTION_RIGHT:
                cyhal_pwm_stop(&pwm_object);
                ledState = false;
                break;

            default:
                break;
        }
    }
}


void endScanCallback(cy_stc_active_scan_sns_t * ptrActiveScan)
{
    CY_UNUSED_PARAMETER(ptrActiveScan);
    scanComplete = true;
}


void capsense_isr(void)
{
    Cy_CapSense_InterruptHandler(CYBSP_CSD_HW, &cy_capsense_context);
}


cy_rslt_t initCapSense(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    cy_status status;

    const cy_stc_sysint_t capSense_intr_config =
    {
        .intrSrc = csd_interrupt_IRQn,
        .intrPriority = CAPSENSE_INTR_PRIORITY,
    };

    status = Cy_CapSense_Init(&cy_capsense_context);
    if (status != CY_RET_SUCCESS)
        return status;

    cyhal_system_set_isr(csd_interrupt_IRQn, csd_interrupt_IRQn,CAPSENSE_INTR_PRIORITY, &capsense_isr);
    NVIC_ClearPendingIRQ(capSense_intr_config.intrSrc);
    NVIC_EnableIRQ(capSense_intr_config.intrSrc);

    status = Cy_CapSense_RegisterCallback(CY_CAPSENSE_END_OF_SCAN_E,endScanCallback,&cy_capsense_context);
    
    if (status != CY_RET_SUCCESS)
        return status;

    status = Cy_CapSense_Enable(&cy_capsense_context);
    if (status != CY_RET_SUCCESS)
        return status;

    return result;
}


cy_rslt_t initTuner(void)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;

    cyhal_ezi2c_slave_cfg_t ezi2c_slave_config;
    cyhal_ezi2c_cfg_t ezi2c_config;

    ezi2c_slave_config.buf = (uint8 *)&cy_capsense_tuner;
    ezi2c_slave_config.buf_rw_boundary = sizeof(cy_capsense_tuner);
    ezi2c_slave_config.buf_size = sizeof(cy_capsense_tuner);
    ezi2c_slave_config.slave_address = 8U;

    ezi2c_config.data_rate = CYHAL_EZI2C_DATA_RATE_1MHZ;
    ezi2c_config.enable_wake_from_sleep = false;
    ezi2c_config.slave1_cfg = ezi2c_slave_config;
    ezi2c_config.sub_address_size = CYHAL_EZI2C_SUB_ADDR16_BITS;
    ezi2c_config.two_addresses = false;

    result = cyhal_ezi2c_init(&ezi2c_object,CYBSP_I2C_SDA,CYBSP_I2C_SCL,NULL,&ezi2c_config);

    return result;
}