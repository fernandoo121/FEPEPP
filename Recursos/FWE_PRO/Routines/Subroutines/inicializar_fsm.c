/*
 * inicializar_fsm.c
 *
 * Created: 23/01/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "pro_routines.h"

#define TERNARIO_SECUENCIA_FSM()	(direccion_datos_relevados == direccion_escritura ? NORMAL : SINCRONIZAR)
#define TERNARIO_NUM_OPRC()			(sizeof(num_oprc) > 2 ? (sizeof(num_oprc) - 2)*8 : 0)

unsigned char secuencia;
unsigned char estado_fsm_task_0;

unsigned long direccion_escritura = NOTHING;
unsigned long direccion_datos_relevados = NOTHING;

void recuperar_datos_ultimo_dia_trabajo();
void recuperar_direccion_datos_relevados();

/* 
 * Inicializa los parámetros principales de la FSM luego de un rst.
 */
void inicializar_fsm(){
	
	init_SD_MMC();
	
	if (unidad_flash_init_ == TRUE){	
		recuperar_direccion_datos_relevados();
	}

	secuencia = TERNARIO_SECUENCIA_FSM();
}

/* 
 * Recupera la última dirección de datos respaldados ante un rst.
 */
void recuperar_direccion_datos_relevados(){
	
	direccion_escritura = file_get_position_link();
	
	if (direccion_escritura == DIRECCION_INICIO_FLASH){
		send_ulong_SD_MMC(NOTHING);
		direccion_datos_relevados = direccion_escritura = file_get_position_link(); // Generamos espacio en memoria, desplasamiento puntero escritura
		
	} else {
		
		file_set_position_link(DIRECCION_INICIO_FLASH);
		
		read_ulong_SD_MMC(&direccion_datos_relevados);
		
		/* Última dirección que se puede garantisar como relevada ante un rst. */
		if (direccion_datos_relevados > SIZE_METADATA && direccion_datos_relevados < (SIZE_METADATA*DECREMENTO_DIRECCION_ULTIMO_RELEVO_ASEGURADO))
			direccion_datos_relevados = DIRECCION_INICIO_METADATA;
		else if(direccion_datos_relevados > (SIZE_METADATA*DECREMENTO_DIRECCION_ULTIMO_RELEVO_ASEGURADO))
			direccion_datos_relevados -= (SIZE_METADATA*DECREMENTO_DIRECCION_ULTIMO_RELEVO_ASEGURADO);
		else
			direccion_datos_relevados = direccion_escritura;
			
		file_set_position_link(direccion_escritura);
	}
}