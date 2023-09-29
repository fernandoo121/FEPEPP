/*
 * link_ArduinoCore.cpp
 *
 * Created: 23/01/2023
 * Author : Andres Mezquida
 */

#include "Arduino.h"
#include "gateway.h"
#include "error_hooks.h"

/*
	CONFIGURACIÓN PINES NÚCLEO ARDUINO

	En varian.cpp el núcleo Arduino configura la funcionalidad de los pines en el arreglo g_APinDescription[], 
	y asigna dichos pines a la clase correspondiente (serial, usb, SPI, Wire ...) en varian.h a traves de las 
	definiciones corespondientes ... por mas detalles consultar:
		
		SparkFun TUTORIALS (https://learn.sparkfun.com/tutorials/adding-more-sercom-ports-for-samd-boards/all)
*/

void system_init_link(){
	
	/*
	// Generic Clock Generator 0 at 48MHz
	// Generic Clock Generator 1 at 32.768kHz
	// Generic Clock Generator 3 at 8MHz
	*/
	
	//Warning the F_CPU symbol must sit on 48000000ul all compilers.
	
	SystemInit_ArduinoCore();
	
	vSetErrorLed(Error_Led_crashes_rtos);		// Set the error led to use by the rtos.
	vSetErrorSerial(&Error_Serial_crashes_rtos);	// Set the error serial port for debugging asserts and crashes.
  
}

/* Linked to USBCore.cpp*/
void usb_start_link(){
 	usb_start();
}

/* Linked with delay.c*/
unsigned long millis_link(void){
	return millis();
}

unsigned long micros_link(void){
	return micros();
}

void delay_link(unsigned long ms){
	delay(ms);
}

void delayMicroseconds_link(unsigned int us){
	delayMicroseconds(us);
}

/* Linked with print.cpp*/
void serialUSB_print_link(char* data){
#if USB_PERIPHERAL_ENABLED == 1
	SerialUSB.print(data);
#else
	return;
#endif /*USB_PERIPHERAL_ENABLED*/
}

