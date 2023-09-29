/*
 * CFile1.c
 *
 * Created: 13/9/2023 10:22:21
 *  Author: Fernando
 */ 
#include "gateway.h"



void start(){
	
 	if(!NetworkConnected_link()){
 		DELAY_MS(500);
 		connect_gprs();
		serialUSB_print_link("");
 	}
 	if(!isMqttConnected_link()){
		 DELAY_MS(1000);
 		connect_mqtt();
	}
	
	send_data_link();
}

void prueba(){
	prueba_Ard_original();
	
	
	
// 	if(!isGprsConnected_link()){
// 		DELAY_MS(500);
// 		connect_gprs();
// 	}
// 	if(!isMqttConnected_link()){
// 		DELAY_MS(1000);
// 		connect_mqtt();
// 	}
// 	
// 	send_data_link();
}

void sendDataUSB(struct data_task_0 *metadatos){
	//unsigned char* dataPtr = (unsigned char*)&metadatos;
// 	for (int i = 0; i < sizeof(*metadatos); i++) {
// 		serialUSB_write_link(metadatos, sizeof(char)); // Enviar un byte a través de la comunicación serie
// 	}

	serialUSB_Ready_link(TRUE);
	
	// Fecha y hora
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR6_Pos], sizeof(unsigned	char));
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR5_Pos], sizeof(unsigned	char));
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR4_Pos], sizeof(unsigned	char));
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR3_Pos], sizeof(unsigned	char));
	
	// Datos operativa
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR2_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR1_Pos], sizeof(unsigned char));
		
	// Estado variables de interés
	serialUSB_write_link(&metadatos->data_oprc[DATA_OPRC_CAHR0_Pos], sizeof(unsigned char));
	
	// Datos funcionamiento electrónica
	serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR0_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR1_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR2_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR3_Pos], sizeof(unsigned char));
	//serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR4_Pos], sizeof(unsigned char));
	//serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR4_Pos], sizeof(unsigned char));
	//serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR4_Pos], sizeof(unsigned char));
	
	// Datos funcionamiento electrónica
	serialUSB_write_link(&metadatos->data_tlm[DATA_TLM_CAHR4_Pos], sizeof(unsigned char));
		
	// Identificación de la electrónica del sarapico
	serialUSB_write_link(&metadatos->id_spbp[ID_SPBP_CAHR3_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_spbp[ID_SPBP_CAHR2_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_spbp[ID_SPBP_CAHR1_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_spbp[ID_SPBP_CAHR0_Pos], sizeof(unsigned char));


	// Identificación del operario				
	serialUSB_write_link(&metadatos->id_oprr[ID_OPRR_CAHR4_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_oprr[ID_OPRR_CAHR3_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_oprr[ID_OPRR_CAHR2_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_oprr[ID_OPRR_CAHR1_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_oprr[ID_OPRR_CAHR0_Pos], sizeof(unsigned char));
	
	// Identificación de la electrónica de la Estación Base
	serialUSB_write_link(&metadatos->id_ebps[ID_EBPS_CAHR3_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_ebps[ID_EBPS_CAHR2_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_ebps[ID_EBPS_CAHR1_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_ebps[ID_EBPS_CAHR0_Pos], sizeof(unsigned char));
	
	// Identificación del capataz
	serialUSB_write_link(&metadatos->id_cdll[ID_CDLL_CAHR4_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_cdll[ID_CDLL_CAHR3_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_cdll[ID_CDLL_CAHR2_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_cdll[ID_CDLL_CAHR1_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->id_cdll[ID_CDLL_CAHR0_Pos], sizeof(unsigned char));
		
	// Datos en crudo GNSS
	serialUSB_write_link(&metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength1_Pos], sizeof(unsigned char));
	serialUSB_write_link(&metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength0_Pos], sizeof(unsigned char));
		
	for (short ind = DATA_RAW_GNSS_CAHRs_Leng; ind < SIZE_RAW_GNSS; ind++){
		serialUSB_write_link(&metadatos->raw_gnss[ind], sizeof(unsigned char));
	}
			
	
	
	
			
	
			
	

	
	DELAY_MS(5000);
}

