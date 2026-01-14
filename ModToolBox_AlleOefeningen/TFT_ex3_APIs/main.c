#include "cyhal.h"
#include "cybsp.h"
#include "cy8ckit_028_tft.h"
#include "GUI.h"
#include "DIALOG.h"  

int main(void)
{
	cybsp_init();

    __enable_irq();

    cy8ckit_028_tft_init(NULL, NULL, NULL, NULL);

    GUI_Init();
    GUI_Clear();

    GUI_DispStringAt("Hello world", 40, 100);

    GUI_SetFont(&GUI_Font16_ASCII); 
    GUI_SetColor(GUI_BLACK);    
    GUI_SetBkColor(GUI_RED);   
    GUI_DispStringAt("Opnieuw welkom", 40, 120);

    for (;;)
    {

    }
}