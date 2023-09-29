/*
 * acciones_protocolo.c
 *
 * Created: 25/1/2023 16:46:33
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "gateway_portable.h"
 #include "slave_RF_operation.h"
 
 #if CAPTURAR_CRC_FAIL == 1
  unsigned char comunicacion_tlm_ = NOTHING;
 #endif
 
 /*
  * Sga. ?
  * Bloquea la tarea hasta se detecte actividad en el canal o se llegue al tiempo de espera dado.
  */
 #define TERNARIO_ESPERA_NOTIFICACION()		(estado_canal_ == FALSE ? pdMS_TO_TICKS(TIEMPO_ESPARA_SOLICITUD_USUARI)/*portMAX_DELAY*/ : pdMS_TO_TICKS(espera_))
 char escucha_canal_ms(unsigned long espera_, unsigned char estado_canal_){
	
	char result_;
	
#if SIMULAR_PROTOCOLO_COM_X_USB == 0
	
	go_stby();
	clear_interrupt_flags();
	
 #if CAPTURAR_CRC_FAIL == 1
	switch_interruption(INT_SEL_PKT_OK);
 #else
	switch_interruption(INT_SEL_CRC_OK);
 #endif
		
 #if SIZE_ASK == 0	
 	ack_packet_format(FALSE);
 #endif /* SIZE_ASK */

 #if PKT_TYPE_VALUE == 1
	packet_length(SIZE_TRAMA);
 #endif

	enable_read_fifo();
	clear_rx_fifo();	// Must clear FIFO after enable SPI to read or write the FIFO
	
	ICR_ENABLE_gpio3();
	go_rx();
	
#endif /* SIMULAR_PROTOCOLO_X_USB */
 
#if CAPTURAR_CRC_FAIL == 1
 retry:
#endif
	result_ = ulTaskNotifyTake(pdTRUE, TERNARIO_ESPERA_NOTIFICACION());  //Espera por CRC_OK (CAPTURAR_CRC_FAIL == 0) 

	if(result_ > 0){
#if CAPTURAR_CRC_FAIL == 1
		if(interrupt_check(MASK_CRC_OK_FLG)){
			comunicacion_tlm_ = 0b00000000;
 			RST_indication_vector_(ID_EsperaPorMetadatos);
 			SET_indication_vector_(ID_RecepcionMetadatos);
			return SI;
		} else {
			clear_interrupt_flags();
			
			#if RAW_TLM_TASK1_ENABLED == 1
				//declaración opcional
			#else
			 #if DEPURACION_TASK1_ENABLED == 1
			  serialUSB_print_link("RUIDO EN EL CANAL :::\n"); /* DEBUGGING */
			 #else
			  //RF_CRC_FailureWarning_;
			 #endif /*DEPURACION_TASKx_ENABLED*/
			#endif /*RAW_TLM_TASKx_ENABLED*/
			
			comunicacion_tlm_ = 0b10000000;
			
			ICR_ENABLE_gpio3();
			goto retry;
		}
#else 

 		RST_indication_vector_(ID_EsperaPorMetadatos);
 		SET_indication_vector_(ID_RecepcionMetadatos);
		return SI;
#endif
	} else{
		SET_indication_vector_(ID_EsperaPorMetadatos);
		RST_indication_vector_(ID_RecepcionMetadatos);
		return NO;
	}
 }
 
