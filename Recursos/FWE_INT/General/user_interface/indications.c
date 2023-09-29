/*
 * indications.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 
  /** Funciones para indicaciones operario **/
void flag_status_check(EventBits_t flag_indication, char id, unsigned char tipo_led, unsigned int pulso_led, unsigned int pulso_buzzer, char *mensaje);

// Define ejecucion indicación de falla al operario.
void ejecucion_indicaciones_operario(){
	
	EventBits_t indication_flags = NOTHING;
	
	indication_flags = xEventGroupWaitBits(EventGroup_indication, 3, pdFALSE, pdFALSE, NOTHING);
	
	#if METADATOS_AL_PUERTO_SERIAL == 1 || (RAW_TLM_TASK1_ENABLED == 1 && defined(raw_to_usb_____))
	 flag_status_check(indication_flags, ID_SD_MMC_FailureWarning_begin, LED_WARNING, 100, 100, NULL);
	 flag_status_check(indication_flags, ID_SD_MMC_FailureWarning_open, LED_WARNING, 100, 100, NULL);
	#else
	 flag_status_check(indication_flags, ID_SD_MMC_FailureWarning_begin, LED_WARNING, 100, 100, String_SD_MMC_FailureWarning_begin);
	 flag_status_check(indication_flags, ID_SD_MMC_FailureWarning_open, LED_WARNING, 100, 100, String_SD_MMC_FailureWarning_open);
	#endif /*METADATOS_AL_PUERTO_SERIAL == 1 || RAW_TLM_TASK1_ENABLED == 1*/
	
 	flag_status_check(indication_flags, ID_SPI_2_FailureWarning_master, LED_WARNING, 50, 100, String_SPI_2_FailureWarning_master);
 	flag_status_check(indication_flags, ID_SPI_2_FailureWarning_slave, LED_WARNING, 50, 100, String_SPI_2_FailureWarning_slave);
 	flag_status_check(indication_flags, ID_SPI_2_FailureWarning_slave, LED_WARNING, 50, 100, String_SPI_2_FailureWarning_indt);
	
	flag_status_check(indication_flags, ID_EsperaPorMetadatos, LED_DONE, 1000, NOTHING, NULL);
	flag_status_check(indication_flags, ID_RecepcionMetadatos, LED_DONE, 50, NOTHING, NULL);
	
}

// ...
void flag_status_check(EventBits_t flag_indication, char id, unsigned char tipo_led, unsigned int pulso_led, unsigned int pulso_buzzer, char *mensaje){
	
	if((flag_indication & (1 << id)) == (1 << id)){
		switch(tipo_led){
			case LED_DONE:		SET_indicacion_done_(id, pulso_led, pulso_buzzer, mensaje); break;
			case LED_WARNING:	SET_FailureWarning_(id, pulso_led, pulso_buzzer, mensaje); break;
		}
	} else {
		switch(tipo_led){
			case LED_DONE:		RST_indicacion_done_(id); break;
			case LED_WARNING:	RST_FailureWarning_(id); break;
		}
	}
}

// ...
void indicacion_prueba(){
	
	LED_DONE_HIGH;
	LED_WARNING_HIGH;
	LED_COM_HIGH;
	LED_GEO_HIGH;
	BUZZER_HIGH;
	DELAY_US(200*1000);
	
	LED_DONE_LOW;
	LED_WARNING_LOW;
	LED_COM_LOW;
	LED_GEO_LOW;
	BUZZER_LOW;
}

// Muestra indicación de falla al operario.
void indicacion_falla(char id, unsigned int pulso_led, unsigned int pulso_buzzer, char *mensaje){

	static char id_resp = NOTHING;	
	static unsigned long tiempo_ = NOTHING;
	
 	if((id_resp != id) && (pulso_led != NOTHING || pulso_buzzer != NOTHING || mensaje != NULL))
 		tiempo_ = NOTHING;
	
 	if(mensaje != NULL){
 		if ((CURRENT_TIME_MS - tiempo_) > 2000){
			serialUSB_print_link(mensaje);
 			tiempo_ = NOTHING;
 		}
		
 		if (tiempo_ == NOTHING)
 			tiempo_ = CURRENT_TIME_MS;
 	}

	if(pulso_led != NOTHING)
		LED_WARNING_TOGGLE_MS(pulso_led);
	else if(id_resp == id)
		LED_WARNING_LOW;
	
 	if (pulso_buzzer != NOTHING)
 		BUZZER_TOGGLE_MS(pulso_buzzer);
 	else if(id_resp == id)
 		BUZZER_LOW;
	
	if(pulso_led != NOTHING || pulso_buzzer != NOTHING || mensaje != NULL)	 
		id_resp = id;
}


// Muestra indicación de ok al operario.
void indicacion_done(char id, unsigned int pulso_led, unsigned int pulso_buzzer, char *mensaje){

	static char id_resp = NOTHING;
	static unsigned long tiempo_ = NOTHING;
	
	if((id_resp != id) && (pulso_led != NOTHING || pulso_buzzer != NOTHING || mensaje != NULL))
	tiempo_ = NOTHING;
	
	if(mensaje != NULL){
		if ((CURRENT_TIME_MS - tiempo_) > 2000){
			serialUSB_print_link(mensaje);
			tiempo_ = NOTHING;
		}
		
		if (tiempo_ == NOTHING)
		tiempo_ = CURRENT_TIME_MS;
	}

	if(pulso_led != NOTHING)
		LED_DONE_TOGGLE_MS(pulso_led);
	else if(id_resp == id)
		LED_DONE_LOW;
	
	if (pulso_buzzer != NOTHING)
		BUZZER_TOGGLE_MS(pulso_buzzer);
	else if(id_resp == id)
		BUZZER_LOW;
	
	if(pulso_led != NOTHING || pulso_buzzer != NOTHING || mensaje != NULL)
		id_resp = id;
}