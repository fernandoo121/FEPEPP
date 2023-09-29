/*
 * main_fte.c
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"

#ifndef FFTE_sim_on

#endif // TASK_5_sim_on

void task_fuente(void *pvParameters){
#ifndef FFTE_sim_on

#endif // TASK_5_sim_on
	while(1){
		#ifdef FFTE_sim_on
		SimData_fuente();
		#else
			// to define
		#endif // TASK_5_sim_on
	}
}