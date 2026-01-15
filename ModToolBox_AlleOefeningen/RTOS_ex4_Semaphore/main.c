#include "cybsp.h"
#include "cyhal.h"
#include "cy_retarget_io.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"

void HighTask(void *pvParameters);
void MedTask(void *pvParameters);
void LowTask(void *pvParameters);

SemaphoreHandle_t xBinSem;

int main(void)
{
	cybsp_init();
    __enable_irq();

    cy_retarget_io_init(CYBSP_DEBUG_UART_TX, CYBSP_DEBUG_UART_RX, 115200);
    cyhal_gpio_init(CYBSP_USER_BTN, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_PULLUP, CYBSP_BTN_OFF);
    
    xBinSem = xSemaphoreCreateBinary();

    xSemaphoreGive(xBinSem);

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
        printf("Entered Task1\r\n");

        if (xSemaphoreTake(xBinSem, portMAX_DELAY) == pdTRUE)
        {
            printf("Semaphore acquired\r\n");

            printf("Leaving Task1 and released semaphore\r\n");
            xSemaphoreGive(xBinSem);
        }

        vTaskDelay(pdMS_TO_TICKS(2000)); 
    }
}

void MedTask(void *pvParameters)
{
(void)pvParameters;
    for (;;)
    {
        printf("Entered Task2\r\n");


        if (xSemaphoreTake(xBinSem, portMAX_DELAY) == pdTRUE)
        {
            printf("Semaphore acquired\r\n");


            while(cyhal_gpio_read(CYBSP_USER_BTN) != 0)
            {
                vTaskDelay(pdMS_TO_TICKS(50));
            }

            printf("Leaving Task2 and released semaphore\r\n");
            xSemaphoreGive(xBinSem);
        }

        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void LowTask(void *pvParameters)
{
    (void)pvParameters;
    for (;;)
    {
        printf("Entered Task3\r\n Leaving Task3\r\n");
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}