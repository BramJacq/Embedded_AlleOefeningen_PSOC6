#include "cyhal.h"
#include "cybsp.h"
#include "cy8ckit_028_tft.h"
#include "GUI.h"
#include "DIALOG.h" 

#include <stdio.h>

int main(void)
{
	cybsp_init();
    __enable_irq();

    cy8ckit_028_tft_init(NULL, NULL, NULL, NULL);

    GUI_Init();
    GUI_Clear();
    
    const char *base_text = "De bom gaat af in ";
    int x = 100;        
    int y = 120;        
    int timer_x = x + GUI_GetStringDistX(base_text); 

    GUI_DispStringAt(base_text, x, y);

    int counter = 9;

    for (;;)
    {
        char buf[2];
        snprintf(buf, sizeof(buf), "%d", counter);
        GUI_DispCharAt(buf[0], timer_x, y);  

        cyhal_system_delay_ms(1000); 

        counter--;
        if (counter < 0)
        {
            counter = 9; 
        }
    }
}