/*
 * metadata.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 
  // ...
 void send_RAW_DATA(unsigned char* raw_data, unsigned int size_data);

/* 
 * Envía los metadatos con representación ASCII al puerto serial.
 */
void metadatos_al_puerto_serial_ascii(struct data_task_0 *metadatos, unsigned char intentos_envio_con, float intentos_envio_max){
	
	char string[256];
	
#if ESPERA_POR_SERIAL == 1 && defined(DDA_)
	serialUSB_Ready_link(TRUE);
#endif
	
#if CSV == 0 	
 	sprintf(string, "\nDATA_OPRC: \a%d/%d/%d %2d:%2d:%2d OPRC=%hu PT= %d FT= %d OR= %d MO= %d\r\n",
 				/*a7'a6'a5'a4'a3'a2*/	((metadatos->data_oprc[DATA_OPRC_CAHR6_Pos] >> 2) & 0b00111111) + rtc_compensation_reference_value,
 				/*m1'm0'm7'm6*/			((metadatos->data_oprc[DATA_OPRC_CAHR6_Pos] << 2) & 0b00001100) | ((metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] >> 6) & 0b00000011),
 				/*d5'd4'd3'd2'd1*/		((metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] >> 1) & 0b00011111),
 				/*h0'h7'h6'h5'h4*/		((metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] << 4) & 0b00010000) | ((metadatos->data_oprc[DATA_OPRC_CAHR4_Pos] >> 4) & 0b00001111),
 				/*m3'm2'm1'm0m7'm6*/	((metadatos->data_oprc[DATA_OPRC_CAHR4_Pos] << 2) & 0b00111100) | ((metadatos->data_oprc[DATA_OPRC_CAHR3_Pos] >> 6) & 0b00000011),
 				/*s5's4's3's2's1's0*/	((metadatos->data_oprc[DATA_OPRC_CAHR3_Pos] >> 0) & 0b00111111),
 				/*oh7'oh6'... 'ol0*/	((metadatos->data_oprc[DATA_OPRC_CAHR2_Pos] << 8) | (metadatos->data_oprc[DATA_OPRC_CAHR1_Pos] << 0)),
 				/*p7'p6*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 6) & 0b00000011),
 				/*f5'f4*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 4) & 0b00000011),
 				/*o5'o4*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 2) & 0b00000011),
 				/*m5'm4*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 0) & 0b00000011));
				
	serialUSB_print_link(string);
	
   	sprintf(string, "DATA_TLM (SPBP): RF = %d GNSS= %d RFID = %d FLASH = %d RTC = %d MODE = %d NBAT = %d%d\r\n",
									((metadatos->data_tlm[0] >> 7) & 0b00000001),
									((metadatos->data_tlm[0] >> 6) & 0b00000001),
  									((metadatos->data_tlm[0] >> 5) & 0b00000001),
  									((metadatos->data_tlm[0] >> 4) & 0b00000001),
  									((metadatos->data_tlm[0] >> 3) & 0b00000001),
  									((metadatos->data_tlm[0] >> 2) & 0b00000001),
									((metadatos->data_tlm[0] >> 1) & 0b00000001),
									((metadatos->data_tlm[0] >> 0) & 0b00000001));
  	serialUSB_print_link(string);
  	sprintf(string, "                 T_AC = %d ds (E = %d)\r\n",	
									((metadatos->data_tlm[1] >> 1) & 0b01111111),
  									((metadatos->data_tlm[1] >> 0) & 0b00000001));
	serialUSB_print_link(string);
	
  	sprintf(string, "                 D_PT = %d%d%d%d (I = %d) (O = %d%d) MO = %d\r\n", 
									((metadatos->data_tlm[2] >> 7) & 0b00000001),
									((metadatos->data_tlm[2] >> 6) & 0b00000001),
  									((metadatos->data_tlm[2] >> 5) & 0b00000001),
  									((metadatos->data_tlm[2] >> 4) & 0b00000001),
  									((metadatos->data_tlm[2] >> 3) & 0b00000001),
									((metadatos->data_tlm[3] >> 2) & 0b00000001),
									((metadatos->data_tlm[3] >> 1) & 0b00000001),
  									((metadatos->data_tlm[2] >> 0) & 0b00000001));
  	serialUSB_print_link(string);

  	sprintf(string, "                 D_FT = %d%d%d%d (I = %d) (O = %d%d) OR = %d\r\n", 
									((metadatos->data_tlm[3] >> 7) & 0b00000001),
									((metadatos->data_tlm[3] >> 6) & 0b00000001),
									((metadatos->data_tlm[3] >> 5) & 0b00000001),
									((metadatos->data_tlm[3] >> 4) & 0b00000001),
									((metadatos->data_tlm[3] >> 3) & 0b00000001),
									((metadatos->data_tlm[3] >> 2) & 0b00000001),
									((metadatos->data_tlm[3] >> 1) & 0b00000001),
									((metadatos->data_tlm[3] >> 0) & 0b00000001));
  	serialUSB_print_link(string);
	  
   	sprintf(string, "DATA_TLM (EBPS): RF = %d CEL= %d%d RFID = %d FLASH = %d MODE = %d NBAT = %d%d\r\n",
									((metadatos->data_tlm[4] >> 7) & 0b00000001),
									((metadatos->data_tlm[4] >> 6) & 0b00000001),
  									((metadatos->data_tlm[4] >> 5) & 0b00000001),
  									((metadatos->data_tlm[4] >> 4) & 0b00000001),
  									((metadatos->data_tlm[4] >> 3) & 0b00000001),
  									((metadatos->data_tlm[4] >> 2) & 0b00000001),
									((metadatos->data_tlm[4] >> 1) & 0b00000001),
									((metadatos->data_tlm[4] >> 0) & 0b00000001));
  	serialUSB_print_link(string); 	
	  
  	sprintf(string, "ID_SPBP: %u\r\n", ((metadatos->id_spbp[1] << 16 | metadatos->id_spbp[2] << 8 | metadatos->id_spbp[3] << 0) >> (24 - (metadatos->id_spbp[0]*8))));
  	serialUSB_print_link(string);
  	
  	sprintf(string, "ID_OPRR: %u\r\n", ((metadatos->id_oprr[1] << 24 | metadatos->id_oprr[2] << 16 | metadatos->id_oprr[3] << 8 | metadatos->id_oprr[4] << 0) >> (32 - (metadatos->id_oprr[0]*8))));
  	serialUSB_print_link(string);

  	sprintf(string, "ID_EBPS: %u\r\n", ((metadatos->id_ebps[1] << 16 | metadatos->id_ebps[2] << 8 | metadatos->id_ebps[3] << 0) >> (24 - (metadatos->id_ebps[0]*8))));
  	serialUSB_print_link(string);
  	
  	sprintf(string, "ID_CDLL: %u\r\n", ((metadatos->id_cdll[1] << 24 | metadatos->id_cdll[2] << 16 | metadatos->id_cdll[3] << 8 | metadatos->id_cdll[4] << 0) >> (32 - (metadatos->id_cdll[0]*8))));
  	serialUSB_print_link(string);
	  
	sprintf(string, "RAW_GNSS (%hu) 0x: \t", ((metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength1_Pos] << 8) | (metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength0_Pos] << 0)));
	serialUSB_print_link(string);

	#if ENVIAR_RAW_GNSS == 1
	 send_RAW_DATA(metadatos->raw_gnss, SIZE_RAW_GNSS);
	#endif /*ENVIAR_RAW_GNSS*/
	
	serialUSB_print_link("\r\v\n");
	
