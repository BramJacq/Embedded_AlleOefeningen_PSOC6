#include "cy_pdl.h"
#include "cy_tcpwm.h"
#include "cy_tcpwm_counter.h"
#include "cybsp.h"
#include "cycfg_peripherals.h"
#include "cy_retarget_io.h"
#include "cycfg_pins.h"
#include "cyhal_gpio.h"
#include "cyhal_gpio_impl.h"
#include "cyhal_system_impl.h"
#include <stdio.h>

int main(void)
{
	
	_Bool input;
	uint32_t counter, capture;
	
    __enable_irq();
    cybsp_init();
	
	cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    cyhal_gpio_init(P0_3, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, false); 
    
    Cy_TCPWM_Counter_Init(counter_HW, counter_NUM, &counter_config);
    Cy_TCPWM_Counter_Enable(counter_HW, counter_NUM);
    Cy_TCPWM_TriggerStart_Single(counter_HW, counter_NUM);
    
    Cy_TCPWM_Counter_Init(timer_HW, timer_NUM, &timer_config);
    Cy_TCPWM_Counter_Enable(timer_HW, timer_NUM);
    Cy_TCPWM_TriggerStart_Single(timer_HW, timer_NUM);
     

    
    printf("Hello world!");

    for(;;)
    {
		counter = Cy_TCPWM_Counter_GetCounter(counter_HW, counter_NUM);
		capture= Cy_TCPWM_Counter_GetCapture(counter_HW, counter_NUM);
		printf("De counter is : %lu %lu\n\r ",counter,capture);
		cyhal_system_delay_ms(1000);
		if (counter > 100){
			cyhal_gpio_write(P0_3, false);
		}
		
		     
    }
}