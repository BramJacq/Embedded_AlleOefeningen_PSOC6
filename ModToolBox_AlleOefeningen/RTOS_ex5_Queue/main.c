#include "cybsp.h"
#include "cyhal.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <stdio.h>

QueueHandle_t pwmQueueHandle;
cyhal_pwm_t pwm_led;

void uartTask(void *arg);
void pwmTask(void *arg);


int main(void)
{
    cybsp_init();
    __enable_irq();

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 115200);

    cyhal_pwm_init(&pwm_led, CYBSP_USER_LED, NULL);
    cyhal_pwm_set_duty_cycle(&pwm_led, 50.0, 1.0);  
    cyhal_pwm_start(&pwm_led);

    pwmQueueHandle = xQueueCreate(5, sizeof(int));
    if (pwmQueueHandle == NULL)
    {
        printf("Queue creation failed!\r\n");
        CY_ASSERT(0);
    }


    xTaskCreate(uartTask, "uartTask", 256, NULL, 1, NULL);
    xTaskCreate(pwmTask, "pwmTask", 256, NULL, 2, NULL);

    vTaskStartScheduler();
    for(;;);
}


void pwmTask(void *arg)
{
    int msg = 0;

    for (;;)
    {
        if (xQueueReceive(pwmQueueHandle, &msg, portMAX_DELAY) == pdTRUE)
        {
            if (msg >= 1 && msg <= 10)
            {
                printf("PWM periode = %d sec\r\n", msg);
                cyhal_pwm_set_duty_cycle(&pwm_led, 50.0, 1.0 / msg);
            }
            else if (msg == -1)
            {
                printf("PWM STOP\r\n");
                cyhal_pwm_stop(&pwm_led);
            }
            else if (msg == -2)
            {
                printf("PWM START\r\n");
                cyhal_pwm_start(&pwm_led);
            }
        }
    }
}



void uartTask(void *arg)
{

    vTaskDelay(pdMS_TO_TICKS(200));

    uint8_t dummy;
    while (cyhal_uart_readable(&cy_retarget_io_uart_obj))
    {
        cyhal_uart_getc(&cy_retarget_io_uart_obj, &dummy, 1);
    }

    char c;
    int value;

    printf("Commando's:\r\n");
    printf("1-10 : set periode (sec)\r\n");
    printf("s    : start PWM\r\n");
    printf("x    : stop PWM\r\n");
    printf("?    : help\r\n");

    uint8_t nextChar;
    for (;;)
    {
        c = getchar();

        if (c >= '1' && c <= '9')
        {
            if (cyhal_uart_getc(&cy_retarget_io_uart_obj, &nextChar, 10) == CY_RSLT_SUCCESS &&
                c == '1' && nextChar == '0')
            {
                value = 10;
            }
            else
            {
                value = c - '0';
            }
            xQueueSend(pwmQueueHandle, &value, 0);
        }
        else if (c == 's')
        {
            value = -2;
            xQueueSend(pwmQueueHandle, &value, 0);
        }
        else if (c == 'x')
        {
            value = -1;
            xQueueSend(pwmQueueHandle, &value, 0);
        }
        else if (c == '?')
        {
            printf("Commando's:\r\n");
            printf("1-10 : set periode (s)\r\n");
            printf("s    : start PWM\r\n");
            printf("x    : stop PWM\r\n");
            printf("?    : help\r\n");
        }
    }
}