/*
 * dda_set.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef DDA_SET_H_
#define DDA_SET_H_

#define DEPURACION_TASK2_ENABLED		0	// Env�a mensajes de depuracion al puerto serial (ejemplo declaraci�n en main.c).
#define RAW_TLM_TASK2_ENABLED			0	// Env�a por puerto serial datos crudos de telemetr�a para an�lisis.

 #define PRUEBA_SIM868					0	// Imprime en el monitor serial la configuraci�n actual de todos los registros.
#define TRAMAS_DES_AL_PUERTO_SERIAL		0	// Env�a las tramas con representaci�n ASCII al puerto serial.
//#define TRAMAS_DES_TIPO_HEXA_			0	// Representaci�n ASCII tipo hexadecimal si TRAMAS_AL_PUERTO_SERIAL = 1.
#define SIMULAR_PROTOCOLO_DES_X_USB		0	// Alimenta al protocolo de comunicaci�n por el serial USB.

#endif /* DDA_SET_H_ */