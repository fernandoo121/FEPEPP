/*
 * system.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "samd21_init.h"

#ifdef PCB_ULT
 #warning "Mapeo de pines para PCB-ULT-002-RevA"
#else
#error "Tipo de PCB no definida"
#endif /* PCB_ULT */

void samd21_init(){

	system_init_link(); //clock and memory settings

	GCLK2_startup(); // Generic Clock Generator 2 at 1.024 KHz
	
	// Interaction peripherals
	PORT_peripheral_init();		// Port controls I/O pins
	EIC_peripheral_init();		// External Interrupt Controller
	PTC_peripheral_init();		// Peripheral Touch Controller
	
	// Communication peripherals
	USB_peripheral_init();		// Universal Serial Bus
	SERCOMx_peripheral_init();	// Serial Communication Interface (USART, SPI, I2C)
	I2S_peripheral_init();		// Inter-IC Sound Controller
	
	// Time peripherals
	WDT_peripheral_init();		// Watchdog Timer
	RTC_peripheral_init();		// Real-Time Counter
	TCx_peripheral_init();		// Timer/Counter
	TCCx_peripheral_init();		// Timer/Counter for Control Applications
	
	// Conversion peripherals
	ADC_peripheral_init();		// Analog-to-Digital Converter
	AC_peripheral_init();		// Analog Comparators
	DAC_peripheral_init();		// Digital-to-Analog Converter
	
	// Internal communication peripherals
	EVSYS_peripheral_init();	// Event System
}

/*
 * NVIC Handler
 */
void Dummy_Handler_APP(){
	
	unsigned int cuenta = NOTHING;
	
	while(1){
		
		if(cuenta > 5){
 			serialUSB_print_link("\nDummy_Handler_ ::: FALLA CRITICA!!!!\n"
 				"\tPosible acceso a memoria no asignada, por desbordamiento de arreglo."
 				"\tProbar también formatear unidad flash.\n");
			
			cuenta = NOTHING;
		} else
			cuenta++;
			
		LED_WARNING_TOGGLE;
		LED_DONE_TOGGLE;
		LED_COM_TOGGLE;
		LED_GEO_TOGGLE;
		BUZZER_TOGGLE;
		DELAY_US(100000); //100ms
	}
}