/*
 * generacion_metadata.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"

#ifdef FCOM_sim_on

 //Estado variables de interés
 #define NO			0b00
 #define SI			0b01
 #define HORIZONTAL	0b01
 #define VERTICAL	0b10
 #define INDET		0b11

 #define plantin		SI
 #define fertilizante	SI
 #define orientacion	VERTICAL
 #define movimiento		SI
 
 #define raw_gnss_val	0XCA
 
 #define TLM_RF		0b10000000
 #define TLM_GNSS	0b01000000
 #define TLM_VIN	0b00100000
 #define TLM_FLASH	0b00010000
 #define TLM_RTCS	0b00001000
 #define TLM_MOD	0b00000100
 #define TLM_NBAT	0b00000000
 
 #define TLM_SEN1	0b00000001
 #define TLM_SEN2	0b00001001
 #define TLM_SEN3	0b00001001

 unsigned char sim_last_work_day = NOTHING;

/* Generacion metadatos */
 unsigned char sim_date_OPRC(unsigned char offset);
 unsigned char sim_id_OPRR(unsigned char offset, unsigned int id);
 unsigned char sim_id_SPBP(unsigned char offset, unsigned char id);
 void sim_actualisar_num_OPRR(unsigned int  sim_num_oprc);

 /* 
  * Completa metadata.
  */
 void generacion_metadata(struct data_task_0 *metadatos, unsigned int sim_num_oprc, unsigned int id_electronica, unsigned int id_operario){

	metadatos->solicitud_ = NADA_;	

	// Fecha y Hora
	metadatos->data_oprc[DATA_OPRC_CAHR6_Pos] = sim_date_OPRC(24);
	metadatos->data_oprc[DATA_OPRC_CAHR5_Pos] = sim_date_OPRC(16);
	metadatos->data_oprc[DATA_OPRC_CAHR4_Pos] = sim_date_OPRC(8);
	metadatos->data_oprc[DATA_OPRC_CAHR3_Pos] = sim_date_OPRC(0);
		
	// Datos operativa
	sim_actualisar_num_OPRR(sim_num_oprc);
	metadatos->data_oprc[DATA_OPRC_CAHR2_Pos] = (sim_num_oprc >> DATA_OPRC_OPRC_Des);
	metadatos->data_oprc[DATA_OPRC_CAHR1_Pos] = (sim_num_oprc << DATA_OPRC_OPRC_Pos0);
		
	// Estado variables de interés
	metadatos->data_oprc[DATA_OPRC_CAHR0_Pos] = (plantin << DATA_OPRC_PT_Pos0)		|
												(fertilizante << DATA_OPRC_FT_Pos0)	|
												(orientacion << DATA_OPRC_OR_Pos0)	|
												(movimiento << DATA_OPRC_MO_Pos0);	
		
	// Identificación de la electrónica del sarapico
	metadatos->id_spbp[ID_SPBP_CAHR3_Pos] = sim_id_SPBP((((SIZE_ID_SPBP -1) - ID_SPBP_CAHR3_Pos)*8), id_electronica);
	metadatos->id_spbp[ID_SPBP_CAHR2_Pos] = sim_id_SPBP((((SIZE_ID_SPBP -1) - ID_SPBP_CAHR2_Pos)*8), id_electronica);
	metadatos->id_spbp[ID_SPBP_CAHR1_Pos] = sim_id_SPBP((((SIZE_ID_SPBP -1) - ID_SPBP_CAHR1_Pos)*8), id_electronica);
	metadatos->id_spbp[ID_SPBP_CAHR0_Pos] = sim_id_SPBP((((SIZE_ID_SPBP -1) - ID_SPBP_CAHR0_Pos)*8), id_electronica);
				
	// Identificación del operario				
	metadatos->id_oprr[ID_OPRR_CAHR4_Pos] = sim_id_OPRR((((SIZE_ID_OPRR -1) - ID_OPRR_CAHR4_Pos)*8), id_operario);
	metadatos->id_oprr[ID_OPRR_CAHR3_Pos] = sim_id_OPRR((((SIZE_ID_OPRR -1) - ID_OPRR_CAHR3_Pos)*8), id_operario);
	metadatos->id_oprr[ID_OPRR_CAHR2_Pos] = sim_id_OPRR((((SIZE_ID_OPRR -1) - ID_OPRR_CAHR2_Pos)*8), id_operario);
	metadatos->id_oprr[ID_OPRR_CAHR1_Pos] = sim_id_OPRR((((SIZE_ID_OPRR -1) - ID_OPRR_CAHR1_Pos)*8), id_operario);
	metadatos->id_oprr[ID_OPRR_CAHR0_Pos] = sim_id_OPRR((((SIZE_ID_OPRR -1) - ID_OPRR_CAHR0_Pos)*8), id_operario);
		
	// Datos en crudo GNSS
	
	unsigned int length_raw_gnss = (sizeof(metadatos->raw_gnss) - DATA_RAW_GNSS_CAHRs_Leng);
	
	metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength1_Pos] = length_raw_gnss >> DATA_RAW_GNSS_LENGTH_Des;
	metadatos->raw_gnss[DATA_RAW_GNSS_CAHRlength0_Pos] = length_raw_gnss;
		
	for (short ind = DATA_RAW_GNSS_CAHRs_Leng; ind < SIZE_RAW_GNSS; ind++){
		metadatos->raw_gnss[ind] = raw_gnss_val;
	}
			
	// Datos funcionamiento electrónica
	metadatos->data_tlm[DATA_TLM_CAHR0_Pos] =   TLM_RF		| 
												TLM_GNSS	|
												TLM_VIN		|
												TLM_FLASH	| 
												TLM_RTCS	| 
												TLM_MOD		| 
												TLM_NBAT;
												  
	metadatos->data_tlm[DATA_TLM_CAHR1_Pos] = TLM_SEN1;
	metadatos->data_tlm[DATA_TLM_CAHR2_Pos] = TLM_SEN2;
	metadatos->data_tlm[DATA_TLM_CAHR3_Pos] = TLM_SEN3;

	metadatos->solicitud_ = NADA_;
 
 } 

 /* 
  * Retorna fecha y hora para cargar en DATA_OPRC.
  */
 unsigned char sim_date_OPRC(unsigned char offset){
	return date_RTC() >> offset;
 }

 /* 
  * Retorna el número de operación de los metadatos para la jornada de trabajo, para cargar en DATA_OPRC.
  */
 void sim_actualisar_num_OPRR(unsigned int sim_num_oprc){
	
	unsigned char current_work_day;
	
	current_work_day = day_RTC();
	
	if (sim_last_work_day != current_work_day){ //num_oprc es reiniciado cada nueva jornada de trabajo
		sim_last_work_day = current_work_day;
		sim_num_oprc = 0;
	}
	
	sim_num_oprc++;
 }

 /* 
  * Retorna el identificación de la electrónica del sarapico y su longitud en bytes, para cargar en ID_SPBP.
  */
 unsigned char sim_id_SPBP(unsigned char offset, unsigned char id){
	
	/*static unsigned char length_id;*/
	static unsigned int id_data;
	
	id_data  = 1 << 24; // largo
	id_data |= id << 16; //id

	return id_data >> offset;
 }

 /* 
  * Retorna el identificación del operario y su longitud en bytes, para cargar en ID_OPRR.
  */
 unsigned char sim_id_OPRR(unsigned char offset, unsigned int id){
	
	static char id_length = 0;
	static unsigned int id_data = 0;
	
	unsigned char ind_id = ((sizeof(id)*8) -1);
	
	do{
		for (unsigned char ind_byte = ind_id;  (ind_id - ind_byte) < 8 ; ind_byte--){
			if ((id & (1 << ind_byte)) != 0)
				goto listo;
		}
		ind_id -= 8;
	}while(ind_id > 8);

 listo:
	id_length = ((ind_id + 1)/8);
	id_data = id << (((sizeof(id)*8) -1) - ind_id);
	 
	if (offset > 24)
		 return id_length;
		 
	return id_data >> offset;
 }
 

#endif // FCOM_sim_on
