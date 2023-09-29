/*
 * sim_dda.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"

#ifdef FDDA_sim_on

	static struct data_task_0 metadatos;

	unsigned char descarga_tlm_ = NOTHING;

void SimData_descarga(){
	
	#if SIMULAR_PROTOCOLO_DES_X_USB == 1 && SIMULAR_PROTOCOLO_COM_X_USB == 0
	unsigned char id_sim_task_comunicacion_USB = 0;
	#endif /* SIMULAR_PROTOCOLO_X_USB */
	
	#if SIMULAR_PROTOCOLO_COM_X_USB == 0 && SIMULAR_PROTOCOLO_DES_X_USB == 0
	 xQueuePeek(QueueHandle_metadatos, &metadatos, portMAX_DELAY); // Si no hay datos para enviar la tarea se bloquea.
	#endif

	#if METADATOS_AL_PUERTO_SERIAL == 1 && defined(DDA_)
	 descarga_tlm_ = 0b00000000;
	 metadatos_al_puerto_serial_ascii(&metadatos, NOTHING, NOTHING);
	 DELAY_MS(35);
	 descarga_tlm_ = 0b01100000;
	#endif /* METADATOS_AL_PUERTO_SERIAL */

	#if SIMULAR_PROTOCOLO_COM_X_USB == 1 && SIMULAR_PROTOCOLO_DES_X_USB == 1
	if (xQueuePeek(QueueHandle_metadatos, &metadatos, NOTHING) == pdTRUE)
	{
	#endif

		#if SIMULAR_PROTOCOLO_DES_X_USB == 1 && SIMULAR_PROTOCOLO_COM_X_USB == 0
		do{
			id_sim_task_comunicacion_USB = serialUSB_read_link();
		}while(id_sim_task_comunicacion_USB != '1');
		#endif /* SIMULAR_PROTOCOLO_X_USB */

		#if SIMULAR_PROTOCOLO_COM_X_USB == 1 && SIMULAR_PROTOCOLO_DES_X_USB == 0
		if (serialUSB_read_link() == 'T')
		xTaskNotifyGive(TaskHandle_comunicacion);
		#endif /* SIMULAR_PROTOCOLO_X_USB */

		#if SIMULAR_PROTOCOLO_COM_X_USB == 1 && SIMULAR_PROTOCOLO_DES_X_USB == 1
		do{
			id_sim_task_comunicacion_USB = serialUSB_read_link();
			if (id_sim_task_comunicacion_USB == 'T')
			xTaskNotifyGive(TaskHandle_comunicacion);
		}while(id_sim_task_comunicacion_USB != '1');
		#endif /* SIMULAR_PROTOCOLO_X_USB */
		
		xQueueReset(QueueHandle_metadatos);

		#if SIMULAR_PROTOCOLO_COM_X_USB == 1 || SIMULAR_PROTOCOLO_DES_X_USB == 1
		} else {
		#endif
		
		#if SIMULAR_PROTOCOLO_COM_X_USB == 1
		if (serialUSB_read_link() == 'T')
		xTaskNotifyGive(TaskHandle_comunicacion);
		#endif /* SIMULAR_PROTOCOLO_X_USB */

		#if SIMULAR_PROTOCOLO_COM_X_USB == 1 || SIMULAR_PROTOCOLO_DES_X_USB == 1
	}
	#endif
}

#endif // FDDA_sim_on



