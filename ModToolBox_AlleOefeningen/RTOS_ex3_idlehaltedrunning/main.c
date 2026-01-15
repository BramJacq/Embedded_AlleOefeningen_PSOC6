#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void hello(void *pvParameters);
void counter(void *pvParameters);

TaskHandle_t helloHandle = NULL;

int main(void)
{
	cybsp_init();
    __enable_irq();

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 115200);

    xTaskCreate(hello, "Hello", 256, NULL, 1, &helloHandle);
    xTaskCreate(counter,  "counter",  256, NULL, 2, NULL);

    vTaskStartScheduler();

    for (;;);
}

void hello(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        printf("hello world\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void counter(void *pvParameters)
{
    (void)pvParameters;
    int count = 0;

    for (;;)
    {
        count++;
        printf("Counter = %d\r\n", count);

        if (count == 5)
        {
            vTaskSuspend(helloHandle);
            printf("Suspend Task1\r\n");
        }
        else if (count == 7)
        {
            vTaskResume(helloHandle);
            printf("Resumed Task1\r\n");
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); 
    }
}
