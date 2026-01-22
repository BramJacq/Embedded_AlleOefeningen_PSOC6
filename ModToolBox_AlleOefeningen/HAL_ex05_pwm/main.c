#include "cy_pdl.h"
#include "cyhal.h"
#include "cybsp.h"

int main(void)
{
    cyhal_pwm_t pwm_obj;

	cybsp_init() ;

    __enable_irq();
 // Initialize PWM on the supplied pin and assign a new clock
	cyhal_pwm_init(&pwm_obj, CYBSP_USER_LED, NULL);

	/* Start the PWM output */
	cyhal_pwm_start(&pwm_obj);

	while(true){
		for (int i = 100; i >= 0; i--){
			// i is de duty cycle en 10000 is de Frequentie
			cyhal_pwm_set_duty_cycle(&pwm_obj, i, 10000);
			cyhal_system_delay_ms(10);
		}
	}
}