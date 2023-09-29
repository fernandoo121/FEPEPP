/*
 * sim_fte.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 
#ifdef FFTE_sim_on

static struct data_task_4 fuente;

void SimData_fuente(){
	
	fuente.tlm_[0] = 0b00000010;
	
	xQueueOverwrite(QueueHandle_fuente, &fuente); //Sobre escribimos los datos si cambia el nivel de la batería.
	DELAY_MS(5000);

}

#endif // TASK_5_sim_on