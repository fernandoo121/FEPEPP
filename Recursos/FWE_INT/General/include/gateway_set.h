/*
 * gateway_set.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#ifndef GATEWAY_SET_H_
#define GATEWAY_SET_H_

/* 
 * Selección mapeo de pines según electrónica.
 *
 */
/*Define el mapeo de pines para la PCB-ULT-002-RevA*/
#define PCB_ULT		// UNCOMMENT ENABLED

/*
 * Configuración para envio de metadatos con representación ASCII al puerto serial 
 */
#define METADATOS_AL_PUERTO_SERIAL	1	// Habilitación: 1 ON 0 OFF
#define ENVIAR_RAW_GNSS				0	// Habilitación: 1 ON 0 OFF
#define ESPERA_POR_SERIAL			0	// Habilitación: 1 ON 0 OFF (solo con task3)
#define CSV							1	// Habilitación: 1 ON 0 OFF (tipo presentacion de datos para archivo .csv)
#define DDA_	/* Opciones: PRO_ (se envain al generarse)
							 DDA_ (se envian al relevarse)	*/									 

/* 
 * Estado implementación firmware
 *
 *	• Simulación: procesa y/o genera metadatos de manera virtual.
 *	• Implementación: procesa y/o genera metadatos haciendo uso del hardware correspondiente.
 *
 *	Una implementación se habilita al comentar la definición correspondiente.
 */

#define FPRO_sim_on
#define FCOM_sim_on
//#define FDDA_sim_on
#define FVIN_sim_on
#define FFTE_sim_on

/* 
 * Prioridad tareas RTOS 
 */
#define TASK_STACK_PRIORITY_procesamiento		(tskIDLE_PRIORITY + 2)
#define TASK_STACK_PRIORITY_comunicacion		(tskIDLE_PRIORITY + 3)
#define TASK_STACK_PRIORITY_descarga			(tskIDLE_PRIORITY + 2)
#define TASK_STACK_PRIORITY_vinculacion			(tskIDLE_PRIORITY + 2)
#define TASK_STACK_PRIORITY_fuente				(tskIDLE_PRIORITY + 2)

/* ARDUINO_CORE */
#define START_WITH_ARDUINO_CORE 1		// Inicializa CPU del microcontrolador según núcleo arduino.

#endif /* GATEWAY_SET_H_ */