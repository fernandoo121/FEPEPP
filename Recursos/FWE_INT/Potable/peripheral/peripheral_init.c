/*
 * peripheral_init.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "samd21_init.h"
 
void USB_peripheral_init(){
#if USB_PERIPHERAL_ENABLED == 0
	//// Clock USB disabled
	PM->AHBMASK.bit.USB_  = LOW;
	PM->APBBMASK.bit.USB_ = LOW;
#else
	usb_start_link();
#endif /*USB_PERIPHERAL_ENABLED*/
}

void EIC_peripheral_init(){
#if EIC_PERIPHERAL_ENABLED == 0
	//// Clock EIC disabled
	PM->APBAMASK.bit.EIC_ = LOW;
#else

	//// Clock EIC enable
	PM->APBAMASK.bit.EIC_ = HIGH;
	
	// Setting Generic Clock EIC
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_EIC) | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
	EXTINT_RF_int();
	
	// NVIC config
	NVIC_DisableIRQ(EIC_IRQn);
	NVIC_ClearPendingIRQ(EIC_IRQn);
	NVIC_SetPriority(EIC_IRQn, EIC_IRQn_app_priority);
	NVIC_EnableIRQ(EIC_IRQn);
	
	//EIC enable			  
	EIC->CTRL.bit.ENABLE = HIGH;
	while(EIC->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
#endif /* EIC_PERIPHERAL_ENABLED*/
}

void GCLK2_startup(){
	
	GCLK->GENDIV.reg =	GCLK_GENDIV_ID(0x2) | // Generic Clock Generator 1
						GCLK_GENDIV_DIV(4);
	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ); /* Wait for synchronization */
	
	/* Write Generic Clock Generator 1 configuration */
	GCLK->GENCTRL.reg =	GCLK_GENCTRL_ID(0x2) | // Generic Clock Generator 2
						GCLK_GENCTRL_SRC_XOSC32K | // Selected source is External 32KHz Oscillator
						GCLK_GENCTRL_DIVSEL | // The generic clock generator equals the clock source divided by 2^(GENDIV.DIV+1).
						GCLK_GENCTRL_GENEN ;
	while ( GCLK->STATUS.reg & GCLK_STATUS_SYNCBUSY ); /* Wait for synchronization */
}

void RTC_peripheral_init(){
#if RTC_PERIPHERAL_ENABLED == 0
	//// Clock RTC disabled
	PM->APBAMASK.bit.RTC_ = LOW;
#else

	//// Clock RTC enable
	PM->APBAMASK.bit.RTC_ = HIGH;

	RTC_int();

	// NVIC config
 	NVIC_DisableIRQ(RTC_IRQn);
 	NVIC_ClearPendingIRQ(RTC_IRQn);
 	NVIC_SetPriority(RTC_IRQn, RTC_IRQn_app_priority);
 	NVIC_EnableIRQ(RTC_IRQn);	
		
	//RTC enable
	RTC->MODE2.CTRL.bit.ENABLE = HIGH;
	while(RTC->MODE2.STATUS.bit.SYNCBUSY == HIGH);	
	
#endif /* RTC_PERIPHERAL_ENABLED*/
}

void WDT_peripheral_init(){
#if WDT_PERIPHERAL_ENABLED == 0
	//// Clock WDT disabled
	PM->APBAMASK.bit.WDT_ = LOW;
#else
	// Undefined initialization, could be done by the ArduinoCore
#endif /* WDT_PERIPHERAL_ENABLED*/
}

