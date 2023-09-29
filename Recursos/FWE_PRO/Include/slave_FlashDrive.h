/*
 * slave_FlashDrive.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef SLAVE_FLASHDRIVE_H_
#define SLAVE_FLASHDRIVE_H_

 #define DIRECCION_INICIO_FLASH		0x0
 #define DIRECCION_INICIO_METADATA	sizeof(direccion_datos_relevados)

 extern char unidad_flash_init_;

#ifdef __cplusplus
extern "C" {
#endif

	void init_SD_MMC();
	void send_metadata_SD_MMC(struct data_task_0 *metadatos);
	void read_metadata_SD_MMC(struct data_task_0 *metadatos);

	void send_ulong_SD_MMC(unsigned long data_ulong);
	void read_uchar_SD_MMC(unsigned char *data_uchar);
	void read_uint_SD_MMC(unsigned int *data_uint);
	void read_ulong_SD_MMC(unsigned long *data_ulong);

	void delete_file_SD_MMC();
	void dump_file_SD_MMC(char tipo_volcado);

#ifdef __cplusplus
}
#endif
#endif /* SLAVE_FLASHDRIVE_H_ */