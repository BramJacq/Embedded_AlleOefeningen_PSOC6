#include "cybsp.h"
#include "cyhal.h"
#include "FreeRTOS.h"
#include "task.h"


void Task_LED_200ms(void *pvParameters);
void Task_LED_500ms(void *pvParameters);


int main(void)
{
    cybsp_init();
    __enable_irq();

    cyhal_gpio_init(CYBSP_USER_LED, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, CYBSP_LED_STATE_OFF);


    xTaskCreate(Task_LED_200ms, "LED_200", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(Task_LED_500ms, "LED_500", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();

    for (;;);
}


void Task_LED_200ms(void *pvParameters)
{
    (void)pvParameters;
    for(;;)
    {
        cyhal_gpio_toggle(CYBSP_USER_LED); 
        vTaskDelay(pdMS_TO_TICKS(200));    
    }
}

void Task_LED_500ms(void *pvParameters)
{
    (void)pvParameters;
    for(;;)
    {
        cyhal_gpio_toggle(CYBSP_USER_LED); 
        vTaskDelay(pdMS_TO_TICKS(500));    
    }
}