/*
 * Sga. ?
 * Releva al módulo de radiofrecuencia los bytes de ASK.
 */
 void envio_ask(unsigned char* ask){
#if SIMULAR_PROTOCOLO_COM_X_USB == 1
	serialUSB_print_link("\nASK");
#else

	char result_TaskNotify;

	go_stby();
	clear_interrupt_flags();
	switch_interruption(INT_SEL_TX_DONE);
	
#if SIZE_ASK == 0	
 	ack_packet_format(TRUE); 
#else
	
#if PKT_TYPE_VALUE == 1
	packet_length(SIZE_ASK);
#endif
	
	enable_write_fifo();
	clear_tx_fifo(); // Must clear FIFO after enable SPI to read or write the FIFO

	marco_escritura_FIFO(ask, SIZE_ASK); // Write while we send

#endif /* SIZE_ASK */
	
	DELAY_US(2*(t_rx * 1000)); // Retraso para asegurar que el sarapico esta en modo rx.
	
	ICR_ENABLE_gpio3(); 
	go_tx();

	result_TaskNotify = ulTaskNotifyTake(pdTRUE, (t_trama *2)); //Espera por TX_DONE
	
	if(result_TaskNotify == 0){
		//goto espera_superada;
		
		#if RAW_TLM_TASK1_ENABLED == 1
			//declaración opcional
		#else
			#if DEPURACION_TASK1_ENABLED == 1
			serialUSB_print_link("ModemRF TX_DONE FAILURE ::::::::::::::::::: \n"); /* DEBUGGING */
			#endif /*DEPURACION_TASKx_ENABLED*/
		#endif /*RAW_TLM_TASKx_ENABLED*/
	}

	//RST_RecepcionMetadatos;
#endif /* SIMULAR_PROTOCOLO_X_USB */
}

 /*
  * Sga. ?
  * Solicita al módulo de radiofrecuencia los bytes de trama recibidos.
  */
void actividad_canal(unsigned char* trama_){

 #if SIMULAR_PROTOCOLO_COM_X_USB == 1
	unsigned char buffer_[SIZE_TRAMA*2];
	
	serialUSB_readBytes_link(buffer_, SIZE_TRAMA*2);
	

	for (int i = 0, i2 = 0; i < SIZE_TRAMA*2; i += 2 ,i2++){
		 switch(buffer_[i]){
			 case ' ':
			 case '0': trama_[i2] = 0x0 << 4; break;
			 case '1': trama_[i2] = 0x1 << 4; break;
			 case '2': trama_[i2] = 0x2 << 4; break;
			 case '3': trama_[i2] = 0x3 << 4; break;
			 case '4': trama_[i2] = 0x4 << 4; break;
			 case '5': trama_[i2] = 0x5 << 4; break;
			 case '6': trama_[i2] = 0x6 << 4; break;
			 case '7': trama_[i2] = 0x7 << 4; break;
			 case '8': trama_[i2] = 0x8 << 4; break;
			 case '9': trama_[i2] = 0x9 << 4; break;
			 case 'a': trama_[i2] = 0xa << 4; break;
			 case 'b': trama_[i2] = 0xb << 4; break;
			 case 'c': trama_[i2] = 0xc << 4; break;
			 case 'd': trama_[i2] = 0xd << 4; break;
			 case 'e': trama_[i2] = 0xe << 4; break;
			 case 'f': trama_[i2] = 0xf << 4; break;
		 }
		 
		 switch(buffer_[i + 1]){
			 case '0': trama_[i2] |= 0x0; break;
			 case '1': trama_[i2] |= 0x1; break;
			 case '2': trama_[i2] |= 0x2; break;
			 case '3': trama_[i2] |= 0x3; break;
			 case '4': trama_[i2] |= 0x4; break;
			 case '5': trama_[i2] |= 0x5; break;
			 case '6': trama_[i2] |= 0x6; break;
			 case '7': trama_[i2] |= 0x7; break;
			 case '8': trama_[i2] |= 0x8; break;
			 case '9': trama_[i2] |= 0x9; break;
			 case 'a': trama_[i2] |= 0xa; break;
			 case 'b': trama_[i2] |= 0xb; break;
			 case 'c': trama_[i2] |= 0xc; break;
			 case 'd': trama_[i2] |= 0xd; break;
			 case 'e': trama_[i2] |= 0xe; break;
			 case 'f': trama_[i2] |= 0xf; break;
		 }
	 }

 #else
	marco_lectura_FIFO(trama_, SIZE_TRAMA);
 #endif /* SIMULAR_PROTOCOLO_X_USB */
}

/* 
 * Sga. N/A (funcion de soporte)
 * Pone al hardware en modo ahorro de enerjia.
 */ 
void dormir_hardware_rf(){
	go_sleep();
}

 /* 
  * Sga. N/A (funcion de soporte)
  * Descarta la actividad almacenada en buffer.
  */ 
void descartar_actividad(){
 #if SIMULAR_PROTOCOLO_COM_X_USB == 1
 	while(serialUSB_available_link() > 0)
 		serialUSB_read_link();
 #endif /* SIMULAR_PROTOCOLO_X_USB */
}

