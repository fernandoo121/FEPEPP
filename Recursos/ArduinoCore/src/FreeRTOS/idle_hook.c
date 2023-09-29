
#include "../../include/FreeRTOS/FreeRTOS.h"
#include <Arduino.h>


// this is referring to the loop function of your arduino project
extern void loop(void); 

void  __attribute__((weak)) vApplicationIdleHook( void ) 
{
   //will use your projects loop function as the rtos idle loop
}
