/*
 * com_set.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */


#ifndef COM_SET_H_
#define COM_SET_H_

 #define DEPURACION_TASK1_ENABLED	0	// Env�a mensajes de depuracion al puerto serial (ejemplo declaraci�n en main.c).
 #define RAW_TLM_TASK1_ENABLED		0	// Env�a por puerto serial datos crudos de telemetr�a para an�lisis.

 //#define TIEMPO_ESPARA_PARA_SUSPENSION	10	// Tiempo para supencion de electronica, en minutos.
 #define TIEMPO_ESPARA_SOLICITUD_USUARI 500	// Tiempo espera solicitud usuario, en ms (cuando no se tiene actividad en el canal).

 #define FSK_	//----------------------------------------------------------------------------------------- //
 #define BT05_	// Solo GFSK																			    //
 //																											//
 //	DEFINICI�N DE ESQUEMA DE MODULACI�N																		//
 //																											//
 //		FSK_																								//
 //		GFSK	Gaussian BT	[BT05_ = 0.5, BT_08 = 0.8, BT10_ = 1.0]											//
 //																											//
 // -------------------------------------------------------------------------------------------------------- //

 #define _100kbps		// -------------------------------------------------------------------------------- //
 //																											//
 //	DEFINICI�N DE CONFIGURACIONES PREESTABLECIDAS PARA LA TASA DE DATOS										//
 //																											//
 //		_300kbps																							//
 //				Data Rate = 300.0 kbps																		//
 //			    Deviation = 100.0 kHz																		//
 //		_200kbps																							//
 //				Data Rate = 200.0 kbps																		//
 //			    Deviation = 150.0 kHz																		//
 //		_100kbps																							//
 //				Data Rate = 100.0 kbps																		//
 //			    Deviation = 200.0 kHz																		//
 //		__50kbps																							//
 //				Data Rate = 50.0 kbps																		//
 //			    Deviation = 100.0 kHz																		//
 // -------------------------------------------------------------------------------------------------------- //

 #define _13dbm		// ------------------------------------------------------------------------------------ //
 //																											//
 //	DEFINICI�N DE CONFIGURACIONES PREESTABLECIDAS PARA POTENCIA TX											//
 //																											//
 //		_13dbm																								//
 //				TRx Matching Network Type = 13																//
 //				Tx Power                  = +13																//
 //		_20dbm																								//
 //				TRx Matching Network Type = 20																//
 //				Tx Power                  = +20																//
 // -------------------------------------------------------------------------------------------------------- //
 
 #define PRUEBA_CMT2300A				0	// Imprime en el monitor serial la configuraci�n actual de todos los registros.
 #define CAPTURAR_CRC_FAIL				1	// Cambia flujo de software recepci�n paquetes para captura de interferencia en canal.
 #define TRAMAS_COM_AL_PUERTO_SERIAL	0	// Env�a las tramas con representaci�n ASCII al puerto serial.
 #define TRAMAS_COM_TIPO_HEXA_			0	// Representaci�n ASCII tipo hexadecimal si TRAMAS_AL_PUERTO_SERIAL = 1.
 #define SIMULAR_PROTOCOLO_COM_X_USB	0	// Alimenta al protocolo de comunicaci�n por el serial USB.
 #define RETARDOS_SPI3_RF				0	// Habilita retardos bus SPI seg�n requisitos de hardware de radiofrecuencia.


#endif /* COM_SET_H_ */