/*
 * gateway.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#ifndef GATEWAY_H_
#define GATEWAY_H_

 #include <samd21g18a.h>
 #include <stdio.h>

 #include "link_arduinocore.h"

 #include "FreeRTOS.h"
 #include "task.h"
 #include "queue.h"
 #include "event_groups.h"

 #include "gateway_set.h"
 #include "gateway_portable.h"
 #include "metadata.h"
 #include "user_interface.h"
 #include "pro.h"
 #include "com.h"
 #include "dda.h"
 #include "vin.h"
 #include "fte.h"
 
 /*

NOTA: TASK_STACK_LENG_

	  El valor especifica el número de palabras que la pila puede contener,
      no su número de bytes. Por ejemplo, como la pila tiene 32 bits de ancho,
	  si se pasa usStackDepth con un valor de 100, se asignarán 400 bytes de
	  espacio de pila (100* 4 bytes). 
	  
	  La profundidad de la pila multiplicada por el ancho de la pila no debe 
	  superar el valor máximo que puede contenerse en una variable de tipo uint16_t.
	  
	  ATSAMD21G18A -> SRAM 32768 bytes (23872)

*/

 #define TASK_STACK_LENG_procesamiento		300
 #define TASK_STACK_LENG_comunicacion		300
 #define TASK_STACK_LENG_descarga			400
 #define TASK_STACK_LENG_vinculacion		200
 #define TASK_STACK_LENG_fuente				200

 #define QUEUE_LENG_metadatos				1
 #define QUEUE_LENG_vinculacion				1
 #define QUEUE_LENG_fuente					1

 #define NOTHING	0

 #ifndef _WIRING_CONSTANTS_
 #define HIGH	1
 #define LOW		0
 #endif /* _WIRING_CONSTANTS_ */
 #define TRUE	1
 #define FALSE	0

 //Estado variables de interés
 #define NO			0b00
 #define SI			0b01

 #define DELAY_MS(time_)		vTaskDelay(pdMS_TO_TICKS(time_))
 #define DELAY_US(time_)		delayMicroseconds_link(time_)
 #define CURRENT_TIME_MS		millis_link()
 #define CURRENT_TIME_US		micros_link()

 #define CRITICAL_SECTION_INIT()		taskENTER_CRITICAL()
 #define CRITICAL_SECTION_END()			taskEXIT_CRITICAL()
 #define CRITICAL_SECTION_BLOCK(line_)	CRITICAL_SECTION_INIT(); line_ CRITICAL_SECTION_END()

 #define SUSPEND_ALL_SECTION_INIT()			vTaskSuspendAll()
 #define SUSPEND_ALL_SECTION_END()			xTaskResumeAll()
 #define SUSPEND_ALL_SECTION_BLOCK(line_)	SUSPEND_ALL_SECTION_INIT(); line_ SUSPEND_ALL_SECTION_END()

 #define DEPURACION_TASKx_ENABLED(state_)	(DEPURACION_TASK0_ENABLED == state_ || DEPURACION_TASK1_ENABLED == state_ || DEPURACION_TASK2_ENABLED == state_ || DEPURACION_TASK3_ENABLED == state_ || DEPURACION_TASK4_ENABLED == state_)
 #define RAW_TLM_TASKx_ENABLED(state_)		(RAW_TLM_TASK0_ENABLED == state_ || RAW_TLM_TASK1_ENABLED == state_ || RAW_TLM_TASK2_ENABLED == state_ || RAW_TLM_TASK3_ENABLED == state_ || RAW_TLM_TASK4_ENABLED == state_)

 #define ptr_access(ptr_,pos_) (*((ptr_) + pos_))

 extern TaskHandle_t	TaskHandle_procesamiento;
 extern TaskHandle_t	TaskHandle_comunicacion;
 extern TaskHandle_t	TaskHandle_descarga;
 extern TaskHandle_t	TaskHandle_vinculacion;
 extern TaskHandle_t	TaskHandle_fuente;

 extern QueueHandle_t QueueHandle_metadatos;
 extern QueueHandle_t QueueHandle_comunicacion;
 extern QueueHandle_t QueueHandle_vinculacion;
 extern QueueHandle_t QueueHandle_fuente;

 extern EventGroupHandle_t EventGroup_indication;
 
#if DEPURACION_TASKx_ENABLED(1) || RAW_TLM_TASKx_ENABLED(0)
 #include <string.h>
 extern char debug_string_[256];

/* EJEMPLO DE DECLARACION DATOS DEPURACION Y TELEMETRIA */

	//Tipo simple:
	
	#if RAW_TLM_TASKx_ENABLED == 1
		//declaración opcional
	#else
	 #if DEPURACION_TASKx_ENABLED == 1
		serialUSB_print_link(""); /* DEBUGGING */
	 #endif /*DEPURACION_TASKx_ENABLED*/
	#endif /*RAW_TLM_TASKx_ENABLED*/
	                             
	//Tipo varible:
	
	#if RAW_TLM_TASKx_ENABLED == 1
		//declaración opcional
	#else
	 #if DEPURACION_TASKx_ENABLED == 1
		sprintf(debug_string_, "", -);
		serialUSB_print_link(debug_string_); /* DEBUGGING */
	 #endif /*DEPURACION_TASKx_ENABLED*/
	#endif /*RAW_TLM_TASKx_ENABLED*/

#endif /* SIMULAR_PROTOCOLO_X_USB */


 #ifdef __cplusplus
 extern "C" {
 #endif

	 void task_procesamiento(void *pvParameters);
	 void task_comunicacion(void *pvParameters);
	 void task_descarga(void *pvParameters);
	 void task_vinculacion(void *pvParameters);
	 void task_fuente(void *pvParameters);
 
	#ifdef FPRO_sim_on
	 void SimData_procesamiento();
	 #warning "SimData_procesamiento ON"
	#endif // FPRO_sim_on
	#ifdef FCOM_sim_on
	 void SimData_comunicacion();
	 #warning "SimData_comunicacion ON"
	#endif // FCOM_sim_on
	#ifdef FDDA_sim_on
	 void SimData_descarga();
	 #warning "SimData_descarga ON"
	#endif // FDDA_sim_on
	#ifdef FVIN_sim_on
	 void SimData_vinculacion();
	 #warning "SimData_vinculacion ON"
	#endif // FVIN_sim_on
	#ifdef FFTE_sim_on
	 void SimData_fuente();
	 #warning "SimData_fuente ON"
	#endif // FFTE_sim_on

	 char uchar_incremento_seguro(unsigned char *variable);
	 char uint_incremento_seguro(unsigned int *variable);
	 char ulong_control_desbordamiento_adicion(unsigned long *variable, unsigned int adicion);
	 char uint_control_desbordamiento_adicion(unsigned int *variable, unsigned int adicion);
 
 #ifdef __cplusplus
 }
 #endif

#endif /* GATEWAY_H_ */