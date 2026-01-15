#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"

#define WDT_TIME_OUT_MS                     4000
#define ENABLE_BLOCKING_FUNCTION            0

cyhal_wdt_t wdt_obj;

int main(void)
{
    cybsp_init();

    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT,
                    CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX,
                        CY_RETARGET_IO_BAUDRATE);

    printf("\x1b[2J\x1b[;H");
    printf("******************"
           "HAL: Watchdog Timer"
           "****************** \r\n\n");

    if (CYHAL_SYSTEM_RESET_WDT ==
        (cyhal_system_get_reset_reason() & CYHAL_SYSTEM_RESET_WDT))
    {
        printf("Reset event from Watchdog Timer\r\n");

        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_ON);
        cyhal_system_delay_ms(100);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);
        cyhal_system_delay_ms(200);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_ON);
        cyhal_system_delay_ms(100);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);
    }
    else
    {
        printf("Reset event from Power-On or XRES\r\n");

        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_ON);
        cyhal_system_delay_ms(100);
        cyhal_gpio_write(CYBSP_USER_LED, CYBSP_LED_STATE_OFF);
        cyhal_system_delay_ms(100);
    }

    cyhal_system_clear_reset_reason();

    cy_rslt_t result = cyhal_wdt_init(&wdt_obj, WDT_TIME_OUT_MS);
    if (result != CY_RSLT_SUCCESS)
    {
        CY_ASSERT(0);
    }


    __enable_irq();

    for (;;)
    {
#if (ENABLE_BLOCKING_FUNCTION)

        while(1);

#else
        cyhal_wdt_kick(&wdt_obj);

        cyhal_system_delay_ms(1000);

        cyhal_gpio_toggle(CYBSP_USER_LED);
#endif
    }
}