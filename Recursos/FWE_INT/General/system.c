/*
 * system.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include <limits.h>

 #include "gateway.h"
 
/* 
 * FUNCIÓN DE ENLACE DE TAREA DE INACTIVIDAD
 *
 * 
 *	Las funciones de enlace de tareas de inactividad tienen que cumplir las siguientes reglas.
 *
 *	1. Una función de enlace de tarea de inactividad nunca debe intentar bloqueos ni suspensiones.
 *	
 *	   Nota: Bloquear la tarea de inactividad, sea cual sea la forma en que se realice, puede provocar una
 *	   situación en la que no haya ninguna tarea disponible para entrar en el estado En ejecución.
 *	   
 *	2. Si la aplicación usa la función de API vTaskDelete(), el enlace de la tarea de inactividad siempre tiene
 *	   que volver a su intermediario en un período de tiempo razonable. Esto se debe a que la tarea de
 *	   inactividad es responsable de limpiar los recursos de kernel después de que se elimine una tarea. Si la
 *	   tarea de inactividad
 *
 */

static struct data_task_0 metadatos;

void vApplicationIdleHook( void ){
	
	capturar_solicitudes_usuario(&metadatos.solicitud_, QueueHandle_comunicacion, &metadatos);
	ejecucion_indicaciones_operario();

}

/*
 * Funciones para control de desbordamiento 
 */

// ...
char uchar_incremento_seguro(unsigned char *variable){
	
	if (*variable != UCHAR_MAX)
		(*variable)++;
	else
		return -1;
		
	return NOTHING;
}

// ...
char uint_incremento_seguro(unsigned int *variable){
	
	if (*variable != UINT_MAX)
		(*variable)++;
	else
		return -1;
		
	return NOTHING;
}

// ...
char ulong_control_desbordamiento_adicion(unsigned long *variable, unsigned int adicion){
	
	char resultado = NOTHING;
	signed long respaldo_variable = *variable;
	
	if ((*variable + adicion) < respaldo_variable)
		resultado = -1;
	
	return resultado;
}

// ...
char uint_control_desbordamiento_adicion(unsigned int *variable, unsigned int adicion){
	
	char resultado = NOTHING;
	signed long respaldo_variable = *variable;
	
	if ((*variable + adicion) < respaldo_variable)
		resultado = -1;
	
	return resultado;
}