#else //CSV == 1

	 	sprintf(string, "%d/%d/%d;%d:%d:%d;%hu;%d;%d;%d;%d;",
	 			/*a7'a6'a5'a4'a3'a2*/	((metadatos->data_oprc[DATA_OPRC_CAHR6_Pos] >> 2) & 0b00111111) + rtc_compensation_reference_value,
	 			/*m1'm0'm7'm6*/			((metadatos->data_oprc[DATA_OPRC_CAHR6_Pos] << 2) & 0b00001100) | ((metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] >> 6) & 0b00000011),
	 			/*d5'd4'd3'd2'd1*/		((metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] >> 1) & 0b00011111),
	 			/*h0'h7'h6'h5'h4*/		((metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] << 4) & 0b00010000) | ((metadatos->data_oprc[DATA_OPRC_CAHR4_Pos] >> 4) & 0b00001111),
	 			/*m3'm2'm1'm0m7'm6*/	((metadatos->data_oprc[DATA_OPRC_CAHR4_Pos] << 2) & 0b00111100) | ((metadatos->data_oprc[DATA_OPRC_CAHR3_Pos] >> 6) & 0b00000011),
	 			/*s5's4's3's2's1's0*/	((metadatos->data_oprc[DATA_OPRC_CAHR3_Pos] >> 0) & 0b00111111),
	 			/*oh7'oh6'... 'ol0*/	((metadatos->data_oprc[DATA_OPRC_CAHR2_Pos] << 8) | (metadatos->data_oprc[DATA_OPRC_CAHR1_Pos] << 0)),
	 			/*p7'p6*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 6) & 0b00000011),
	 			/*f5'f4*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 4) & 0b00000011),
	 			/*o5'o4*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 2) & 0b00000011),
	 			/*m5'm4*/				((metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] >> 0) & 0b00000011));
				 
	serialUSB_print_link(string);

