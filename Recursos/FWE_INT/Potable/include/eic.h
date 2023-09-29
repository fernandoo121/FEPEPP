/*
 * eic.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */


#ifndef EIC_H_
#define EIC_H_

 /* EIC public definition */
 //#define ...



 #ifdef __cplusplus
 extern "C" {
 #endif
 
	 /*
	  * Private functions
	  */
 
		// EXTIN RF
		void PORT_EXTINT_RF_int();
		void EXTINT_RF_int();
		void EXTINT_RF_Handler();

	 /*
	  * Public functions
	  */
	 
 		// EXTIN RF
 		void ICR_cmt2300a();
 		void ICR_DISABLE_gpio3();
 		void ICR_ENABLE_gpio3();

 		// ArduinoCore
 		void EIC_Handler_link();

 #ifdef __cplusplus
 }
 #endif

#endif /* EIC_H_ */