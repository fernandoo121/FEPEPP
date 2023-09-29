/*
 * extint_rf.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"
  
/* EIC private definition */

#if defined(PCB_ULT)
 // RF_GPIO3 (Pin PA14/D2) (Pin GPIO3 cmt2300a)
 #define PORT_EXTIN_RF		PORT_PA14
 #define PIN_EXTIN_RF		PIN_PA14
 #define EXTINTE_RF			EXTINTEO14
 #define EXTINT_RF			EXTINT14
 #define INTENSET_EXTIN_RF	EIC_INTENSET_EXTINT14
 #define INTENCLR_EXTIN_RF	EIC_INTENCLR_EXTINT14
 #define INTFLAG_EXTIN_RF	EIC_INTFLAG_EXTINT14
 #define CONFIG_EXTIN_RF		1
 #define SENSE_EXTIN_RF		SENSE6
 #define FILTEN_EXTIN_RF	FILTEN6
 #define PMUX_EXTIN_RF		PORT_PMUX_PMUXE(PORT_PMUX_PMUXE_A_Val)
#endif /* PCB_ULT*/
 
#define EXTIN_RF_PIN_STATUS (((PORT->Group[PIN_EXTIN_RF/32].IN.reg) & (1ul << PIN_EXTIN_RF)) >> PIN_EXTIN_RF)

/*
 * EIC private functions
 */
 void PORT_EXTINT_RF_int(){
#if defined(PCB_ULT)
	// EIC EXTIN14 (Pin GPIO3 Módulo Radiofrecuencia)
	PORT->Group[PIN_EXTIN_RF/32].DIRCLR.reg													= PORT_EXTIN_RF;	// Data Direction: input.
	PORT->Group[PIN_EXTIN_RF/32].PINCFG[(PIN_EXTIN_RF - ((PIN_EXTIN_RF/32)*32))].bit.INEN	= HIGH;				// Read-Back Input Enable.
	PORT->Group[PIN_EXTIN_RF/32].PINCFG[(PIN_EXTIN_RF - ((PIN_EXTIN_RF/32)*32))].bit.PULLEN	= LOW;				// Pull Enable.
	PORT->Group[PIN_EXTIN_RF/32].PINCFG[(PIN_EXTIN_RF - ((PIN_EXTIN_RF/32)*32))].bit.PMUXEN	= HIGH;				// Peripheral Multiplexer Enable (REG_OUT control).
	PORT->Group[PIN_EXTIN_RF/32].PMUX[(PIN_EXTIN_RF - ((PIN_EXTIN_RF/32)*32))/2].reg	   |= PMUX_EXTIN_RF;	// Peripheral Multiplexing Selection
#endif /* PCB_ULT*/
 }

void EXTINT_RF_int(){
#if defined(PCB_ULT)

	// EIC External Interrupt x Event Output Enable
	EIC->EVCTRL.bit.EXTINTE_RF = LOW;

	// EIC External Interrupt Request
	EIC->INTENCLR.reg = INTENCLR_EXTIN_RF;

	// EIC Input Sense Configuration
	EIC->CONFIG[CONFIG_EXTIN_RF].bit.SENSE_EXTIN_RF = EIC_CONFIG_SENSE3_RISE_Val;

	// Filter Enable
	EIC->CONFIG[CONFIG_EXTIN_RF].bit.FILTEN_EXTIN_RF = LOW;
#endif /* PCB_ULT*/
}

void EXTINT_RF_Handler(){
	if (EIC->INTFLAG.bit.EXTINT_RF == HIGH){
		ICR_cmt2300a();
		EIC->INTFLAG.reg |= INTFLAG_EXTIN_RF;
	}
}

/*
 * EIC public functions
 */

// NVIC Handler link
void ICR_cmt2300a(){
	
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;

	ICR_DISABLE_gpio3();
	
	vTaskNotifyGiveFromISR(TaskHandle_comunicacion, &xHigherPriorityTaskWoken);
	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

// Deshabilita la interrupción en cuestión
void ICR_DISABLE_gpio3(){
	
 	CRITICAL_SECTION_INIT();
 	 //EIC->INTENCLR.bit.EXTINT_GPIO3 = HIGH; si se declara de esta manera se borran todos los bit en 1, no funciona!
	 EIC->INTENCLR.reg = INTENCLR_EXTIN_RF;
 	CRITICAL_SECTION_END();
}

// Habilita la interrupción en cuestión
void ICR_ENABLE_gpio3(){
	
	CRITICAL_SECTION_INIT();
	 EIC->INTFLAG.reg |= INTFLAG_EXTIN_RF; // clean flag
	 EIC->INTENSET.bit.EXTINT_RF = HIGH; // ICR_ENABLE
	CRITICAL_SECTION_END();
}
