/*
 * respaldo.c
 *
 * Created: 23/01/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
#include "pro_routines.h"

#define TERNARIO_ESTADO_FSM()			(secuencia == NORMAL || unidad_flash_init_ == FALSE ? RELEVAMIENTO : RECUPERACION)
#define TERNARIO_DIRECCION_ESCRITURA()	unidad_flash_init_ != FALSE ? direccion_escritura = file_get_position_link() : file_set_position_link(direccion_escritura)

/* 
 * Definida para ejecutar acciones secuenciales inherentes al respaldo de metadatos.
 *
 * #2
 * Entrada:	Operación normal				Desde #0
 *			Operación fuera de línea		Desde #0
 *			Operación de sincronización		Desde #0
 * Accion:	Consultar documento.
 * Salida:	Después de secuencia
 *
 */
void respaldo_metadatos(struct data_task_0 *metadatos){
	
	if (unidad_flash_init_ == FALSE)
		inicializar_fsm();
	else {
		
		send_metadata_SD_MMC(metadatos);
		
		if (unidad_flash_init_ != FALSE)
			xQueueReset(QueueHandle_comunicacion); // Si el respaldo esta ok, se autorisa recepción de más metadatos
	}
	
	TERNARIO_DIRECCION_ESCRITURA();
	estado_fsm_task_0 = TERNARIO_ESTADO_FSM();
}