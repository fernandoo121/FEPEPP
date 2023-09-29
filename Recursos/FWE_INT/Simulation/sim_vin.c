/*
 * sim_vin.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"

#ifdef FVIN_sim_on

 static struct data_task_3 vinculacion;

void SimData_vinculacion(){
	
	vinculacion.id_capataz = 1668942;
	
	vinculacion.tlm_[3] = 0b00010000;
	
	xQueueOverwrite(QueueHandle_vinculacion, &vinculacion); //Sobre escribimos los datos si tenemos una nueva vinculación.
	DELAY_MS(1000);
}

#endif // TASK_4_sim_on