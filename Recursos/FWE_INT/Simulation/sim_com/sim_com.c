/*
 * sim_com.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"

#ifdef FCOM_sim_on

 #define NUM_SPBP 1
 #define INTERVALO_OPP	3	// en segundos.
 
 static struct data_task_0 metadatos;

 unsigned int  sim_num_oprc[NUM_SPBP];

/* ... */
 void generacion_metadata(struct data_task_0 *metadatos, unsigned int sim_num_oprc, unsigned int id_electronica, unsigned int id_operario);

 void SimData_comunicacion(){
 	
	static unsigned int toggle_delay;
	
	if (toggle_delay == NOTHING)
		toggle_delay = CURRENT_TIME_MS;
	
	if (CURRENT_TIME_MS - toggle_delay > (INTERVALO_OPP*1000)){
		
		for (unsigned int spbp_ = 0; spbp_ < NUM_SPBP; spbp_++){
			generacion_metadata(&metadatos, ++sim_num_oprc[spbp_], (100 + spbp_), (spbp_ + 1));
			xQueueSend(QueueHandle_comunicacion, &metadatos, portMAX_DELAY); // Si la lista está llena no se autoriza recepción de más metadatos y la tarea se bloquea.
		}
		
		toggle_delay = NOTHING;
	}
	
	DELAY_MS(10);
 }

#endif // FCOM_sim_on