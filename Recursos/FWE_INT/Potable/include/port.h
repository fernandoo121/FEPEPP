/*
 * port.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */


#ifndef PORT_H_
#define PORT_H_

/* PORT public definition */

#define PORT_IN0(pin_)			((REG_PORT_IN0 & (1ul << pin_)) >> pin_)
#define PORT_IN1(pin_)			((REG_PORT_IN1 & (1ul << pin_)) >> pin_)

/* 
 * GPIO RF public definition 
 */

 #if defined(PCB_ULT)
  // PIN_RF_CSB (Pin PA07/D9) (Pin CSB Módulo Radiofrecuencia)
  #define PIN_RF_CSB		PIN_PA07
  #define PORT_RF_CSB	PORT_PA07

  // PIN_RF_FCSB (Pin PA10/D1TX) (Pin FCSB Módulo Radiofrecuencia)
  #define PIN_RF_FCSB	PIN_PA10
  #define PORT_RF_FCSB	PORT_PA10
 #endif /* PCB_ULT */

 #define RF_CSB_HIGH	PORT->Group[PIN_RF_CSB/32].OUTSET.reg = PORT_RF_CSB
 #define RF_FCSB_HIGH	PORT->Group[PIN_RF_FCSB/32].OUTSET.reg = PORT_RF_FCSB

 #define RF_FCSB_LOW	PORT->Group[PIN_RF_FCSB/32].OUTCLR.reg = PORT_RF_FCSB
 #define RF_CSB_LOW		PORT->Group[PIN_RF_CSB/32].OUTCLR.reg = PORT_RF_CSB

/* 
 * GPIO Indications public definition
 */

enum toggle_delay{
	BUZZER,
	LED_DONE,
	LED_WARNING,
	LED_COM,
	LED_GEO,
	NUM_INDICACIONES
};

#ifdef PCB_ULT
 #define PORT_BUZZER	PORT_PA03
 #define PIN_BUZZER		PIN_PA03
#endif /* PCB_ULT */
 #define BUZZER_LOW						PORT->Group[PIN_BUZZER/32].OUTCLR.reg = PORT_BUZZER
 #define BUZZER_HIGH					PORT->Group[PIN_BUZZER/32].OUTSET.reg = PORT_BUZZER
 #define BUZZER_TOGGLE					PORT->Group[PIN_BUZZER/32].OUTTGL.reg = PORT_BUZZER
 #define BUZZER_TOGGLE_MS(time_)		pin_toggle_ms(time_, PIN_BUZZER, PORT_BUZZER, BUZZER)

#ifdef PCB_ULT
 #define PORT_LED_DONE	PORT_PB22
 #define PIN_LED_DONE	PIN_PB22	// Led a bordo ULT-002-RevA con catodo comun.
 #define LED_DONE_LOW					PORT->Group[PIN_LED_DONE/32].OUTCLR.reg = PORT_LED_DONE
 #define LED_DONE_HIGH					PORT->Group[PIN_LED_DONE/32].OUTSET.reg = PORT_LED_DONE
#endif /* PCB_ULT */
 #define LED_DONE_TOGGLE				PORT->Group[PIN_LED_DONE/32].OUTTGL.reg = PORT_LED_DONE
 #define LED_DONE_TOGGLE_MS(time_)		pin_toggle_ms(time_, PIN_LED_DONE, PORT_LED_DONE, LED_DONE)

#ifdef PCB_ULT
 #define PORT_LED_WARNING	PORT_PB23
 #define PIN_LED_WARNING	PIN_PB23	// Led a bordo ULT-002-RevA con catodo comun.
#endif /* PCB_ULT */
 #define LED_WARNING_LOW				PORT->Group[PIN_LED_WARNING/32].OUTCLR.reg = PORT_LED_WARNING
 #define LED_WARNING_HIGH				PORT->Group[PIN_LED_WARNING/32].OUTSET.reg = PORT_LED_WARNING
 #define LED_WARNING_TOGGLE				PORT->Group[PIN_LED_WARNING/32].OUTTGL.reg = PORT_LED_WARNING
 #define LED_WARNING_TOGGLE_MS(time_)	pin_toggle_ms(time_, PIN_LED_WARNING, PORT_LED_WARNING, LED_WARNING)

#ifdef PCB_ULT
 #define PORT_LED_COM	PORT_PB02
 #define PIN_LED_COM	PIN_PB02	// Led a bordo ULT-002-RevA con catodo comun.
 #define LED_COM_LOW				PORT->Group[PIN_LED_COM/32].OUTCLR.reg = PORT_LED_COM
 #define LED_COM_HIGH				PORT->Group[PIN_LED_COM/32].OUTSET.reg = PORT_LED_COM
 #define LED_COM_TOGGLE				PORT->Group[PIN_LED_COM/32].OUTTGL.reg = PORT_LED_COM
 #define LED_COM_TOGGLE_MS(time_)	pin_toggle_ms(time_, PIN_LED_COM, PORT_LED_COM, LED_COM)
#endif /* PCB_ULT */

#ifdef PCB_ULT
 #define PORT_LED_GEO	PORT_PA02
 #define PIN_LED_GEO	PIN_PA02	// Led a bordo ULT-002-RevA con catodo comun.
 #define LED_GEO_LOW				PORT->Group[PIN_LED_GEO/32].OUTCLR.reg = PORT_LED_GEO
 #define LED_GEO_HIGH				PORT->Group[PIN_LED_GEO/32].OUTSET.reg = PORT_LED_GEO
 #define LED_GEO_TOGGLE				PORT->Group[PIN_LED_GEO/32].OUTTGL.reg = PORT_LED_GEO
 #define LED_GEO_TOGGLE_MS(time_)	pin_toggle_ms(time_, PIN_LED_GEO, PORT_LED_GEO, LED_GEO)
#endif /* PCB_ULT */

#ifdef __cplusplus
extern "C" {
#endif
 
 /*
  * Private functions
  */
 
	// GPIO_RF
	void PORT_GPIO_RF_int();
	
	// GPIO_indications 
	void PORT_GPIO_indications_int();
	

 /*
  * Public functions
  */
 
	void pin_toggle_ms(unsigned int delay, unsigned char pin, unsigned int port, unsigned char indicacion);

#ifdef __cplusplus
}
#endif
#endif /* PORT_H_ */