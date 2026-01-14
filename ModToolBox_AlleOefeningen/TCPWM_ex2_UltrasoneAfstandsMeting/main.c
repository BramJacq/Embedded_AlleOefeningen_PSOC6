#include "cy_pdl.h"
#include "cy_tcpwm.h"
#include "cy_tcpwm_counter.h"
#include "cybsp.h"
#include "cycfg_peripherals.h"
#include "cy_retarget_io.h"
#include "cycfg_pins.h"
#include "cyhal_gpio.h"
#include "cyhal_system_impl.h"
#include <stdio.h>

int main(void)
{
    uint32_t captureRising = 0;
    uint32_t captureFalling = 0;
    uint32_t lastCapture = 0;
    float afstand_cm = 0.0f;
    bool firstEdge = true;

    __enable_irq();
    cybsp_init();

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, CY_RETARGET_IO_BAUDRATE);

    Cy_TCPWM_Counter_Init(trigger_HW, trigger_NUM, &trigger_config);
    Cy_TCPWM_Counter_Enable(trigger_HW, trigger_NUM);

    Cy_TCPWM_Counter_Init(counter_HW, counter_NUM, &counter_config);
    Cy_TCPWM_Counter_Enable(counter_HW, counter_NUM);
    Cy_TCPWM_TriggerStart_Single(counter_HW, counter_NUM);

    printf("Ultrasone afstandsmeting gestart\r\n");

    for (;;)
    {
        Cy_TCPWM_TriggerStart_Single(trigger_HW, trigger_NUM);

        firstEdge = true;
        captureRising = 0;
        captureFalling = 0;
        lastCapture = Cy_TCPWM_Counter_GetCounter(counter_HW, counter_NUM);

        while (captureFalling == 0)
        {
            uint32_t cap = Cy_TCPWM_Counter_GetCapture(counter_HW, counter_NUM);
            if (cap != lastCapture) 
            {
                if (firstEdge)
                {
                    captureRising = cap;
                    firstEdge = false;
                }
                else
                {
                    captureFalling = cap;
                }
                lastCapture = cap;
            }
        }

        uint32_t pulse_length = captureFalling - captureRising;
        afstand_cm = (pulse_length * 0.0343f) / 2.0f;

        printf("Afstand: %.2f cm\r\n", afstand_cm);


        if (afstand_cm < 20.0f) {
            cyhal_gpio_write(P0_3, true);
        } else {
            cyhal_gpio_write(P0_3, false);
        }

        cyhal_system_delay_ms(500);
    }
}