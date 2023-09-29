/*
 * user_interface.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef USER_INTERFACE_H_
#define USER_INTERFACE_H_

 /**
 ** REQUESTS 
 **/

 /* Codigos de solicitudes de usuario */
 #define NADA_ ' '	// Sin solicitud de usuario, se usa para relevar los datos de operación.
 #define VFSA_ '1'	// Volcado de metadata a puerto serial en formato legible ASCII.
 #define VFSH_ '2'	// Volcado de metadata a puerto serial en formato hexadecimal por caracteres ASCII.
 #define ECUF_ '3'	// Eliminacion de metadata.
 #define AHFS_ '4'	// Actualizacion hora y fecha del sistema.

 /* Enlace a funciones solicitudes de usuario */
#ifndef FPRO_sim_on
 #define VFSA_FUNCTION()	dump_file_SD_MMC(FALSE)
 #define VFSH_FUNCTION()	dump_file_SD_MMC(TRUE)
 #define ECUF_FUNCTION()	delete_file_SD_MMC()
#else
 #define VFSA_FUNCTION()	serialUSB_print_link("\n VFSA_FUNCTION")
 #define VFSH_FUNCTION()	serialUSB_print_link("\n VFSH_FUNCTION")
 #define ECUF_FUNCTION()	serialUSB_print_link("\n ECUF_FUNCTION")
#endif // FPRO_sim_on

 /**
  ** INDICATIONS
  **/

 /* Vector de indicaciones */
 enum indication_vector_ID{
	 ID_SD_MMC_FailureWarning_begin,
	 ID_SD_MMC_FailureWarning_open,
	 ID_I2C_1_FailureWarning_master,
	 ID_I2C_1_FailureWarning_slave,
	 ID_I2C_1_FailureWarning_indt,
	 ID_SPI_2_FailureWarning_master,
	 ID_SPI_2_FailureWarning_slave,
	 ID_SPI_2_FailureWarning_indt,
	 ID_RF_FailureWarning,
	 ID_IOT_FailureWarning,
	 ID_EsperaPorMetadatos,
	 ID_RecepcionMetadatos,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //ID_,
	 //// Maximo 24 IDs
 };

 /* Mensajes para indicaciones */
 #define String_SD_MMC_FailureWarning_begin	"\n\nADVERTENCIA Subsistema Procesamiento:" "\n\tSe registra falla en unidad flash (respaldo metadatos).\n"
 #define String_SD_MMC_FailureWarning_open	"\n\nADVERTENCIA Subsistema Procesamiento:" "\n\tNo se pudo abrir/crear archibo (respaldo metadatos).\n"
 #define String_SPI_2_FailureWarning_master	"\n\nADVERTENCIA Subsistema Comunicación:\n\tSe registra falla en bus SPI_2 (SERCOM no respondió).\n"
 #define String_SPI_2_FailureWarning_slave	"\n\nADVERTENCIA Subsistema Comunicación:\n\tSe registra falla en bus SPI_2 (ESCLAVO no respondió).\n"
 #define String_SPI_2_FailureWarning_indt	"\n\nADVERTENCIA Subsistema Comunicación:\n\tSe registra falla en bus SPI_2 (Sin rutina de mitigación).\n"
 #define String_RF_FailureWarning			"\n\nADVERTENCIA Subsistema Comunicación:\n\tSe registra falla en chip CMT2300.\n"

 /* Manejo de indicaciones */
 #define RST_indication_vector_(indication_vector_ID)	xEventGroupClearBits(EventGroup_indication, (1 << indication_vector_ID))
 #define SET_indication_vector_(indication_vector_ID)	xEventGroupSetBits(EventGroup_indication, (1 << indication_vector_ID))

 #define RST_FailureWarning_(indication_vector_ID)											indicacion_falla(indication_vector_ID, NOTHING, NOTHING, NULL)
 #define SET_FailureWarning_(indication_vector_ID, pulso_led_, pulso_buzzer_, mensaje_)		indicacion_falla(indication_vector_ID, pulso_led_, pulso_buzzer_, mensaje_)

 #define RST_indicacion_done_(indication_vector_ID)											indicacion_done(indication_vector_ID, NOTHING, NOTHING, NULL)
 #define SET_indicacion_done_(indication_vector_ID, pulso_led_, pulso_buzzer_, mensaje_)	indicacion_done(indication_vector_ID, pulso_led_, pulso_buzzer_, mensaje_)

#ifdef __cplusplus
extern "C" {
#endif
 
	/* REQUESTS */
	void capturar_solicitudes_usuario(char* solicitud_, QueueHandle_t QueueHandle_, const void * const struct_);
	void procesar_solicitudes_usuario(char* solicitud_);
	void ejecucion_indicaciones_operario();
 
	/*INDICATIONS*/
	void indicacion_prueba();
	void indicacion_falla(char id, unsigned int pulso_led, unsigned int pulso_buzzer, char *mensaje);
	void indicacion_done(char id, unsigned int pulso_led, unsigned int pulso_buzzer, char *mensaje);

#ifdef __cplusplus
}
#endif

#endif /* USER_INTERFACE_H_ */