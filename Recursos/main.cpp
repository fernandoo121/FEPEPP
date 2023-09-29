/*
 * Proyecto Firmware Especializado para Puerta de Enlace de Picos Plantadores
 * Consult release_management.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"

TaskHandle_t	TaskHandle_procesamiento;
TaskHandle_t	TaskHandle_comunicacion;
TaskHandle_t	TaskHandle_descarga;
TaskHandle_t	TaskHandle_vinculacion;
TaskHandle_t	TaskHandle_fuente;

QueueHandle_t	QueueHandle_metadatos;
QueueHandle_t	QueueHandle_comunicacion;
QueueHandle_t	QueueHandle_vinculacion;
QueueHandle_t	QueueHandle_fuente;

EventGroupHandle_t EventGroup_indication;

#if DEPURACION_TASKx_ENABLED(1) || RAW_TLM_TASKx_ENABLED(state_)
char debug_string_[256];
#endif /* SIMULAR_PROTOCOLO_X_USB */

int main(void){
	
	samd21_init();
	indicacion_prueba();

	QueueHandle_metadatos			= xQueueCreate(QUEUE_LENG_metadatos, sizeof(data_task_0));
	QueueHandle_comunicacion		= xQueueCreate(QUEUE_LENG_metadatos, sizeof(data_task_0));
	QueueHandle_vinculacion			= xQueueCreate(QUEUE_LENG_vinculacion, sizeof(data_task_3));
	QueueHandle_fuente				= xQueueCreate(QUEUE_LENG_fuente, sizeof(data_task_4));

	EventGroup_indication			= xEventGroupCreate();
	
 	xTaskCreate(task_procesamiento, "task 0", TASK_STACK_LENG_procesamiento, NULL, TASK_STACK_PRIORITY_procesamiento, &TaskHandle_procesamiento);
 	xTaskCreate(task_comunicacion, "task 1", TASK_STACK_LENG_comunicacion, NULL, TASK_STACK_PRIORITY_comunicacion, &TaskHandle_comunicacion);
	xTaskCreate(task_descarga, "task 2", TASK_STACK_LENG_descarga, NULL, TASK_STACK_PRIORITY_descarga, &TaskHandle_descarga);
 	xTaskCreate(task_vinculacion, "task 3", TASK_STACK_LENG_vinculacion, NULL, TASK_STACK_PRIORITY_vinculacion, &TaskHandle_vinculacion);
 	xTaskCreate(task_fuente, "task 4", TASK_STACK_LENG_fuente, NULL, TASK_STACK_PRIORITY_fuente, &TaskHandle_fuente);
	
	vTaskStartScheduler();
	
	while(1);
	
}