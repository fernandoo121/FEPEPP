/*
 * slave_FlashDrive.c
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

 #include "gateway.h"
 #include "pro_routines.h"
 #include "slave_FlashDrive.h"
 

#define FILE_NAME_LENGTH 8 + 4
char nombre_archivo[FILE_NAME_LENGTH] = FILE_NAME_;

char unidad_flash_init_ = FALSE;
 
/* 
 * Inicializa la escritura a la unidad flash en formato Fat32.
 */
 void init_SD_MMC(){
	 
	if(!sd_begin_link(F_CPU, PIN_SD))
		SD_MMC_FailureAttention_begin;
	else
		if(file_open_link(nombre_archivo)){
			unidad_flash_init_ = TRUE;
		} else
			SD_MMC_FailureAttention_open;
}

/* 
 * Respalda estructura de metadatos hacia la unidad flas.
 */
 void send_metadata_SD_MMC(struct data_task_0 *metadatos){
	 
	 unsigned long result = 0;
	 
	 result  = file_write_bytes_link(metadatos->data_oprc,	SIZE_DATA_OPRC);
	 result += file_write_bytes_link(metadatos->data_tlm,	SIZE_DATA_TLM);
	 result += file_write_bytes_link(metadatos->id_spbp,	SIZE_ID_SPBP);
	 result += file_write_bytes_link(metadatos->id_oprr,	SIZE_ID_OPRR);
	 result += file_write_bytes_link(metadatos->id_ebps,	SIZE_ID_EBPS);
	 result += file_write_bytes_link(metadatos->id_cdll,	SIZE_ID_CDLL);
	 result += file_write_bytes_link(metadatos->raw_gnss,	SIZE_RAW_GNSS);
	 
	 if(result == SIZE_METADATA){
		 file_flush_link();
	 } else {
		 unidad_flash_init_ = FALSE;
	 }
 }
 
/* 
 * Recupera estructura de metadatos desde la unidad flas.
 */
void read_metadata_SD_MMC(struct data_task_0 *read_metadatos){
	 
	unsigned long result = 0;
	
	result  = file_read_bytes_link(read_metadatos->data_oprc,	SIZE_DATA_OPRC);
	result += file_read_bytes_link(read_metadatos->data_tlm,	SIZE_DATA_TLM);
	result += file_read_bytes_link(read_metadatos->id_spbp,		SIZE_ID_SPBP);
	result += file_read_bytes_link(read_metadatos->id_oprr,		SIZE_ID_OPRR);
	result += file_read_bytes_link(read_metadatos->id_ebps,		SIZE_ID_EBPS);
	result += file_read_bytes_link(read_metadatos->id_cdll,		SIZE_ID_CDLL);
	result += file_read_bytes_link(read_metadatos->raw_gnss,	SIZE_RAW_GNSS);
	
	if(result != SIZE_METADATA)
		unidad_flash_init_ = FALSE;
}

/* 
 * Envía una variable tipo unsigned long hacia la unidad flash.
 */
void send_ulong_SD_MMC(unsigned long data_ulong){
	
	unsigned char array_char[sizeof(unsigned long)] = "";
	
	for(int i = 0, offset = 0; i < sizeof(unsigned long); i ++, offset += 8)
		array_char[-1 + sizeof(unsigned long) - i] = data_ulong >> offset;
	
	if(file_write_bytes_link(array_char, sizeof(unsigned long)) != sizeof(unsigned long))
		unidad_flash_init_ = FALSE;
	else
		file_flush_link();
}

/* 
 * Leee una variable tipo unsigned char desde la unidad flash.
 */
void read_uchar_SD_MMC(unsigned char *data_uchar){
	
	if(file_read_bytes_link(data_uchar, sizeof(unsigned char)) != sizeof(unsigned char))
		unidad_flash_init_ = FALSE;
}

/* 
 * Leee una variable tipo unsigned int desde la unidad flash.
 */
 void read_uint_SD_MMC(unsigned int *data_uint){
 	
 	unsigned char array_char[sizeof(unsigned int)] = "";
 	
 	if(file_read_bytes_link(array_char, sizeof(unsigned int)) != sizeof(unsigned int))
 		unidad_flash_init_ = FALSE;
 	else
 		for(int i = 0, offset = 0; i < sizeof(unsigned int); i ++, offset += 8)
 			*data_uint |= array_char[-1 + sizeof(unsigned int) - i] << offset;
 			
 }

/* 
 * Lee una variable tipo unsigned long desde la unidad flash.
 */
