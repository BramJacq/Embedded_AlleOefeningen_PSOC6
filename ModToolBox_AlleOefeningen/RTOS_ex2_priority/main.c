#include "cybsp.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>


void HighTask(void *pvParameters);
void MedTask(void *pvParameters);
void LowTask(void *pvParameters);

int main(void)
{
	cybsp_init();
    __enable_irq();

   cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 115200);

    xTaskCreate(HighTask, "HighTask", 256, NULL, 1, NULL);
    xTaskCreate(MedTask,  "MedTask",  256, NULL, 2, NULL);
    xTaskCreate(LowTask,  "LowTask",  256, NULL, 3, NULL);

    vTaskStartScheduler();

    for (;;);
}


void HighTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        printf("hello from task1\r\n");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void MedTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        printf("hello from task2\r\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void LowTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        printf("hello from task3\r\n");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}