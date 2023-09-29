/*
 * main_com.c	-	 Consult document  "Proyecto SARAPICO - Diseño/Comunicación" https://trello.com/c/cctNNLu5)
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "slave_RF_operation.h"

#ifndef FCOM_sim_on
 static struct data_task_0 metadatos;
#endif //FCOM_sim_on

 void task_comunicacion(void *pvParameters){
#ifndef FCOM_sim_on

	init_cmt2300a();
	#if PRUEBA_CMT2300A == 1
	 prueba_cmt2300a();
	#endif
#else
	 DELAY_MS(5000);
#endif //FCOM_sim_on
   
	while(1){
		#ifdef FCOM_sim_on
		 SimData_comunicacion();
		#else
		
 		 while(resepcion_metadatos(&metadatos) != EXITO);
 		
 		 metadatos.solicitud_ = NADA_;
 		 xQueueSend(QueueHandle_comunicacion, &metadatos, portMAX_DELAY); // Si la lista está llena no se autoriza recepción de más metadatos y la tarea se bloquea.
		
		#endif // FCOM_sim_on
	}
 }