void PORT_peripheral_init(){
#if PORT_PERIPHERAL_ENABLED == 0
	//// Clock PORT disabled
	PM->APBBMASK.bit.PORT_ = LOW;
#else
	//// Clock PORT disabled enable
	PM->APBBMASK.bit.PORT_ = HIGH;

/*	All registers for pin configuration, example.
	#define PORT_	PORT_P[A:B]0n
	#define PIN_	PIN_P[A:B]0n
	#define PMUX_	PORT_PMUX_PMUXO(PORT_PMUX_PMUXO_A_Val)	//Pin impar (odd pin)
					PORT_PMUX_PMUXE(PORT_PMUX_PMUXO_A_Val);	//Pin par   (even pin)	... Peripheral Multiplexing Selection

	PORT->Group[PIN_/32].DIRCLR.reg									= PORT_;  // Data Direction: input.		
	PORT->Group[PIN_/32].PINCFG[(PIN_ - ((PIN_/32)*32))].bit.INEN	= HIGH;	  // Read-Back Input Enable.
	PORT->Group[PIN_/32].PINCFG[(PIN_ - ((PIN_/32)*32))].bit.PULLEN	= LOW;	  // Pull Enable.
	PORT->Group[PIN_/32].OUTSET.reg									|= PORT_; // Pull-up Mode.
	PORT->Group[PIN_/32].PINCFG[(PIN_ - ((PIN_/32)*32))].bit.DRVSTR	= LOW;	  // Output Driver Strength Selection.
	PORT->Group[PIN_/32].CTRL.reg									= PORT_CTRL_SAMPLING((PIN_ - ((PIN_/32)*32)));	// Input Sampling Mode.			
	PORT->Group[PIN_/32].PINCFG[(PIN_ - ((PIN_/32)*32))].bit.PMUXEN	= HIGH;	// Peripheral Multiplexer Enable (REG_OUT control).	
	PORT->Group[PIN_/32].PMUX[((PIN_ - ((PIN_/32)*32)))/2].reg		|= PMUX_
*/

	PORT_GPIO_RF_int();
	
	PORT_EXTINT_RF_int();
	
	PORT_SPI_2_int();
		
	PORT_GPIO_indications_int();
		
#endif /* PORT_PERIPHERAL_ENABLED*/
}

void SERCOMx_peripheral_init(){
#if SERCOMx_PERIPHERAL_ENABLED == 0
	//// Clock SERCOMx disabled
	PM->APBCMASK.bit.SERCOM0_ = LOW;
	PM->APBCMASK.bit.SERCOM1_ = LOW;
	PM->APBCMASK.bit.SERCOM2_ = LOW;
	PM->APBCMASK.bit.SERCOM3_ = LOW;
	PM->APBCMASK.bit.SERCOM4_ = LOW;
	PM->APBCMASK.bit.SERCOM5_ = LOW;
#else

	//// Clock SERCOMx enable
	PM->APBCMASK.bit.SERCOM0_ = HIGH;
	PM->APBCMASK.bit.SERCOM1_ = HIGH;
	PM->APBCMASK.bit.SERCOM2_ = HIGH;
	PM->APBCMASK.bit.SERCOM3_ = HIGH;
	PM->APBCMASK.bit.SERCOM4_ = HIGH;	// Used by arduino core SPI library.
	PM->APBCMASK.bit.SERCOM5_ = HIGH;

	// Setting Generic Clock SERCOMx (SLOW)
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_SERCOMX_SLOW) | GCLK_CLKCTRL_GEN_GCLK1 | GCLK_CLKCTRL_CLKEN;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains

	SERCOM_SPI_2_int();
	serial_GNSS_start_link(9600); // using with USART SIM868
	
#endif /* SERCOMx_PERIPHERAL_ENABLED*/
}

void EVSYS_peripheral_init(){
#if EVSYS_PERIPHERAL_ENABLED == 0
	//// Clock EVSYS disabled
	PM->APBCMASK.bit.EVSYS_ = LOW;
#else

	//// Clock EVSYS enable
	PM->APBCMASK.bit.EVSYS_ = HIGH;
	
	// Setting Generic Clock EVSYS
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_EVSYS_0_Val) | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN ;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
	channel_0_init();
	channel_1_init();
	
#endif /* EVSYS_PERIPHERAL_ENABLED*/
}

