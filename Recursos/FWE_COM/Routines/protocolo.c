/*
 * protocolo.c
 *
 * Created: 25/1/2023 15:33:00
 * Author : Andres Mezquida
 */

/*
 * Esta rutina secundaria se encarga de la ejecución del 
 * protocolo de comunicación para la resepción de todas las tramas 
 * derivadas de los metadatos asociados a una operación con SPBP.
 * 
 */

 #include "gateway.h"
 #include "com_routines.h"

 unsigned char estado_fsm_protocolo;
  
 unsigned char num_trama_anterior;
  
 char espera_recepcion_consumidas = NOTHING;
 char resultado_disponible = FALSE;
 unsigned char estado_canal = LIBRE;
 char resultado = -1;
 
#if METADATOS_AL_PUERTO_SERIAL == 1
 unsigned char espera_recepcion_live_tlm = 0;
#endif /* METADATOS_AL_PUERTO_SERIAL */

 void ask_rst(unsigned char* ask);
 
char resepcion_trama(unsigned char* trama_){

#if SIMULAR_PROTOCOLO_COM_X_USB == 1
	 serialUSB_Ready_link(TRUE);
	 #warning "Entrda protocolo comunicacion por serialUSB"
#endif /* SIMULAR_PROTOCOLO_X_USB */
		
 	while(1){
	 	switch (estado_fsm_protocolo){
		 	case VERIFICACION:		verificacion(trama_);	break;
		 	case RELEVAMIENTO:		relevamiento(trama_);	break;
		 	case ASIGNACION_CANAL:	asignacion_canal();		break;
		 	case ESPERA:			espera();				break;
	 	}
	 
	 	if (resultado_disponible == TRUE){
		 	resultado_disponible = FALSE;

			#if RAW_TLM_TASK1_ENABLED == 1
			 if (resultado == EXITO){
			  sprintf(debug_string_, "EXITO; espera_recepcion_consumidas; %d\n", espera_recepcion_consumidas);
			  serialUSB_print_link(debug_string_); /* DEBUGGING */
			 }
			#else
			 #if DEPURACION_TASK1_ENABLED == 1
			 switch(resultado){  /* DEBUGGING */
				case FRACASO: 	serialUSB_print_link("\n protocolo EBPS:: FRACASO\n\n"); break; /**/
				case EXITO:		serialUSB_print_link("\n protocolo EBPS:: EXITO\n\n");	break; /**/
			 }
			 #endif /*DEPURACION_TASKx_ENABLED*/
			#endif /*RAW_TLM_TASKx_ENABLED*/	
		 	return resultado;
	 	}
 	}
	
	return -1;
 }
 
 /* 
 * Definida para ejecutar acción “Escucha (2Tt)” y decisión “Recepción trama?” y “Canal asignado?” (Figura 4).
 *
 * #0
 * Entrada:	Desde #RST/1/2/3
 * Accion:	Consultar documento
 * Salida:  Recepción trama = SI | (Recepción trama = NO && Canal asignado = SI)
 *
 */
 void verificacion(unsigned char* trama_){
	 
	if (escucha_canal_ms(2*ESPERA_Tt, estado_canal) == SI){
					
		actividad_canal(trama_);
		
		#if RAW_TLM_TASK1_ENABLED == 1
			//declaración opcional
		#else
		 #if DEPURACION_TASK1_ENABLED == 1
		 sprintf(debug_string_, "\nTrama %d (%c) ", trama_[ID_TRAMA_NUM_pos] , trama_[ID_TRAMA_TIPO_pos]);
		 serialUSB_print_link(debug_string_); /* DEBUGGING */
		 #endif /*DEPURACION_TASKx_ENABLED*/
		#endif /*RAW_TLM_TASKx_ENABLED*/
		
		#if TRAMAS_COM_AL_PUERTO_SERIAL == 1 && METADATOS_AL_PUERTO_SERIAL == 0
		 tramas_al_puerto_serial(trama_);
		#endif /* TRAMAS_AL_PUERTO_SERIAL */
		
		if (trama_[ID_TRAMA_TIPO_pos] == TRAMA_INICIAL){
			#if RAW_TLM_TASK1_ENABLED == 1
				//declaración opcional
			#else
			 #if DEPURACION_TASK1_ENABLED == 1
			 if (estado_canal == LIBRE)
				serialUSB_print_link("RECIBIDA\n"); /* DEBUGGING */
			 else
				serialUSB_print_link("DESCARTADA\n"); /* DEBUGGING */
			 #endif /*DEPURACION_TASKx_ENABLED*/
			#endif /*RAW_TLM_TASKx_ENABLED*/	
			estado_fsm_protocolo = ASIGNACION_CANAL;	
		}else if(trama_[ID_TRAMA_TIPO_pos] == TRAMA_INTERMEDIA || trama_[ID_TRAMA_TIPO_pos] == TRAMA_FINAL){
			
			if (estado_canal == ASIGNADO){	
				#if RAW_TLM_TASK1_ENABLED == 1
					//declaración opcional
				#else
				 #if DEPURACION_TASK1_ENABLED == 1
				  serialUSB_print_link("RECIBIDA\n"); /* DEBUGGING */
				 #endif /*DEPURACION_TASKx_ENABLED*/
				#endif /*RAW_TLM_TASKx_ENABLED*/				
				estado_fsm_protocolo = RELEVAMIENTO;
			}else{		
				#if RAW_TLM_TASK1_ENABLED == 1
					//declaración opcional
				#else
				 #if DEPURACION_TASK1_ENABLED == 1
				  serialUSB_print_link("DESCARTADA\n"); /* DEBUGGING */
				 #endif /*DEPURACION_TASKx_ENABLED*/
				#endif /*RAW_TLM_TASKx_ENABLED*/		
				estado_fsm_protocolo = VERIFICACION;
			}
		}
	} else {
		if (estado_canal == ASIGNADO)
			estado_fsm_protocolo = ESPERA;
	
		#if RAW_TLM_TASK1_ENABLED == 1
			//declaración opcional
		#else
		 #if DEPURACION_TASK1_ENABLED == 1
		 sprintf(debug_string_, "%lf ms = Espera por TRAMA superada:\n", 2*ESPERA_Tt);
		 serialUSB_print_link(debug_string_); /* DEBUGGING */
		 #endif /*DEPURACION_TASKx_ENABLED*/
		#endif /*RAW_TLM_TASKx_ENABLED*/
	}
}
 
 /* 
 * Definida para ejecutar acción de “Relevamiento”, “Envió ASK” y decisión “Numero de trama?” (Figura 4).
 *
 * #1
 * Entrada:	Desde #0/2
 * Accion:	Consultar documento
 * Salida:  Después de secuencia
 *
 */
 void relevamiento(unsigned char* trama_){
	 
	unsigned char ask_[SIZE_ASK];
	 
	if (trama_[ID_TRAMA_NUM_pos] > num_trama_anterior){
		 num_trama_anterior = trama_[ID_TRAMA_NUM_pos];
		 
		if (trama_[ID_TRAMA_TIPO_pos] == TRAMA_FINAL){
			resultado = EXITO;
			espera_recepcion_consumidas = NOTHING;
			estado_canal = LIBRE;
		}else 
			resultado = RECIBIENDO;		 
		 
		resultado_disponible = TRUE;
	}
	
	ask_rst(ask_);
	ask_[ID_ASK_pos] = ID_ASK;
	
	envio_ask(ask_);

	#if RAW_TLM_TASK1_ENABLED == 1
	 sprintf(debug_string_, "ASK; espera_recepcion_consumidas; %d\n", espera_recepcion_consumidas);
	 serialUSB_print_link(debug_string_); /* DEBUGGING */
	#else
	 #if DEPURACION_TASK1_ENABLED == 1
	 sprintf(debug_string_, "\n\tASK (%c) ::: enviado\n", ID_ASK);
	 serialUSB_print_link(debug_string_); /* DEBUGGING */
	 #endif /*DEPURACION_TASKx_ENABLED*/
	#endif /*RAW_TLM_TASKx_ENABLED*/
	
	estado_fsm_protocolo = VERIFICACION;	  
 }
 
 /* 
 * Definida para ejecutar acción de proceso “Asignar canal” y decisiones “Canal asignado?” (Figura 4).
 *
 * #2
 * Entrada:	Desde #0
 * Accion:	Consultar documento
 * Salida:  Después de secuencia
 *
 */
 void asignacion_canal(){
	
	static unsigned long tiempo_ = NOTHING;
	
	if (estado_canal == LIBRE){
		
		#if RAW_TLM_TASK1_ENABLED == 1
			//declaración opcional
		#else
		 #if DEPURACION_TASK1_ENABLED == 1
		 serialUSB_print_link("Canal Asignado\n"); /* DEBUGGING */
		 #endif /*DEPURACION_TASKx_ENABLED*/
		#endif /*RAW_TLM_TASKx_ENABLED*/
		
		tiempo_ = NOTHING;
		estado_canal = ASIGNADO;
		num_trama_anterior = NOTHING;
		estado_fsm_protocolo = RELEVAMIENTO;
		
	} else {
		
		if (tiempo_ != NOTHING)
			tiempo_ = CURRENT_TIME_MS;
		
		if(CURRENT_TIME_MS - tiempo_ < (2*ESPERA_Tt))
			estado_fsm_protocolo = VERIFICACION;
		else
			estado_fsm_protocolo = ESPERA;
	}
 }
 
 
 /* 
 * Definida para ejecutar acción de proceso “Liberar canal”, “Espera++” y decisión, “Espera > n” (Figura 4).
 *
 * #3
 * Entrada:	Desde #0
 * Accion:	Consultar documento
 * Salida:  Después de secuencia
 *
 */
 void espera(){
	 
	espera_recepcion_consumidas++;
	
	#if RAW_TLM_TASK1_ENABLED == 1
		//declaración opcional
	#else
	 #if DEPURACION_TASK1_ENABLED == 1
	 sprintf(debug_string_, "\t\tespera_ (%d)\n", espera_recepcion_consumidas);
	 serialUSB_print_link(debug_string_); /* DEBUGGING */
	 #endif /*DEPURACION_TASKx_ENABLED*/
	#endif /*RAW_TLM_TASKx_ENABLED*/

	#if METADATOS_AL_PUERTO_SERIAL == 1
 	if (espera_recepcion_live_tlm < espera_recepcion_consumidas)
 		espera_recepcion_live_tlm = espera_recepcion_consumidas;
	#endif /* METADATOS_AL_PUERTO_SERIAL */
	
	if (espera_recepcion_consumidas > ESPERA_RECEPCION_MAX){
		
		estado_canal = LIBRE;
		
		#if RAW_TLM_TASK1_ENABLED == 1
		 sprintf(debug_string_, "FRACASO; espera_recepcion_consumidas; %d\n", espera_recepcion_consumidas);
		 serialUSB_print_link(debug_string_); /* DEBUGGING */
		#else
		 #if DEPURACION_TASK1_ENABLED == 1
		 serialUSB_print_link("Canal Liberado\n"); /* DEBUGGING */
		 #endif /*DEPURACION_TASKx_ENABLED*/
		#endif /*RAW_TLM_TASKx_ENABLED*/
		
		espera_recepcion_consumidas = NOTHING;
		
		resultado_disponible = TRUE;
		resultado = FRACASO;
	}	
	
	estado_fsm_protocolo = VERIFICACION;
 }
 
 
 
/*
 * N/A
 * Inicializa el arreglo de ask.
 */
void ask_rst(unsigned char* ask){
	
	for (int i = 0; i < SIZE_ASK; i++)
		ask[i] = 0b11110010;	// Demasiados byets en cero puede generar la perdida de paquetes.
}