/*
 * pro_routines.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#ifndef PRO_ROUTINES_H_
#define PRO_ROUTINES_H_

 #include "slave_FlashDrive.h"
 
 enum estado_fsm_task_0 {
	GENERACION,
	RELEVAMIENTO,
	RESPALDO,
	RECUPERACION,
	NUM_ESTADOS
 };

 extern unsigned char estado_fsm_task_0;

 enum secuencia{
	NORMAL,
	FUERA_LINEA,
	SINCRONIZAR,
 };

 extern unsigned char secuencia;

 extern unsigned long direccion_escritura;			// Ultima posición en memoria con metadatos corectamente esctitos, en bytes desde el principio.
 extern unsigned long direccion_datos_relevados;		// Ultima posición en memoria con metadatos relevados, en bytes desde el principio.

#ifdef __cplusplus
extern "C" {
#endif

	void inicializar_fsm();	// Inicializa los parámetros principales de la FSM luego de un rst.

	// Estados FSM
	void generacion_metadatos(struct data_task_0 *metadatos);
	void relevamiento_metadatos(struct data_task_0 *metadatos);
	void respaldo_metadatos(struct data_task_0 *metadatos);
	void recuperacion_metadatos(struct data_task_0 *metadatos);

#ifdef __cplusplus
}
#endif
#endif /* PRO_ROUTINES_H_ */