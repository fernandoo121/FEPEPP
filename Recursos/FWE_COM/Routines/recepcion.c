/*
 * recepcion.c
 *
 * Created: 24/1/2023 8:58:48
 * Author : Andres Mezquida
 */

/*
 * Esta rutina ...
 *
 *
 *
 */

 #include "gateway.h"

enum estado_rutina{
	COPY_DATA_OPRC,
	COPY_DATA_TLM,
	COPY_ID_SPBP,
	COPY_ID_OPRR,
	COPY_RAW_GNSS,
};

char estado_rutina = COPY_DATA_OPRC;

unsigned char trama_[SIZE_TRAMA];
char trama_inicial = FALSE;

unsigned int ind_trama;
unsigned int ind_metadatos;

/* Estados rutina */
char copy_data_oprc(struct data_task_0 *metadatos);
char copy_data_tlm(struct data_task_0 *metadatos);
char copy_id_spbp(struct data_task_0 *metadatos);
char copy_id_oprr(struct data_task_0 *metadatos);
char copy_raw_gnss(struct data_task_0 *metadatos);
char paste_trama(unsigned char* metadatos, unsigned int size_, char variable_size, char bytes_data_size);

void trama_rst();
unsigned int obtener_size_(unsigned int size_max, char bytes_data_size);
void corrupcion_metadatos_entrantes();

char resepcion_metadatos(struct data_task_0 *metadatos){
	
	switch(estado_rutina){
		case COPY_DATA_OPRC:	return copy_data_oprc(metadatos);	break;
		case COPY_DATA_TLM:		return copy_data_tlm(metadatos);	break;
		case COPY_ID_SPBP:		return copy_id_spbp(metadatos);		break;
		case COPY_ID_OPRR:		return copy_id_oprr(metadatos);		break;
		case COPY_RAW_GNSS:		return copy_raw_gnss(metadatos);	break;
	}
	
	return -1;
}

/*
 * Configura copia elementos del arreglo de trama, al arreglo datos operación.
 */
char copy_data_oprc(struct data_task_0 *metadatos){
	
	char resultado_; 

	ind_metadatos = 0;
	trama_inicial = TRUE;
	
	resultado_ = paste_trama(metadatos->data_oprc, SIZE_DATA_OPRC, NO, NOTHING);
	
	estado_rutina = (resultado_ != FRACASO ?  COPY_DATA_TLM : COPY_DATA_OPRC);

	return resultado_;
}

/*
 * Configura copia elementos del arreglo de trama, al arreglo datos telemetría.
 */
char copy_data_tlm(struct data_task_0 *metadatos){
	
	char resultado_;
	
	ind_metadatos = 0;
	
	resultado_ = paste_trama(metadatos->data_tlm, SIZE_DATA_TLM_SPBP, NO, NOTHING);
	
	estado_rutina = (resultado_ != FRACASO ?  COPY_ID_SPBP : COPY_DATA_OPRC);

	return resultado_;
}

/*
 * Configura copia elementos del arreglo de trama, al arreglo identificación sarapico.
 */
char copy_id_spbp(struct data_task_0 *metadatos){
	
	char resultado_;
	
	ind_metadatos = 0;
	
	resultado_ = paste_trama(metadatos->id_spbp, SIZE_ID_SPBP, SI, ID_SPBP_CAHRs_Leng);
	
	estado_rutina = (resultado_ != FRACASO ?  COPY_ID_OPRR : COPY_DATA_OPRC);

	return resultado_;
}

/*
 * Configura copia elementos del arreglo de trama, al arreglo identificación operario.
 */
char copy_id_oprr(struct data_task_0 *metadatos){
	
	char resultado_;
	
	ind_metadatos = 0;
	
	resultado_ = paste_trama(metadatos->id_oprr, SIZE_ID_OPRR, SI, ID_OPRR_CAHRs_Leng);
	
	estado_rutina = (resultado_ != FRACASO ?  COPY_RAW_GNSS : COPY_DATA_OPRC);

	return resultado_;
}

/*
 * Configura copia de los elementos del arreglo datos en crudo GNSS, al arreglo de trama.
 */
char copy_raw_gnss(struct data_task_0 *metadatos){
	
	char resultado_;
	
	ind_metadatos = 0;
	
	resultado_ = paste_trama(metadatos->raw_gnss, SIZE_RAW_GNSS, SI, DATA_RAW_GNSS_CAHRs_Leng);
	
	estado_rutina = COPY_DATA_OPRC;

	return resultado_;
}


/*
 * Solicita trama y copia los elementos del arreglo de trama, al arreglo en cuestion.
 */

char paste_trama(unsigned char* metadatos, unsigned int size_, char variable_size, char bytes_data_size){
	
	char resultado = RECIBIENDO;
	
	while(ind_metadatos < size_){
		
		if (ind_trama == SIZE_TRAMA || trama_inicial == TRUE){
			
			trama_rst();
			resultado = resepcion_trama(trama_); // Solicita al protocolo la trama.
		
			if (resultado == FRACASO)
				break;
			else{
				ind_trama = METADATOS_pos;
			}
		}
		
		if (variable_size == SI){
			size_ = obtener_size_(size_, bytes_data_size);
			variable_size = NO;
		}
			
		metadatos[ind_metadatos] = trama_[ind_trama];
		
		ind_trama++;
		ind_metadatos++;
		
	}
	
	return resultado;
}

/*
 * Inicializa el arreglo de trama con NOTHING.
 */
void trama_rst(){
	
	for (int i = 0; i < SIZE_TRAMA; i++)
		trama_[i] = NOTHING;
	
	trama_inicial = FALSE;
}


/*
 *	Obtiene el tamaño de la estructura de metadatos en cuestión.
 */

unsigned int obtener_size_(unsigned int size_max, char bytes_data_size){
	
	unsigned int size_ = NOTHING;
	
	switch(bytes_data_size){
		 case 1:
				size_ = trama_[ind_trama];
				break;
		 case 2: 
				size_ = trama_[ind_trama] << 8;
				size_ |= trama_[ind_trama + 1];
				break;
	}
	
	size_ += bytes_data_size;
	
	if (size_ > size_max){
		size_ = size_max;
		corrupcion_metadatos_entrantes();
	}
	
	return size_;
}

/*
 *	Establece las banderas correspondientes para indicar corrupción en metadatos.
 */

void corrupcion_metadatos_entrantes(){
#warning "mitigacion de corrupcion de metadatos entrantes sin implementar"

	unsigned long tiempo_ = NOTHING;

	while(1){
		
		if (tiempo_ == NOTHING || ((CURRENT_TIME_MS - tiempo_) > 10000 && serialUSB_Ready_link(FALSE))){
			serialUSB_print_link("\n\n FALLA Subsistema Comunicación:" "\n\t Metadatos dañados (transmision metadatos).\n");
			serialUSB_print_link("\t Mitigacion de corrupcion de metadatos entrantes sin implementar.\n\n");
			tiempo_ = NOTHING;
		}
		
		if (tiempo_ == NOTHING && serialUSB_Ready_link(FALSE))
			tiempo_ = CURRENT_TIME_MS;
		
		LED_WARNING_TOGGLE;
		LED_DONE_TOGGLE;
// 		LED_COM_TOGGLE;
// 		LED_GEO_TOGGLE;
		BUZZER_TOGGLE;
		DELAY_MS(500);
		
	}

}

