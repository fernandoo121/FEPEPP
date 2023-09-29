/*
 * recuperacion.c
 *
 * Created: 23/01/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
#include "pro_routines.h"

#define TERNARIO_ESTADO_FSM()		(unidad_flash_init_ != FALSE ? RELEVAMIENTO : GENERACION)

static unsigned long resp_direccion_datos_relevados = NOTHING;
static struct data_task_0 resp_metadatos;

void recuperacion_unidad_flash();
void recuperacion_local(struct data_task_0 *metadatos);
void copia_metadatos(unsigned char *metadato_pegado, unsigned char *metadato_copia, unsigned int size);

/* 
 * Definida para ejecutar acciones secuenciales inherentes a la recuperación de metadatos.
 *
 * #3
 * Entrada:	Operación normal				No aplica
 *			Operación fuera de línea		Desde #2
 *			Operación de sincronización		Desde #0/2
 * Accion:	Consultar documento
 * Salida:	Después de secuencia
 *
 */
void recuperacion_metadatos(struct data_task_0 *metadatos){

	if (unidad_flash_init_ == FALSE)
		inicializar_fsm();
	else {
		if (direccion_datos_relevados > resp_direccion_datos_relevados)
			recuperacion_unidad_flash();
		
		recuperacion_local(metadatos);
	}
	
	estado_fsm_task_0 = TERNARIO_ESTADO_FSM();
}

/* 
 * Extrae a respaldo, desde la unidad flashla, la siguiente estructura de metadatos a relevar.
 */
void recuperacion_unidad_flash(){
	
	file_set_position_link(direccion_datos_relevados);
	resp_direccion_datos_relevados = direccion_datos_relevados;
	
	read_metadata_SD_MMC(&resp_metadatos);
	
 	if (unidad_flash_init_ == FALSE)
 		corrupcion_metadatos_unidad(&resp_metadatos);
	
	file_set_position_link(direccion_escritura);
}

/* 
 * Respalda los metadatos desde la estructura local a la global.
 */
void recuperacion_local(struct data_task_0 *metadatos){
	
	copia_metadatos(metadatos->data_oprc, resp_metadatos.data_oprc, SIZE_DATA_OPRC);
	copia_metadatos(metadatos->data_tlm, resp_metadatos.data_tlm, SIZE_DATA_TLM);
	copia_metadatos(metadatos->id_spbp, resp_metadatos.id_spbp, SIZE_ID_SPBP);
	copia_metadatos(metadatos->id_oprr, resp_metadatos.id_oprr, SIZE_ID_OPRR);
	copia_metadatos(metadatos->id_ebps, resp_metadatos.id_ebps, SIZE_ID_EBPS);
	copia_metadatos(metadatos->id_cdll, resp_metadatos.id_cdll, SIZE_ID_CDLL);
	copia_metadatos(metadatos->raw_gnss, resp_metadatos.raw_gnss, SIZE_RAW_GNSS);
}

/* 
 * Copia metadatos entre la estructura local y la global.
 */
void copia_metadatos(unsigned char *metadato_pegado, unsigned char *metadato_copia, unsigned int size){

	for (int i = 0; i < size; i++)
		ptr_access(metadato_pegado, i) = ptr_access(metadato_copia, i);
}
