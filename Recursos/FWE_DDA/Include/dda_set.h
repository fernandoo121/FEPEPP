/*
 * dda_set.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef DDA_SET_H_
#define DDA_SET_H_

#define DEPURACION_TASK2_ENABLED		0	// Envía mensajes de depuracion al puerto serial (ejemplo declaración en main.c).
#define RAW_TLM_TASK2_ENABLED			0	// Envía por puerto serial datos crudos de telemetría para análisis.

 #define PRUEBA_SIM868					0	// Imprime en el monitor serial la configuración actual de todos los registros.
#define TRAMAS_DES_AL_PUERTO_SERIAL		0	// Envía las tramas con representación ASCII al puerto serial.
//#define TRAMAS_DES_TIPO_HEXA_			0	// Representación ASCII tipo hexadecimal si TRAMAS_AL_PUERTO_SERIAL = 1.
#define SIMULAR_PROTOCOLO_DES_X_USB		0	// Alimenta al protocolo de comunicación por el serial USB.

#endif /* DDA_SET_H_ */