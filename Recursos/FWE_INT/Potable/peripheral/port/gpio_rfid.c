/*
 * gpio_RFIDid.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"
  
/* PORT private definition */

#if defined(PCB_ULT)
// PIN_RFID_ (Pin P)
// #define PORT_RFID_	PORT_
#endif /* PCB_ULT*/

/*
 * PORT private functions
 */
 void PORT_GPIO_RFID_int(){
#if defined(PCB_ULT)
	  
	//// PIN_RFID_
	//PORT->Group[PIN_RFID_/32].DIRSET.reg												= PORT_RFID_;	// Data Direction: Output.
	//PORT->Group[PIN_RFID_/32].OUTSET.reg												= PORT_RFID_;	// Output High.
	//PORT->Group[PIN_RFID_/32].PINCFG[(PIN_RFID_ - ((PIN_RFID_/32)*32))].bit.INEN		= LOW;			// Read-Back Input Enable.
	//PORT->Group[PIN_RFID_/32].PINCFG[(PIN_RFID_ - ((PIN_RFID_/32)*32))].bit.PULLEN	= LOW;			// Pull Enable.
	//PORT->Group[PIN_RFID_/32].PINCFG[(PIN_RFID_ - ((PIN_RFID_/32)*32))].bit.PMUXEN	= LOW;			// Peripheral Multiplexer Enable (REG_OUT control).
//
	//// PIN_RFID_
	//PORT->Group[PIN_RFID_/32].DIRSET.reg												= PORT_RFID_;	// Data Direction: Output.
	//PORT->Group[PIN_RFID_/32].OUTSET.reg												= PORT_RFID_;	// Output High.
	//PORT->Group[PIN_RFID_/32].PINCFG[(PIN_RFID_ - ((PIN_RFID_/32)*32))].bit.INEN		= LOW;			// Read-Back Input Enable.
	//PORT->Group[PIN_RFID_/32].PINCFG[(PIN_RFID_ - ((PIN_RFID_/32)*32))].bit.PULLEN	= LOW;			// Pull Enable.
	//PORT->Group[PIN_RFID_/32].PINCFG[(PIN_RFID_ - ((PIN_RFID_/32)*32))].bit.PMUXEN	= LOW;			// Peripheral Multiplexer Enable (REG_OUT control).
#endif /* PCB_ULT*/
  }

/*
 * PORT public functions
 */
