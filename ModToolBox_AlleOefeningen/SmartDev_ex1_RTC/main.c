#include "cyhal.h"
#include "cybsp.h"
#include "cy_retarget_io.h"
#include <stdio.h>
#include <time.h>

#define TM_YEAR_BASE (1900u)

cyhal_rtc_t my_rtc;
char buffer[80];
volatile bool print_time_request = false;

void button_isr(void *arg, cyhal_gpio_event_t event)
{
    print_time_request = true;
}

void print_current_time(void)
{
    struct tm now = {0};

    if (cyhal_rtc_read(&my_rtc, &now) == CY_RSLT_SUCCESS)
    {
        strftime(buffer, sizeof(buffer), "%c", &now);
        printf("Current time: %s\r\n", buffer);
    }
}

int main(void)
{
    cybsp_init();
    __enable_irq();

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 115200);

    printf("\r\n-------------- Application RTC basics started --------------\r\n");

    struct tm new_date_time =
    {
        .tm_sec   = 30,
        .tm_min   = 41,
        .tm_hour  = 12,
        .tm_mday  = 26,
        .tm_mon   = 10,
        .tm_year  = 2025 - TM_YEAR_BASE,
        .tm_wday  = 1,
        .tm_isdst = 0
    };

    cyhal_rtc_init(&my_rtc);
    cyhal_rtc_write(&my_rtc, &new_date_time);

    print_current_time();

    cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 1);

    cyhal_gpio_callback_data_t cb =
    {
        .callback = button_isr,
        .callback_arg = NULL
    };

    cyhal_gpio_register_callback(CYBSP_USER_BTN, &cb);
    cyhal_gpio_enable_event(CYBSP_USER_BTN, CYHAL_GPIO_IRQ_FALL, 3, true);


    int last_second = -1;

    for (;;)
    {
        struct tm now = {0};
        cyhal_rtc_read(&my_rtc, &now);

        if (now.tm_sec != last_second)
        {
            last_second = now.tm_sec;
            printf("Tick!\r\n");
        }

        if (print_time_request)
        {
            print_time_request = false;
            printf("Button pressed – ");
            print_current_time();
        }
    }
}