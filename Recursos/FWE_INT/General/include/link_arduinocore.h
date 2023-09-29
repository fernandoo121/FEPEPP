/*
 * link_arduinocore.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#ifndef LINK_ARDUINOCORE_H_
#define LINK_ARDUINOCORE_H_


 #ifdef __cplusplus
 extern "C" {
 #endif

	/* ArduinoCore startup.c link */
	void system_init_link();

	/* ArduinoCore USBCore.cpp link */
	void usb_start_link();

	/* ArduinoCore print.cpp link */
	void serialUSB_print_link(char* data);
	void serial_GNSS_print_link(char* data);

	/* ArduinoCore CDC.cpp link */
	char serialUSB_Ready_link(char stop);
	signed int serialUSB_available_link();
	signed int serialUSB_read_link();
	unsigned int serialUSB_readBytes_link(unsigned char* buffer, unsigned long length);
	void serialUSB_write_link(unsigned char *buffer, long unsigned int size);

	/* ArduinoCore Uart.cpp link */
	void serial_GNSS_start_link(unsigned long baudrate);
	void serial_GNSS_Ready_link();
	signed int serial_GNSS_available_link();
	signed int serial_GNSS_read_link();
	unsigned int serial_GNSS_readBytes_link(unsigned char* buffer, unsigned long length);
	void serial_GNSS_write_link(unsigned char *buffer, long unsigned int size);

	/* ArduinoCore SD.cpp link */
	char sd_check_link(long clock, char csPin);
	char sd_begin_link(long clock, char csPin);
	char file_open_link(const char *filepath);
	char file_remove_link(const char *filepath);
	unsigned long file_write_string_link(char* data);
	unsigned long file_write_bytes_link(unsigned char* data, unsigned long size);
	char file_read_character_link();
	signed int file_read_bytes_link(unsigned char* storage, signed int size);
	unsigned long file_get_position_link();
	char file_set_position_link(unsigned long position);
	void file_flush_link();
	void file_close_link();
	int file_data_available();
	void card_info(int chipSelect);

	/* ArduinoCore delay.c link */
	unsigned long millis_link(void);
	unsigned long micros_link(void);
	void delay_link(unsigned long ms);
	void delayMicroseconds_link(unsigned int us);
	
	// MQTT FERNANDO
	void init_sim868();
	char connect_gprs();
	char connect_mqtt();
	//void send_data(struct data_task_0 *metadatos);
	char send_data_link();
	char NetworkConnected_link();
	char isMqttConnected_link();
	char isGprsConnected_link();
	void modeminformation();
	char prueba_Ard_original();
	
 
 #ifdef __cplusplus
 }
 #endif

#endif /* LINK_ARDUINOCORE_H_ */