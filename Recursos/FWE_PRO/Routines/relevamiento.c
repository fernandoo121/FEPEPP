/*
 * relevamiento.c
 *
 * Created: 23/01/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
#include "pro_routines.h"

#define TERNARIO_ESPERA_LISTA()					(secuencia != FUERA_LINEA ? NOTHING : pdMS_TO_TICKS(TIEMPO_BLOQUEO_OPERACION_FUERA_LINEA))
#define TERNARIO_SECUENCIA_FSM()				(direccion_datos_relevados == direccion_escritura ? NORMAL : SINCRONIZAR)
#define TERNARIO_DIRECCION_DATOS_RELEVADOS()	((secuencia == NORMAL || unidad_flash_init_ == FALSE) ? direccion_escritura : direccion_datos_relevados + SIZE_METADATA)
void respaldar_direccion_datos_relevados();

/* 
 * Definida para ejecutar acciones secuenciales inherentes al relevamiento de metadatos.
 *
 * #1
 * Entrada:	Operación normal				Desde #0
 *			Operación fuera de línea		Desde #0
 *			Operación de sincronización		Desde #0
 * Accion:	Consultar documento.
 * Salida:	Después de secuencia
 *
 */
void relevamiento_metadatos(struct data_task_0 *metadatos){
	
	BaseType_t Queue_result;

	Queue_result = xQueueSend(QueueHandle_metadatos, metadatos, TERNARIO_ESPERA_LISTA());
	
	if (Queue_result == pdTRUE){
		
		if (unidad_flash_init_ != TRUE)
			xQueueReset(QueueHandle_comunicacion);	// Si el respaldo falla, pero el relevo esta ok, se autoriza recepción de más metadatos
			
		direccion_datos_relevados = TERNARIO_DIRECCION_DATOS_RELEVADOS();
		respaldar_direccion_datos_relevados();
		secuencia = TERNARIO_SECUENCIA_FSM();
				
	} else
		secuencia = FUERA_LINEA;
	
	estado_fsm_task_0 = GENERACION;
}

/* 
 * Guarda en la unidad flash la dirección del último dato relevado a comunicacion.
 */
void respaldar_direccion_datos_relevados(){
	
	if (unidad_flash_init_ != FALSE){
		
		file_set_position_link(DIRECCION_INICIO_FLASH);
		send_ulong_SD_MMC(direccion_datos_relevados);
		file_set_position_link(direccion_escritura);
	}
}