void read_ulong_SD_MMC(unsigned long *data_ulong){
	
	unsigned char array_char[sizeof(unsigned long)] = "";
	
	if(file_read_bytes_link(array_char, sizeof(unsigned long)) != sizeof(unsigned long))
		unidad_flash_init_ = FALSE;
	else
		for(int i = 0, offset = 0; i < sizeof(unsigned long); i ++, offset += 8)
			*data_ulong |= array_char[-1 + sizeof(unsigned long) - i] << offset;
			
}

/* 
 * Elimina todos los metadatos en unidad flash.
 */ 
void delete_file_SD_MMC(){
	
	unsigned long tiempo_ = CURRENT_TIME_MS;
	int size_file = NOTHING;
	char string_[100];
	
	SUSPEND_ALL_SECTION_INIT();
	
	serialUSB_print_link("\n Realmente desea eliminar los datos? S/N\n");
	
	while(!serialUSB_available_link() && (CURRENT_TIME_MS - tiempo_) < 3000);
	
	if (serialUSB_read_link() == 'S'){
		serialUSB_print_link("\n Elimiando ...\n");
		file_set_position_link(DIRECCION_INICIO_FLASH);
		size_file = file_data_available();
		
		if(file_remove_link(nombre_archivo)){
			inicializar_fsm();
			serialUSB_print_link("\n Borrado OK");
			
			sprintf(string_," (%d bytes)\n\n", size_file);
			serialUSB_print_link(string_);
			
		}else
			serialUSB_print_link("\n Borrado FAILED\n\n");		
	}
	
	tiempo_ = NOTHING;
		
	SUSPEND_ALL_SECTION_END();
}

/* 
 * Vuelca todos los metadatos en unidad flash, al puerto serial.
 */
 static struct data_task_0 temp_metadatos;
 static unsigned long temp_direccion_datos_relevados = NOTHING;
 static unsigned long temp_direccion_actual_escritura = NOTHING;
	 
 void dump_file_SD_MMC(char volcado_hexa){
	 
	 char string_[256];
	 
	 if (unidad_flash_init_ == FALSE){
		 serialUSB_print_link("\n\n\t NO SE PUDO LEER UNIDAD FLASH\n\n");
		 return;
	 }
	 
	 SUSPEND_ALL_SECTION_INIT();

	 serialUSB_print_link("\n\nMETADATOS EBPS ::\n\n");
	 
	 sprintf(string_, "Procesamiento solicitud:; %d/%d/%d %d:%d:%d\n\n",
							day_RTC(), month_RTC(), year_RTC(), hour_RTC(), minute_RTC(), second_RTC());
	 serialUSB_print_link(string_);
	 
	 temp_direccion_actual_escritura = file_get_position_link();
	 file_set_position_link(DIRECCION_INICIO_FLASH);
	 
	 read_ulong_SD_MMC(&temp_direccion_datos_relevados);
	 
	 sprintf(string_,"Ultima dirección de metadatos relevados:; %8lu\n", temp_direccion_datos_relevados - SIZE_METADATA);
	 serialUSB_print_link(string_);
	 sprintf(string_,"Tamaño del archivo:; %d bytes\n\n", file_data_available() + sizeof(direccion_datos_relevados));
	 serialUSB_print_link(string_);
	 
	if(volcado_hexa == FALSE)
		serialUSB_print_link("Dirección unidad flash; Fecha; Hora; Número operación; Plantín; Fertilizante; Orientación; Movimiento; TLM_SPBP; TLM_EBPS; ID_SPBP; ID_OPRR; ID_EBPS; ID_CDLL; RAW_GNSS\n");
	else
		serialUSB_print_link("Dirección unidad flash; Metadatos\n");
	 
	 while(file_data_available()){

		sprintf(string_,"%8lu;",file_get_position_link());
		serialUSB_print_link(string_);
		
		read_metadata_SD_MMC(&temp_metadatos);
		if(volcado_hexa == FALSE)
			metadatos_al_puerto_serial_ascii(&temp_metadatos, NOTHING, NOTHING);
		else
			metadatos_al_puerto_serial_hexa(&temp_metadatos);
		
		if (unidad_flash_init_ == FALSE){
			serialUSB_print_link("\n\n\t NO SE PUDO LEER UNIDAD FLASH\n\n");
			break;
		}
	 }
	 
	 file_set_position_link(temp_direccion_actual_escritura);
	 
	 sprintf(string_, "\nFin solicitud:; %d/%d/%d %d:%d:%d\n\n",
							day_RTC(), month_RTC(), year_RTC(), hour_RTC(), minute_RTC(), second_RTC());
	 serialUSB_print_link(string_);
	 
	 SUSPEND_ALL_SECTION_END();
	 
	 return;
 }