/*
 * main_dda.c
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"


#ifndef FDDA_sim_on
 static struct data_task_0 metadatos;
#endif // FDDA_sim_on

void task_descarga(void *pvParameters){
#ifndef FDDA_sim_on
	//init_sim868();	
#endif // FDDA_sim_on

	while(1){
		#ifdef FDDA_sim_on
		 SimData_descarga();
		#else
		DELAY_MS(5000);
		#if PRUEBA_SIM868 == 1
			prueba_Ard_original();
		#else
		
		xQueuePeek(QueueHandle_metadatos, &metadatos, portMAX_DELAY); // Si no hay datos para enviar la tarea se bloquea.
		sendDataUSB(&metadatos);
		xQueueReset(QueueHandle_metadatos); // Eliminamos los datos enviados de la lista.
		
		#endif
		#endif // FDDA_sim_on
	}
}