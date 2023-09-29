/*
 * main_vin.c
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"

#ifndef FVIN_sim_on

#endif // FVIN_sim_on

void task_vinculacion(void *pvParameters){
	#ifndef FVIN_sim_on

	#endif // FVIN_sim_on
	while(1){
		#ifdef FVIN_sim_on
		SimData_vinculacion();
		#else
		// to define
		#endif // FVIN_sim_on
	}
}