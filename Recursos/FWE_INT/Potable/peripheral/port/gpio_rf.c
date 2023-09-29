/*
 * gpio_rf.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"
  
/* PORT private definition */

#if defined(PCB_ULT)
// PIN_RF_ (Pin P)
// #define PORT_RF_	PORT_
#endif /* PCB_ULT*/

/*
 * PORT private functions
 */
 void PORT_GPIO_RF_int(){
#if defined(PCB_ULT)

	// PIN_RF_CSB (Pin CSB Módulo Radiofrecuencia)
	PORT->Group[PIN_RF_CSB/32].DIRSET.reg												= PORT_RF_CSB;	// Data Direction: Output.
	PORT->Group[PIN_RF_CSB/32].OUTSET.reg												= PORT_RF_CSB;	// Output High.
	PORT->Group[PIN_RF_CSB/32].PINCFG[(PIN_RF_CSB - ((PIN_RF_CSB/32)*32))].bit.INEN		= LOW;			// Read-Back Input Enable.
	PORT->Group[PIN_RF_CSB/32].PINCFG[(PIN_RF_CSB - ((PIN_RF_CSB/32)*32))].bit.PULLEN	= LOW;			// Pull Enable.
	PORT->Group[PIN_RF_CSB/32].PINCFG[(PIN_RF_CSB - ((PIN_RF_CSB/32)*32))].bit.PMUXEN	= LOW;			// Peripheral Multiplexer Enable (REG_OUT control).

	// PIN_RF_FCSB (Pin FCSB Módulo Radiofrecuencia)
	PORT->Group[PIN_RF_FCSB/32].DIRSET.reg													= PORT_RF_FCSB;	// Data Direction: Output.
	PORT->Group[PIN_RF_FCSB/32].OUTSET.reg													= PORT_RF_FCSB;	// Output High.
	PORT->Group[PIN_RF_FCSB/32].PINCFG[(PIN_RF_FCSB - ((PIN_RF_FCSB/32)*32))].bit.INEN		= LOW;			// Read-Back Input Enable.
	PORT->Group[PIN_RF_FCSB/32].PINCFG[(PIN_RF_FCSB - ((PIN_RF_FCSB/32)*32))].bit.PULLEN	= LOW;			// Pull Enable.
	PORT->Group[PIN_RF_FCSB/32].PINCFG[(PIN_RF_FCSB - ((PIN_RF_FCSB/32)*32))].bit.PMUXEN	= LOW;			// Peripheral Multiplexer Enable (REG_OUT control).
#endif /* PCB_ULT*/
  }

/*
 * PORT public functions
 */
