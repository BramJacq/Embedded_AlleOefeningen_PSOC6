#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"
#include "GUI.h"
#include "mtb_st7789v.h"
#include "cy8ckit_028_tft_pins.h"

const mtb_st7789v_pins_t tft_pins =
{
    .db08 = CY8CKIT_028_TFT_PIN_DISPLAY_DB8,
    .db09 = CY8CKIT_028_TFT_PIN_DISPLAY_DB9,
    .db10 = CY8CKIT_028_TFT_PIN_DISPLAY_DB10,
    .db11 = CY8CKIT_028_TFT_PIN_DISPLAY_DB11,
    .db12 = CY8CKIT_028_TFT_PIN_DISPLAY_DB12,
    .db13 = CY8CKIT_028_TFT_PIN_DISPLAY_DB13,
    .db14 = CY8CKIT_028_TFT_PIN_DISPLAY_DB14,
    .db15 = CY8CKIT_028_TFT_PIN_DISPLAY_DB15,
    .nrd  = CY8CKIT_028_TFT_PIN_DISPLAY_NRD,
    .nwr  = CY8CKIT_028_TFT_PIN_DISPLAY_NWR,
    .dc   = CY8CKIT_028_TFT_PIN_DISPLAY_DC,
    .rst  = CY8CKIT_028_TFT_PIN_DISPLAY_RST
};

int main(void)
{

	cybsp_init();
    __enable_irq();

    mtb_st7789v_init8(&tft_pins);

    GUI_Init();
	GUI_SetFont(&GUI_Font32_ASCII);

    GUI_DispString("Hello world!");

	GUI_DispStringAt("Position 50,100", 50, 100);

	GUI_SetBkColor(GUI_RED);
	GUI_SetColor(GUI_BLACK);
	GUI_DispStringAt("Position 50,140", 50, 140);

	GUI_DispNextLine();
	GUI_DispString("NEXTLINE BITCH");
    for (;;)
    {

    }
}

/* [] END OF FILE */