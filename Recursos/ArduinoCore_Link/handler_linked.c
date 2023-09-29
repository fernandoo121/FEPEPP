/*
 * handler_linked.c
 *
 * Created: 18/10/2022
 * Author : Andres Mezquida
 */

#include "Arduino.h"

#ifdef __cplusplus
extern "C" {
#endif

 /* Functions cortex_handlers.c ArduinoCore */
 void SysTick_Handler_ArduinoCore();
 void USB_Handler_ArduinoCore(void);
 void EIC_Handler_ArduinoCore(void);
 void SERCOM0_Handler_ArduinoCore();

#ifdef __cplusplus
}
#endif

/* Handler linked to ArduinoCore with IRQs*/
void SysTick_Handler(){
	SysTick_Handler_ArduinoCore();
}

void USB_Handler(void){
	USB_Handler_ArduinoCore();
}

void EIC_Handler_link(){
	EIC_Handler_ArduinoCore();
}

void SERCOM0_Handler_link(){
	SERCOM0_Handler_ArduinoCore();
}
