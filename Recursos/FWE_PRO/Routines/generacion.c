/*
 * generacion.c
 *
 * Created: 23/01/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "pro_routines.h"

#define TERNARIO_ESPERA_LISTA()		(secuencia == NORMAL ? portMAX_DELAY : NOTHING)
#define TERNARIO_ESTADO_FSM()		((Queue_result == pdTRUE && metadatos->solicitud_ == NADA_) ? RESPALDO : ((Queue_result == pdTRUE && metadatos->solicitud_ != NADA_) ? GENERACION : (secuencia == SINCRONIZAR ? RECUPERACION : RELEVAMIENTO)))

static struct data_task_3 vinculacion;
static struct data_task_4 fuente;

#if CAPTURAR_CRC_FAIL == 1
extern unsigned char comunicacion_tlm_;
#endif
extern unsigned char descarga_tlm_;

/* Generacion metadatos */
unsigned char id_CDLL(unsigned char offset, unsigned int id);
unsigned char id_EBPS(unsigned char offset);

/* 
 * Definida para ejecutar acciones secuenciales inherentes a la generación de metadatos->
 *
 * #0
 * Entrada:	Operación normal				RST/Desde #1
 *			Operación fuera de línea		Desde #1
 *			Operación de sincronización		Desde #1
 * Accion:	Consultar documento.
 * Salida:	Después de secuencia
 *
 */
void generacion_metadatos(struct data_task_0 *metadatos){
	
	BaseType_t Queue_result;
	
	Queue_result = xQueuePeek(QueueHandle_comunicacion, metadatos, TERNARIO_ESPERA_LISTA()); // Eliminamos de la lista solo si se puede respaldar o relevar.
	
	if (Queue_result == pdTRUE && metadatos->solicitud_ == NADA_){
		
		// Identificación de la electrónica de la Estación Base 
 		metadatos->id_ebps[ID_EBPS_CAHR3_Pos] = id_EBPS((((SIZE_ID_EBPS -1) - ID_EBPS_CAHR3_Pos)*8));
 		metadatos->id_ebps[ID_EBPS_CAHR2_Pos] = id_EBPS((((SIZE_ID_EBPS -1) - ID_EBPS_CAHR2_Pos)*8));
 		metadatos->id_ebps[ID_EBPS_CAHR1_Pos] = id_EBPS((((SIZE_ID_EBPS -1) - ID_EBPS_CAHR1_Pos)*8));
 		metadatos->id_ebps[ID_EBPS_CAHR0_Pos] = id_EBPS((((SIZE_ID_EBPS -1) - ID_EBPS_CAHR0_Pos)*8));
				
		// Identificación del capataz
		xQueueReceive(QueueHandle_vinculacion, &vinculacion, NOTHING);	// Si no hay datos para procesar se envían los últimos recibidos.
				
		metadatos->id_cdll[ID_CDLL_CAHR4_Pos] = id_CDLL((((SIZE_ID_CDLL -1) - ID_CDLL_CAHR4_Pos)*8), vinculacion.id_capataz);
		metadatos->id_cdll[ID_CDLL_CAHR3_Pos] = id_CDLL((((SIZE_ID_CDLL -1) - ID_CDLL_CAHR3_Pos)*8), vinculacion.id_capataz);
		metadatos->id_cdll[ID_CDLL_CAHR2_Pos] = id_CDLL((((SIZE_ID_CDLL -1) - ID_CDLL_CAHR2_Pos)*8), vinculacion.id_capataz);
		metadatos->id_cdll[ID_CDLL_CAHR1_Pos] = id_CDLL((((SIZE_ID_CDLL -1) - ID_CDLL_CAHR1_Pos)*8), vinculacion.id_capataz);
		metadatos->id_cdll[ID_CDLL_CAHR0_Pos] = id_CDLL((((SIZE_ID_CDLL -1) - ID_CDLL_CAHR0_Pos)*8), vinculacion.id_capataz);
		
		// Datos funcionamiento electrónica
		xQueueReceive(QueueHandle_fuente, &fuente, NOTHING);	// Si no hay datos para procesar se envían los últimos recibidos.

		metadatos->data_tlm[DATA_TLM_CAHR4_Pos] = DATA_TLM_CEL			|
#if CAPTURAR_CRC_FAIL == 1
												  DATA_TLM_RF_EBPS		|
#endif
												  vinculacion.tlm_[3]	|
												  DATA_TLM_FLASH_EBPS	|
												  fuente.tlm_[3];
												  
#if METADATOS_AL_PUERTO_SERIAL == 1 && defined(task0)
		metadatos_al_puerto_serial_ascii(metadatos, NOTHING, NOTHING);
#endif /* METADATOS_AL_PUERTO_SERIAL */

	} else if(Queue_result == pdTRUE && metadatos->solicitud_ != NADA_){
		procesar_solicitudes_usuario(&metadatos->solicitud_);
		xQueueReset(QueueHandle_comunicacion); // Limpiamos solicitud
	}
	
	estado_fsm_task_0 = TERNARIO_ESTADO_FSM();
}

/* 
 * Retorna el identificación de la electrónica de la Estación Base  y su longitud en bytes, para cargar en ID_EBPS.
 */
unsigned char id_EBPS(unsigned char offset){
	
	static char id_data_calculated;
	//static unsigned char length_id;
	static unsigned int id_data/*[4]*/;
	
	if (id_data_calculated == FALSE){
		// 1) Obtenemos el ID.
		//id_data[0] = 0b10110011 << 20;
		//id_data[1] = 0b0;
		//id_data[2] = 0b0;
		//id_data[3] = 0b0;		
		// 2) Calculamos la Longitud en BYTE.
		//length_id = 0b00000001;		
		// 3) Cargamos valores en id_data.
		id_data = 0b0000000101100100 << 16; //100
		id_data_calculated = TRUE;
	}
		
	return id_data >> offset;
}

/* 
 * Retorna el identificación del capataz y su longitud en bytes, para cargar en ID_CDLL.
 */
unsigned char id_CDLL(unsigned char offset, unsigned int id){
	
	#define MASK 0b10000000000000000000000000000000
	
	static char id_data_calculated = FALSE;
	static char id_length = 0;
	static unsigned int id_data = 0;
	
 	if (id_data_calculated == FALSE){
 		for (unsigned char ind = 0; (id & (MASK >> ind)) == 0 && ind < sizeof(unsigned int) ; ind++){
 			id_length  = 4 - (ind + 1)/8;		// 1) Calculamos la Longitud en BYTE.
 			id_data = id << (32 - (id_length*8));	// 1) Cargamos valores para id_data.		
 		}
 		id_data_calculated = TRUE;
 	}
	if (offset > 24)
		 return id_length;
		 
	return id_data >> offset;
}