/* 
 * Sga. N/A (funcion de soporte)
 * Envía las tramas con representación ASCII al puerto serial.
 */
#if TRAMAS_COM_AL_PUERTO_SERIAL == 1 && METADATOS_AL_PUERTO_SERIAL == 0
#include <string.h>
#define CSV 1	//tipo presentacion de datos
#warning "TRAMAS_COM_AL_PUERTO_SERIAL = 1"

void tramas_al_puerto_serial(unsigned char* trama_){
	
	 char string_[256];
	 
	 serialUSB_Ready_link(TRUE);

	 sprintf(string_, "\nTrama %d (%c)", trama_[ID_TRAMA_NUM_pos] , trama_[ID_TRAMA_TIPO_pos]);
	 serialUSB_print_link(string_);
	  
	 if (trama_[ID_TRAMA_TIPO_pos] == 'S'){
#if TRAMAS_COM_TIPO_HEXA_ == 0
#if CSV == 0 
		 sprintf(string_, "DATA_OPRC: %d/%d/%d %d:%d:%d OPRC=%hu PT= %d FT= %d OR= %d MO= %d\r\n",
		 /*a7'a6'a5'a4'a3'a2*/	((trama_[0 + METADATOS_pos] >> 2) & 0b00111111) + RTC_COMPENSATION_REFERENCE_VALUE,
		 /*m1'm0'm7'm6*/		((trama_[0 + METADATOS_pos] << 2) & 0b00001100) | ((trama_[1 + METADATOS_pos] >> 6) & 0b00000011),
		 /*d5'd4'd3'd2'd1*/		((trama_[1 + METADATOS_pos] >> 1) & 0b00011111),
		 /*h0'h7'h6'h5'h4*/		((trama_[1 + METADATOS_pos] << 4) & 0b00010000) | ((trama_[2 + METADATOS_pos] >> 4) & 0b00001111),
		 /*m3'm2'm1'm0m7'm6*/	((trama_[2 + METADATOS_pos] << 2) & 0b00111100) | ((trama_[3 + METADATOS_pos] >> 6) & 0b00000011),
		 /*s5's4's3's2's1's0*/	((trama_[3 + METADATOS_pos] >> 0) & 0b00111111),
		 /*oh7'oh6'... 'ol0*/	((trama_[4 + METADATOS_pos] << 8) | (trama_[5 + METADATOS_pos] << 0)),
		 /*p7'p6*/				((trama_[6 + METADATOS_pos] >> 6) & 0b00000011),
		 /*f5'f4*/				((trama_[6 + METADATOS_pos] >> 4) & 0b00000011),
		 /*o5'o4*/				((trama_[6 + METADATOS_pos] >> 2) & 0b00000011),
		 /*m5'm4*/				((trama_[6 + METADATOS_pos] >> 0) & 0b00000011));

		 serialUSB_print_link(string_);
		 
		 sprintf(string_, "DATA_TLM: RF = %d GNSS= %d RFID = %d FLASH = %d RTC = %d\n\t   MODE = %d NBAT = %d%d\r\n",
		 ((trama_[0 + 7 + METADATOS_pos] >> 7) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 6) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 5) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 4) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 3) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 2) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 1) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 0) & 0b00000001));
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, "DATA_TLM: D_PT = %d%d (I = %d) D_FT = %d%d (I = %d)\r\n", ((trama_[2 + 7 + METADATOS_pos] >> 5) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 4) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 3) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 2) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 1) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 0) & 0b00000001));
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, "ID_SPBP (%d): %u\r\n", trama_[0 + 10 + METADATOS_pos], trama_[1 + 10 + METADATOS_pos]);
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, "ID_OPRR (%d): %u\r\n", trama_[0 + 12 + METADATOS_pos], (trama_[1 + 12 + METADATOS_pos] << 16 | trama_[2 + 12 + METADATOS_pos] << 8 | trama_[3 + 12 + METADATOS_pos]));
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, "RAW_GNSS (%d): ", (trama_[0 + 16 + METADATOS_pos] << 8 | trama_[1 + 16 + METADATOS_pos]));
		 serialUSB_print_link(string_);
		 
		 for (short ind = (2 + 16 + METADATOS_pos); ind < SIZE_TRAMA; ind++){
			 sprintf(string_, " %d", trama_[ind]);
			 //serialUSB_print_link(string_);
		 }