void TCx_peripheral_init(){
#if TCx_PERIPHERAL_ENABLED == 0
	//// Clock TCx disabled
	PM->APBCMASK.bit.TC3_ = LOW;
	PM->APBCMASK.bit.TC4_ = LOW;
	PM->APBCMASK.bit.TC5_ = LOW;
	PM->APBCMASK.bit.TC6_ = LOW;
	PM->APBCMASK.bit.TC7_ = LOW;
#else
	
	//// Clock TCx enable
	PM->APBCMASK.bit.TC3_ = HIGH;
	PM->APBCMASK.bit.TC4_ = HIGH;
	
	// Setting Generic Clock TCx
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_TCC2_TC3_Val) | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN ;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_TC4_TC5_Val) | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN ;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains

	TCx_init();

	//NVIC config
 	NVIC_DisableIRQ(TCx_IRQn);
 	NVIC_ClearPendingIRQ(TCx_IRQn);
 	NVIC_SetPriority(TCx_IRQn, TCx_IRQn_app_priority);
 	NVIC_EnableIRQ(TCx_IRQn);
		
	//TCx enable
	ADC->CTRLA.bit.ENABLE = HIGH;
	while(ADC->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains


#endif /* TCx_PERIPHERAL_ENABLED*/
}

void TCCx_peripheral_init(){
#if TCCx_PERIPHERAL_ENABLED == 0
	//// Clock TCCx disabled
	PM->APBCMASK.bit.TCC0_ = LOW;
	PM->APBCMASK.bit.TCC1_ = LOW;
	PM->APBCMASK.bit.TCC2_ = LOW;
#else
	// Undefined initialization.
#endif /* TCCx_PERIPHERAL_ENABLED*/
}

void AC_peripheral_init(){
#if AC_PERIPHERAL_ENABLED == 0
	//// Clock AC disabled
	PM->APBCMASK.bit.AC_ = LOW;
#else
	#error "Undefined initialization."
#endif /* AC_PERIPHERAL_ENABLED*/
}

void ADC_peripheral_init(){
#if ADC_PERIPHERAL_ENABLED == 0
	//// Clock ADC disabled
	PM->APBCMASK.bit.ADC_ = LOW;
#else
	//// Clock ADC enable
	PM->APBCMASK.bit.ADC_ = HIGH;
	
	// Setting Generic Clock ADC
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(GCLK_CLKCTRL_ID_ADC_Val) | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN ;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
	ADC_init();
		
	//NVIC config
	NVIC_DisableIRQ(ADC_IRQn);
	NVIC_ClearPendingIRQ(ADC_IRQn);
	NVIC_SetPriority(ADC_IRQn, ADC_IRQn_app_priority);
	NVIC_EnableIRQ(ADC_IRQn);
	
	//ADC enable			  
	ADC->CTRLA.bit.ENABLE = HIGH;
	while(ADC->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
#endif /* ADC_PERIPHERAL_ENABLED*/
}

void DAC_peripheral_init(){
#if DAC_PERIPHERAL_ENABLED == 0
	//// Clock DAC disabled
	PM->APBCMASK.bit.DAC_ = LOW;
#else
	#error "Undefined initialization."
#endif /* DAC_PERIPHERAL_ENABLED*/
}

void I2S_peripheral_init(){
#if I2S_PERIPHERAL_ENABLED == 0
	//// Clock I2S disabled
	PM->APBCMASK.bit.I2S_ = LOW;
#else
	#error "Undefined initialization."
#endif /* I2S_PERIPHERAL_ENABLED*/
}

void PTC_peripheral_init(){
#if PTC_PERIPHERAL_ENABLED == 0
	//// Clock PTC disabled
	PM->APBCMASK.bit.PTC_ = LOW;
#else
	#error "Undefined initialization."
#endif /* PTC_PERIPHERAL_ENABLED*/
}
