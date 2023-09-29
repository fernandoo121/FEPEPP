/*
 * main_pro.c	-	 Consult document  "Proyecto SARAPICO - Diseño/Procesamiento" https://trello.com/c/zyBfjxuQ)
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "pro_routines.h"

#ifndef FPRO_sim_on
 static struct data_task_0 metadatos;
#endif //FPRO_sim_on

void task_procesamiento(void *pvParameters){
#ifndef FPRO_sim_on

	void (*puntero_estadosFSM[NUM_ESTADOS])(struct data_task_0*) = {generacion_metadatos,
																    relevamiento_metadatos,
																    respaldo_metadatos,
																    recuperacion_metadatos};
	inicializar_fsm();
#if PRUEBA_SD_MMC == 1
	card_info(PIN_SD);
#endif /*PRUEBA_SD_MMC*/
#endif // TASK_0_sim_on

	while(1){
		#ifdef FPRO_sim_on
		 SimData_procesamiento();
		#else
			puntero_estadosFSM[estado_fsm_task_0](&metadatos);
		#endif // TASK_0_sim_on
	}
}