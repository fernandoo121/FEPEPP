/*
 * extint_iot.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"
  
/* EIC private definition */

#if defined(PCB_ULT)
// PIN_IOT_ (Pin P)
// #define PORT_IOT_	PORT_
#endif /* PCB_ULT*/

/*
 * EIC private functions
 */
 void PORT_EXTINT_IOT_int(){
#if defined(PCB_ULT)
	// EIC EXTIN14 (Pin GPIO3 Módulo Radiofrecuencia)
	//PORT->Group[PIN_EXTIN_IOT/32].DIRCLR.reg													= PORT_EXTIN_IOT;	// Data Direction: input.
	//PORT->Group[PIN_EXTIN_IOT/32].PINCFG[(PIN_EXTIN_IOT - ((PIN_EXTIN_IOT/32)*32))].bit.INEN	= HIGH;				// Read-Back Input Enable.
	//PORT->Group[PIN_EXTIN_IOT/32].PINCFG[(PIN_EXTIN_IOT - ((PIN_EXTIN_IOT/32)*32))].bit.PULLEN	= LOW;				// Pull Enable.
	//PORT->Group[PIN_EXTIN_IOT/32].PINCFG[(PIN_EXTIN_IOT - ((PIN_EXTIN_IOT/32)*32))].bit.PMUXEN	= HIGH;				// Peripheral Multiplexer Enable (REG_OUT control).
	//PORT->Group[PIN_EXTIN_IOT/32].PMUX[(PIN_EXTIN_IOT - ((PIN_EXTIN_IOT/32)*32))/2].reg	   |= PMUX_EXTIN_IOT;	// Peripheral Multiplexing Selection
#endif /* PCB_ULT*/
 }

void EXTINT_IOT_int(){
#if defined(PCB_ULT)
 	//// EIC External Interrupt x Event Output Enable
 	//EIC->EVCTRL.bit.EXTINTE_IOT = LOW;
 	//
 	//// EIC External Interrupt Request
 	//EIC->INTENCLR.reg = INTENCLR_EXTIN_IOT;
 	//
 	//// EIC Input Sense Configuration
 	//EIC->CONFIG[CONFIG_EXTIN_IOT].bit.SENSE_EXTIN_IOT = EIC_CONFIG_SENSE3_RISE_Val;
 //
 	//// Filter Enable
 	//EIC->CONFIG[CONFIG_EXTIN_IOT].bit.FILTEN_EXTIN_IOT = LOW;
#endif /* PCB_ULT*/
}

void EXTINT_IOT_Handler(){

}

/*
 * EIC public functions
 */