#else
		 sprintf(string_, "%d/%d/%d %d:%d:%d;%5hu;%d;%d;%d;%d ",
		 /*a7'a6'a5'a4'a3'a2*/	((trama_[0 + METADATOS_pos] >> 2) & 0b00111111) + RTC_COMPENSATION_REFERENCE_VALUE,
		 /*m1'm0'm7'm6*/		((trama_[0 + METADATOS_pos] << 2) & 0b00001100) | ((trama_[1 + METADATOS_pos] >> 6) & 0b00000011),
		 /*d5'd4'd3'd2'd1*/		((trama_[1 + METADATOS_pos] >> 1) & 0b00011111),
		 /*h0'h7'h6'h5'h4*/		((trama_[1 + METADATOS_pos] << 4) & 0b00010000) | ((trama_[2 + METADATOS_pos] >> 4) & 0b00001111),
		 /*m3'm2'm1'm0m7'm6*/	((trama_[2 + METADATOS_pos] << 2) & 0b00111100) | ((trama_[3 + METADATOS_pos] >> 6) & 0b00000011),
		 /*s5's4's3's2's1's0*/	((trama_[3 + METADATOS_pos] >> 0) & 0b00111111),
		 /*oh7'oh6'... 'ol0*/	((trama_[4 + METADATOS_pos] << 8) | (trama_[5 + METADATOS_pos] << 0)),
		 /*p7'p6*/				((trama_[6 + METADATOS_pos] >> 6) & 0b00000011),
		 /*f5'f4*/				((trama_[6 + METADATOS_pos] >> 4) & 0b00000011),
		 /*o5'o4*/				((trama_[6 + METADATOS_pos] >> 2) & 0b00000011),
		 /*m5'm4*/				((trama_[6 + METADATOS_pos] >> 0) & 0b00000011));

		 serialUSB_print_link(string_);
		 
		 sprintf(string_, ";%d %d %d %d %d %d %d%d",
		 ((trama_[0 + 7 + METADATOS_pos] >> 7) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 6) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 5) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 4) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 3) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 2) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 1) & 0b00000001),
		 ((trama_[0 + 7 + METADATOS_pos] >> 0) & 0b00000001));
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, " %d%d %d %d%d %d;", ((trama_[2 + 7 + 2] >> 5) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 4) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 3) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 2) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 1) & 0b00000001),
		 ((trama_[2 + 7 + METADATOS_pos] >> 0) & 0b00000001));		 
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, " %u;", trama_[1 + 10 + METADATOS_pos]);
		 serialUSB_print_link(string_);
		 
		 sprintf(string_, " %u;", (trama_[1 + 12 + METADATOS_pos] << 16 | trama_[2 + 12 + METADATOS_pos] << 8 | trama_[3 + 12 + METADATOS_pos]));
		 serialUSB_print_link(string_);
		 
		 for (short ind = (2 + 16 + METADATOS_pos); ind < SIZE_TRAMA; ind++){
			 sprintf(string_, " %d", trama_[ind]);
			 //serialUSB_print_link(string_);
		 }
#endif /* CSV */
#else
		 serialUSB_print_link("{");
			 for (short ind = 0; ind < SIZE_TRAMA; ind++){
				 sprintf(string_, "0x%2x, ", trama_[ind]);
				 serialUSB_print_link(string_);
			 }
		 serialUSB_print_link("}");
#endif
	 
	 } else{
#if TRAMAS_COM_TIPO_HEXA_ == 0
		 for (short ind = METADATOS_pos; ind < SIZE_TRAMA; ind++){
			 sprintf(string_, "% d", trama_[ind]);
			 //serialUSB_print_link(string_);
		 }
#else
		 serialUSB_print_link("{");
			 for (short ind = METADATOS_pos; ind < SIZE_TRAMA; ind++){
				 sprintf(string_, "0x%2x, ", trama_[ind]);
				 serialUSB_print_link(string_);
			 }
		 serialUSB_print_link("}");
#endif
	 }
	 /*serialUSB_print_link("\n");*/
}
#endif /* TRAMAS_COM_AL_PUERTO_SERIAL */