void serial1_print_link(char* data){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	Serial1.print((char*) data);
#else
	return;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

void serial_GNSS_print_link(char* data){
#if USB_PERIPHERAL_ENABLED == 1
	Serial_GNSS.print((char*) data);
#else
	return;
#endif /*USB_PERIPHERAL_ENABLED*/
}

/* Linked with CDC.cpp*/
char serialUSB_Ready_link(char stop){
	
	char serial_status = 1;
	
#if USB_PERIPHERAL_ENABLED == 1
	if (stop == TRUE)
		while(!SerialUSB);
	else
		serial_status = SerialUSB;
#else
	serial_status = 0;
#endif /*USB_PERIPHERAL_ENABLED*/
	return serial_status;
}

signed int serialUSB_available_link(){
#if USB_PERIPHERAL_ENABLED == 1
	return SerialUSB.available();
#else
	return -1;
#endif /*USB_PERIPHERAL_ENABLED*/
}

void serialUSB_write_link(unsigned char *buffer, long unsigned int size){
#if USB_PERIPHERAL_ENABLED == 1
	SerialUSB.write(buffer, size);
#else
	return;
#endif /*USB_PERIPHERAL_ENABLED*/
}

signed int serialUSB_read_link(){
#if USB_PERIPHERAL_ENABLED == 1
	return SerialUSB.read();
#else
	return -1;
#endif /*USB_PERIPHERAL_ENABLED*/
}

unsigned int serialUSB_readBytes_link(unsigned char* buffer, unsigned long length){
#if USB_PERIPHERAL_ENABLED == 1
	return SerialUSB.readBytes((char*) buffer, length);
#else
	return -1;
#endif /*USB_PERIPHERAL_ENABLED*/
}

/* Linked to Uart.cpp*/
void serial1_start_link(unsigned long baudrate){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	Serial1.begin(baudrate);
#endif /*SERCOMx_PERIPHERAL_ENABLED*/	
}

void serial1_Ready_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	while(!Serial1);
#else
	return;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

signed int serial1_available_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return Serial1.available();
#else
	return -1;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

void serial1_write_link(unsigned char *buffer, long unsigned int size){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	Serial1.write(buffer, size);
#else
	return;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

signed int serial1_read_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return Serial1.read();
#else
	return -1;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

void serial_GNSS_start_link(unsigned long baudrate){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	Serial_GNSS.begin(baudrate);
#endif /*SERCOMx_PERIPHERAL_ENABLED*/	
}

void serial_GNSS_Ready_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	while(!Serial_GNSS);
#else
	return;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

signed int serial_GNSS_available_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return Serial_GNSS.available();
#else
	return -1;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

void serial_GNSS_write_link(unsigned char *buffer, long unsigned int size){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	Serial_GNSS.write(buffer, size);
#else
	return;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

signed int serial_GNSS_read_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return Serial_GNSS.read();
#else
	return -1;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

/* Linked Stream.cpp*/
unsigned int serial1_readBytes_link(unsigned char* buffer, unsigned long length){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return Serial1.readBytes((char*) buffer, length);
#else
	return -1;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

unsigned int serial_GNSS_readBytes_link(unsigned char* buffer, unsigned long length){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return Serial_GNSS.readBytes((char*) buffer, length);
#else
	return -1;
#endif /*SERCOMx_PERIPHERAL_ENABLED*/
}

/* Linked with SD.cpp*/
#include "SD.h"
File backup_file;

char sd_check_link(long clock, char csPin){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	Sd2Card card;
	
	return card.init(clock, csPin);
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

char sd_begin_link(long clock, char csPin){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return SD.begin(clock, csPin);
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

char file_open_link(const char *filepath){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	backup_file = SD.open(filepath, O_READ | O_WRITE | O_CREAT);
	backup_file.seek(backup_file.size());
	return backup_file;
#else	
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

char file_remove_link(const char *filepath){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return SD.remove(filepath);
#else	
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

unsigned long file_write_string_link(char* data){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.write(data);
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

unsigned long file_write_bytes_link(unsigned char* data, unsigned long size){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.write((char*) data, size);
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

char file_read_character_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.read();
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

signed int file_read_bytes_link(unsigned char* storage, signed int size){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.read((char*) storage, size);
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

void file_flush_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	backup_file.flush();
#else
	return ;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

void file_close_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	backup_file.close();
#else
	return ;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

unsigned long file_get_position_link(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.position();
#else
	return ;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

char file_set_position_link(unsigned long position){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.seek(position);
#else
	return ;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

int file_data_available(){
#if SERCOMx_PERIPHERAL_ENABLED == 1
	return backup_file.available();
#else
	return 0;
#endif /* SERCOMx_PERIPHERAL_ENABLED */
}

#if PRUEBA_SD_MMC == 1
// Set up variables using the SD utility library functions:
Sd2Card card;
SdVolume volume;
SdFile root;

void card_info(int chipSelect) {

	while (!SerialUSB) {
		; // wait for serial port to connect. Needed for native USB port only
	}

	SerialUSB.print("\nInitializing SD card...\n");

	// we'll use the initialization code from the utility libraries
	// since we're just testing if the card is working!

	if (!card.init(SPI_HALF_SPEED, chipSelect)) {

		SerialUSB.println("initialization failed. Things to check:");
		SerialUSB.println("* is a card inserted?");
		SerialUSB.println("* is your wiring correct?");
		SerialUSB.println("* did you change the chipSelect pin to match your shield or module?");

		while (1);

	} else {
		SerialUSB.println("Wiring is correct and a card is present.");
	}

	// print the type of card
	SerialUSB.println();
	SerialUSB.print("Card type:         ");

	switch (card.type()) {

		case SD_CARD_TYPE_SD1:
		SerialUSB.println("SD1");
		break;

		case SD_CARD_TYPE_SD2:
		SerialUSB.println("SD2");
		break;

		case SD_CARD_TYPE_SDHC:
		SerialUSB.println("SDHC");
		break;

		default:
		SerialUSB.println("Unknown");

	}

	// Now we will try to open the 'volume'/'partition' - it should be FAT16 or FAT32
	if (!volume.init(card)) {

		SerialUSB.println("Could not find FAT16/FAT32 partition.\nMake sure you've formatted the card");
		while (1);
	}

	SerialUSB.print("Clusters:          ");
	SerialUSB.println(volume.clusterCount());
	SerialUSB.print("Blocks x Cluster:  ");
	SerialUSB.println(volume.blocksPerCluster());
	SerialUSB.print("Total Blocks:      ");
	SerialUSB.println(volume.blocksPerCluster() * volume.clusterCount());
	SerialUSB.println();

	// print the type and size of the first FAT-type volume

	uint32_t volumesize;
	SerialUSB.print("Volume type is:    FAT");
	SerialUSB.println(volume.fatType(), DEC);
	volumesize = volume.blocksPerCluster();    // clusters are collections of blocks
	volumesize *= volume.clusterCount();       // we'll have a lot of clusters
	volumesize /= 2;                           // SD card blocks are always 512 bytes (2 blocks are 1KB
	
	SerialUSB.print("Volume size (Kb):  ");
	SerialUSB.println(volumesize);
	SerialUSB.print("Volume size (Mb):  ");

	volumesize /= 1024;
	SerialUSB.println(volumesize);
	SerialUSB.print("Volume size (Gb):  ");
	SerialUSB.println((float)volumesize / 1024.0);
	SerialUSB.println("\nFiles found on the card (name, date and size in bytes): ");

	root.openRoot(volume);

	// list all files in the card with date and size
	root.ls(LS_R | LS_DATE | LS_SIZE);

	root.close();
}

#endif /*PRUEBA_SD_MMC*/