/*
 * gpio_indications.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "gateway_portable.h"
 
 
/* PORT private definition */



/*
 * PORT private functions
 */
void PORT_GPIO_indications_int(){

#if defined(PCB_ULT)
	// BUZZER
	PORT->Group[PIN_BUZZER/32].DIRSET.reg = PORT_BUZZER;			//Data Direction: output.
	// LED_DONE
	PORT->Group[PIN_LED_DONE/32].DIRSET.reg = PORT_LED_DONE;		//Data Direction: output.
	// LED_WARNING
	PORT->Group[PIN_LED_WARNING/32].DIRSET.reg = PORT_LED_WARNING;	//Data Direction: output.
	
	// LED_COM
	PORT->Group[PIN_LED_COM/32].DIRSET.reg = PORT_LED_COM;		//Data Direction: output.
	// LED_GEO
	PORT->Group[PIN_LED_GEO/32].DIRSET.reg = PORT_LED_GEO;	//Data Direction: output.	
#endif /* PCB_ULT */
}

/*
 * PORT public functions
 */
void pin_toggle_ms(unsigned int delay, unsigned char pin, unsigned int port, unsigned char indicacion){
	
	static unsigned int toggle_delay[NUM_INDICACIONES];
	
	if (toggle_delay[indicacion] == NOTHING)
	toggle_delay[indicacion] = CURRENT_TIME_MS;
	
	if (CURRENT_TIME_MS - toggle_delay[indicacion] > delay){
		PORT->Group[pin/32].OUTTGL.reg = port;
		toggle_delay[indicacion] = NOTHING;
	}
}