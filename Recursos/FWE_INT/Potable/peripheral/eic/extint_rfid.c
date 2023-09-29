/*
 * extint_rfid.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"
  
/* EIC private definition */

#if defined(PCB_ULT)
// PIN_RFID_ (Pin P)
// #define PORT_RFID_	PORT_
#endif /* PCB_ULT*/

/*
 * EIC private functions
 */
 void PORT_EXTINT_RFID_int(){
#if defined(PCB_ULT)
	// EIC EXTIN14 (Pin GPIO3 Módulo Radiofrecuencia)
	//PORT->Group[PIN_EXTIN_RFID/32].DIRCLR.reg													= PORT_EXTIN_RFID;	// Data Direction: input.
	//PORT->Group[PIN_EXTIN_RFID/32].PINCFG[(PIN_EXTIN_RFID - ((PIN_EXTIN_RFID/32)*32))].bit.INEN	= HIGH;				// Read-Back Input Enable.
	//PORT->Group[PIN_EXTIN_RFID/32].PINCFG[(PIN_EXTIN_RFID - ((PIN_EXTIN_RFID/32)*32))].bit.PULLEN	= LOW;				// Pull Enable.
	//PORT->Group[PIN_EXTIN_RFID/32].PINCFG[(PIN_EXTIN_RFID - ((PIN_EXTIN_RFID/32)*32))].bit.PMUXEN	= HIGH;				// Peripheral Multiplexer Enable (REG_OUT control).
	//PORT->Group[PIN_EXTIN_RFID/32].PMUX[(PIN_EXTIN_RFID - ((PIN_EXTIN_RFID/32)*32))/2].reg	   |= PMUX_EXTIN_RFID;	// Peripheral Multiplexing Selection
#endif /* PCB_ULT*/
 }

void EXTINT_RFID_int(){
#if defined(PCB_ULT)
 	//// EIC External Interrupt x Event Output Enable
 	//EIC->EVCTRL.bit.EXTINTE_RFID = LOW;
 	//
 	//// EIC External Interrupt Request
 	//EIC->INTENCLR.reg = INTENCLR_EXTIN_RFID;
 	//
 	//// EIC Input Sense Configuration
 	//EIC->CONFIG[CONFIG_EXTIN_RFID].bit.SENSE_EXTIN_RFID = EIC_CONFIG_SENSE3_RISE_Val;
 //
 	//// Filter Enable
 	//EIC->CONFIG[CONFIG_EXTIN_RFID].bit.FILTEN_EXTIN_RFID = LOW;
#endif /* PCB_ULT*/
}

void EXTINT_RFID_Handler(){

}

/*
 * EIC public functions
 */