// 	sprintf(string, "%d %d %d %d %d %d %d%d",
	sprintf(string, "%d - - %d - %d %d%d",	
									((metadatos->data_tlm[0] >> 7) & 0b00000001),
									/*((metadatos->data_tlm[0] >> 6) & 0b00000001),*/
									/*((metadatos->data_tlm[0] >> 5) & 0b00000001),*/
									((metadatos->data_tlm[0] >> 4) & 0b00000001),
									/*((metadatos->data_tlm[0] >> 3) & 0b00000001),*/
									((metadatos->data_tlm[0] >> 2) & 0b00000001),
									((metadatos->data_tlm[0] >> 1) & 0b00000001),
									((metadatos->data_tlm[0] >> 0) & 0b00000001));
	serialUSB_print_link(string);
	
  	sprintf(string, " %d%d%d%d%d%d%d %d",((metadatos->data_tlm[1] >> 7) & 0b00000001),
  										((metadatos->data_tlm[1] >> 6) & 0b00000001),
										((metadatos->data_tlm[1] >> 5) & 0b00000001),
  										((metadatos->data_tlm[1] >> 4) & 0b00000001),
										((metadatos->data_tlm[1] >> 3) & 0b00000001),
  										((metadatos->data_tlm[1] >> 2) & 0b00000001),
  										((metadatos->data_tlm[1] >> 1) & 0b00000001),
  										((metadatos->data_tlm[1] >> 0) & 0b00000001));
	serialUSB_print_link(string);

	sprintf(string, " %d%d%d%d %d %d%d %d", 
									((metadatos->data_tlm[2] >> 7) & 0b00000001),
									((metadatos->data_tlm[2] >> 6) & 0b00000001),
  									((metadatos->data_tlm[2] >> 5) & 0b00000001),
  									((metadatos->data_tlm[2] >> 4) & 0b00000001),
  									((metadatos->data_tlm[2] >> 3) & 0b00000001),
									((metadatos->data_tlm[2] >> 2) & 0b00000001),
									((metadatos->data_tlm[2] >> 1) & 0b00000001),
  									((metadatos->data_tlm[2] >> 0) & 0b00000001));
  	serialUSB_print_link(string);
	  
  	sprintf(string, " %d%d%d%d %d %d%d %d;", 
									((metadatos->data_tlm[3] >> 7) & 0b00000001),
									((metadatos->data_tlm[3] >> 6) & 0b00000001),
									((metadatos->data_tlm[3] >> 5) & 0b00000001),
									((metadatos->data_tlm[3] >> 4) & 0b00000001),
									((metadatos->data_tlm[3] >> 3) & 0b00000001),
									((metadatos->data_tlm[3] >> 2) & 0b00000001),
									((metadatos->data_tlm[3] >> 1) & 0b00000001),
									((metadatos->data_tlm[3] >> 0) & 0b00000001));
  	serialUSB_print_link(string); 

   	//sprintf(string, "%d %d%d %d %d %d %d%d %3d %3.0lf;",
	sprintf(string, "%d %d%d - %d %d %d%d",
											((metadatos->data_tlm[4] >> 7) & 0b00000001),
											((metadatos->data_tlm[4] >> 6) & 0b00000001),
											((metadatos->data_tlm[4] >> 5) & 0b00000001),
											/*((metadatos->data_tlm[4] >> 4) & 0b00000001),*/
											((metadatos->data_tlm[4] >> 3) & 0b00000001),
											((metadatos->data_tlm[4] >> 2) & 0b00000001),
											((metadatos->data_tlm[4] >> 1) & 0b00000001),
											((metadatos->data_tlm[4] >> 0) & 0b00000001));								
  	serialUSB_print_link(string);
	  
	if (intentos_envio_max != NOTHING)
		sprintf(string, " %3d %3.0lf;", intentos_envio_con, intentos_envio_max); //TLM live subsistema comunicación ...									
	else
		sprintf(string, "   0   0;");
	serialUSB_print_link(string);
	    	
  	sprintf(string, "%d;", (metadatos->id_spbp[1] << 16 | metadatos->id_spbp[2] << 8 | metadatos->id_spbp[3] << 0) >> (24 - (metadatos->id_spbp[0]*8)));
  	serialUSB_print_link(string);
  	
  	sprintf(string, "%d;", ((metadatos->id_oprr[1] << 24 | metadatos->id_oprr[2] << 16 | metadatos->id_oprr[3] << 8 | metadatos->id_oprr[4] << 0) >> (32 - (metadatos->id_oprr[0]*8))));
  	serialUSB_print_link(string);

  	sprintf(string, "%d;", ((metadatos->id_ebps[1] << 16 | metadatos->id_ebps[2] << 8 | metadatos->id_ebps[3] << 0) >> (24 - (metadatos->id_ebps[0]*8))));
  	serialUSB_print_link(string);
  	
  	sprintf(string, "%d;", ((metadatos->id_cdll[1] << 24 | metadatos->id_cdll[2] << 16 | metadatos->id_cdll[3] << 8 | metadatos->id_cdll[4] << 0) >> (32 - (metadatos->id_cdll[0]*8))));
  	serialUSB_print_link(string);
  		
	sprintf(string, "(%hu) 0x: ", ((metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength1_Pos] << 8) | (metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength0_Pos] << 0)));
	serialUSB_print_link(string);

	#if ENVIAR_RAW_GNSS == 1
	send_RAW_DATA(metadatos->raw_gnss, SIZE_RAW_GNSS);
	#endif /*ENVIAR_RAW_GNSS*/
	
 	serialUSB_print_link("\n");
