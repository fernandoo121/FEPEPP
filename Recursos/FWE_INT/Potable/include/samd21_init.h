/*
 * samd21_init.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */ 

#ifndef SAMD21_INIT_H_
#define SAMD21_INIT_H_

/* SAMD21 PERIPHERAL_VECTOR */
// Interaction peripherals
#define PORT_PERIPHERAL_ENABLED		1	// Port controls I/O pins
#define EIC_PERIPHERAL_ENABLED		1	// External Interrupt Controller
#define EVSYS_PERIPHERAL_ENABLED	0	// Event System
#define PTC_PERIPHERAL_ENABLED		0	// Peripheral Touch Controller
// Communication peripherals
#define USB_PERIPHERAL_ENABLED		1	// Universal Serial Bus
#define SERCOMx_PERIPHERAL_ENABLED	1	// Serial Communication Interface (USART, SPI, I2C)
#define I2S_PERIPHERAL_ENABLED		0	// Inter-IC Sound Controller
// Time peripherals
#define WDT_PERIPHERAL_ENABLED		1	// Watchdog Timer
#define RTC_PERIPHERAL_ENABLED		1	// Real-Time Counter
#define TCx_PERIPHERAL_ENABLED		0	// Timer/Counter
#define TCCx_PERIPHERAL_ENABLED		0	// Timer/Counter for Control Applications
// Conversion peripherals
#define ADC_PERIPHERAL_ENABLED		0	// Analog-to-Digital Converter
#define AC_PERIPHERAL_ENABLED		0	// Analog Comparators
#define DAC_PERIPHERAL_ENABLED		0	// Digital-to-Analog Converter

/* Available setting for interrupt priority */
enum IRQn_priority{
	
	_highest______________	= 0, //0x00 (highest urgency)
	_highest_intermediate_	= 1, //0x40
	_lowest_intermediate__	= 2, //0x80
	_lowest_______________	= 3, //0xC0 (lowest urgency)
};

#ifdef __cplusplus
extern "C" {
#endif

	/* SAMD21 INITIALIZATION */
	void samd21_init();

	/* SAMD21 PERIPHERAL */
	void GCLK2_startup();
	//Interaction peripherals
	void EIC_peripheral_init();		// External Interrupt Controller
	void PORT_peripheral_init();	// Port controls I/O pins
	void EVSYS_peripheral_init();	// Event System
	void PTC_peripheral_init();		// Peripheral Touch Controller
	// Communication peripherals
	void USB_peripheral_init();		// Universal Serial Bus
	void SERCOMx_peripheral_init();	// Serial Communication Interface (USART, SPI, I2C)
	void I2S_peripheral_init();		// Inter-IC Sound Controller
	// Time peripherals
	void WDT_peripheral_init();		// Watchdog Timer
	void RTC_peripheral_init();		// Real-Time Counter
	void TCx_peripheral_init();		// Timer/Counter
	void TCCx_peripheral_init();	// Timer/Counter for Control Applications
	//Conversion peripherals
	void ADC_peripheral_init();		// Analog-to-Digital Converter
	void AC_peripheral_init();		// Analog Comparators
	void DAC_peripheral_init();		// Digital-to-Analog Converter
	
#ifdef __cplusplus
}
#endif

#endif /* SAMD21_INIT_H_ */