/*
 * sercom.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */


#ifndef SERCOM_H_
#define SERCOM_H_

 /* 
  * SPI_1 bus public definition 
  */

 #ifdef PCB_ULT
  #define PIN_SD	(38ul) //PIN_ATN ArduinoCore (Pin PA13)
 #endif /* PCB_ULT */

 /* 
  * SPI_2 bus public definition 
  */

 #define F_GCLK_SERCOMx_CORE	8000000ul		//
 #define F_SPI_2				1000000ul		// 8MHz GEN_GCLK3 : 16KHz < F_SPI2 < 4MHz

 enum state_spi_bus{
	SPI_DOING,
	SPI_DONE,
	SPI_FAIL = -1,
 };

 #ifdef PCB_ULT
  #define PIN_SD	(38ul) //PIN_ATN ArduinoCore (Pin PA13)
 #endif /* PCB_ULT */

 #ifdef __cplusplus
 extern "C" {
 #endif
 
	 /*
	  * Private functions
	  */
	
		// SPI_2
		void PORT_SPI_2_int();
		void SERCOM_SPI_2_int();

	 /*
	  * Public functions
	  */
  	
		// SPI_2
		signed char SPI_2_transaction(unsigned char *tx_data_packet, unsigned char *rx_data_packet, unsigned char data_packet_size, unsigned char pin, unsigned int port);
		void SPI_2_failure();

 #ifdef __cplusplus
 }
 #endif

#endif /* SERCOM_H_ */