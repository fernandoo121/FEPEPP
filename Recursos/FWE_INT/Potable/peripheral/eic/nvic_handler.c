/*
 * nvic_handler.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"


/*
 * NVIC Handler
 */
void EIC_Handler(void){
	
	EXTINT_RF_Handler();
	
	//EIC_Handler_link();
}