#endif /*CSV*/
}

/*
 * Envía los metadatos con representación Hexadecimal al puerto serial.
 */
void metadatos_al_puerto_serial_hexa(struct data_task_0 *metadatos){

	send_RAW_DATA(metadatos->data_oprc, SIZE_DATA_OPRC);
	send_RAW_DATA(metadatos->data_tlm, SIZE_DATA_TLM);
	send_RAW_DATA(metadatos->id_spbp, SIZE_ID_SPBP);
	send_RAW_DATA(metadatos->id_oprr, SIZE_ID_OPRR);

	#if ENVIAR_RAW_GNSS == 1
	send_RAW_DATA(metadatos->raw_gnss, SIZE_RAW_GNSS);
	#endif /*ENVIAR_RAW_GNSS*/
	
	serialUSB_print_link("\n");
}

 /*
  * ...
  */
void corrupcion_metadatos_unidad(struct data_task_0 *metadatos){
#warning "mitigacion de corrupcion de metadatos sin implementar"

	unsigned long tiempo_ = NOTHING;

	while(1){
		
		if (tiempo_ == NOTHING || ((CURRENT_TIME_MS - tiempo_) > 10000 && serialUSB_Ready_link(FALSE))){
			serialUSB_print_link("\n\n FALLA Subsistema Procesamiento:" "\n\t Metadatos dañados (respaldo metadatos).\n");
			serialUSB_print_link("\t Mitigacion de corrupcion de metadatos en unidad sin implementar.\n");
			serialUSB_print_link("\t Ejecute los comandos para respaldar y eliminar los metadatos. "
									"Caso no se solucione el problema, formatee la unidad.\n\n");
			tiempo_ = NOTHING;
		}
		
		if (tiempo_ == NOTHING && serialUSB_Ready_link(FALSE))
			tiempo_ = CURRENT_TIME_MS;
		
		LED_WARNING_TOGGLE;
		LED_DONE_TOGGLE;
		LED_COM_TOGGLE;
		LED_GEO_TOGGLE;
		BUZZER_TOGGLE;
		DELAY_MS(500);
		
	}
}

//------------------------------------------------------------------
void send_RAW_DATA(unsigned char* raw_data, unsigned int size_data){
	
	char string[10];
	
	for (short ind = 2; ind < size_data; ind++){
		if (raw_data[ind] > 0xF)
			sprintf(string, "%X", raw_data[ind]);
		else
			sprintf(string, "0%X", raw_data[ind]);
		
		serialUSB_print_link(string);
	}
}