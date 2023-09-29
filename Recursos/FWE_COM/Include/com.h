/*
 * com.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef COM_H_
#define COM_H_

 #include "com_set.h"

 /* Configuración modem RF */

 #define FIFO_LENG 64	// The FIFO is merge into one 64-byte FIFO or it is divided into 2 separate 32-byte.

 #define HIGH___RF_Performance	 // RF Performance:
								 //					LOW____RF_Performance
								 //					MEDIUM_RF_Performance
								 //					HIGH___RF_Performance
 
 #define DATA_MODE_VALUE		2		// Packet Type ( 1 = Direct Mode, 2 = Packet Mode)

 #define PKT_TYPE_VALUE			1		// Packet length type 0 = Fixed packet length 1 = Variable packet length
 #if PKT_TYPE_VALUE == 0
 #define PAYLOAD_LENG_VALUE		FIFO_LENG		// Payload Length = Data
 #else
 #define PAYLOAD_LENG_VALUE		(FIFO_LENG - 1)	// Payload Length = Length Byte + Data
 #endif
 
 #define RX_PREAM_SIZE_VALUE	8		// Preamble Rx Size (Can be configured to be 0-31 units in length)
										// !!! Reconfigurar ESPERA_Tt y ESPERA_Td si se modifica.
 #define TX_PREAM_SIZE_VALUE	8		// Preamble Tx Size (Can be configured to be 0-65535 units in length)
 #define PREAM_LENG_UNIT_VALUE	0x0		// Preamble Unit (0 = Unit is 8bits, 1 = unit is 4 bits.)
 #define PREAM_VALUE_VALUE	0xAA	// Preamble Value (8bit is valid when PREAM_LEN_UNIT = 0, only <3:0> is valid when)

 #define SYNC_SIZE_VALUE	3			// Sync Size (1 a 8 byte)
 #define SYNC_VALUE_VALUE	0xCA11CA	// Sync Value (Can be configured to be 0-(2^(Sync Size*8)-1))

 #define CRC_TYPE_VALUE		1			// CRC Option (0:CCITT-16, 1:IBM-16, 2:ITU-16 (equals the reversed CCITT-16))
 #define CRC_SEED_VALUE		0xCA11		// CRC Seed (Can be configured to be 0-32767)

 #define RSSI_DET_SEL_VALUE		3	// RSSI Detect Mode (0: always, 1: only done when PREAM_OK active, 2: only done when SYNC_OK active, 3: only done when PKT_OK active)
 #define RSSI_AVG_MODE_VALUE	0	// RSSI Filter Setting (0: none, 1: 4th order, 2: 8th order, 3: 16th order, 4: 32th order)
 #define CCA_INT_SEL_VALUE		0   // RSSI Valid Source:
									//						0: Determine whether there is a signal by PJD's
									//						2: Option 0 and option 1 are both met at the same time.
 
 #define PJD_WIN_SEL_VALUE	2    // PJD Window:
								 //				0: 4 Jumps
								 //				1: 6 Jumps
								 //				2: 8 Jumps
								 //				3: 10 Jumps

 /* Configuración protocolo de aplicación */

#define SIZE_TRAMA PAYLOAD_LENG_VALUE // En datos primeros dos byte se define para indicar el identificador de trama.
#if PKT_TYPE_VALUE == 0
 #define SIZE_ASK SIZE_TRAMA
#else
 #define SIZE_ASK (1 + 2) // En ask primer byte se define para indicar el identificador de acuso recibo, resto para mensajes.
#endif

#if SIZE_TRAMA > 64 || SIZE_ASK > 64
 #error "Max. PAYLOAD_LENG_VALUE = 64"
#endif

#if SIMULAR_PROTOCOLO_COM_X_USB == 1
 #define ESPERA_Tt 1000		// Tiempo máximo en ms necesario para transmitir el ASK y recibir una trama.
#else
 #define t_tx 1 // Tiempo que demora la aplicación en poner modem en TX.
 #define t_rx 1 // Tiempo que demora la aplicación en poner modem en RX.
 #define t_fifo_trama (float) (((float) ((float) 1000ul/(float) F_SPI_2)*(float) (8.0*SIZE_TRAMA))*1.5) // Tiempo que demora la aplicación al llenar/vaciar fifo con trama.
 #define t_fifo_ask (float) (((float) ((float) 1000ul/(float) F_SPI_2)*(float) (8.0*SIZE_ASK))*1.5) // Tiempo que demora la aplicación al llenar/vaciar fifo con acuso de recibo.
 #ifdef _300kbps
   #define t_byte	0.052812						// Tiempo de un byte en el aire.
   #define t_trama (t_byte * (float)SIZE_TRAMA)		// Tiempo de una trama en el aire.
   #define t_ask (t_byte * (float)SIZE_ASK)			// Tiempo de trama acuso recibo en el aire.
   #define ESPERA_Tt (t_fifo_trama + t_tx + t_trama + t_fifo_trama + t_fifo_ask + t_rx + t_ask + t_fifo_ask)
 #else
  #ifdef _200kbps
   #define t_byte	0.079219						// Tiempo de un byte en el aire.
   #define t_trama (t_byte * (float)SIZE_TRAMA)		// Tiempo de una trama en el aire.
   #define t_ask (t_byte * (float)SIZE_ASK)			// Tiempo de trama acuso recibo en el aire.
   #define ESPERA_Tt (t_fifo_trama + t_tx + t_trama + t_fifo_trama + t_fifo_ask + t_rx + t_ask + t_fifo_ask)
  #else
   #ifdef _100kbps
	#define t_byte	0.158436						// Tiempo de un byte en el aire.
	#define t_trama (t_byte * (float)SIZE_TRAMA)	// Tiempo de una trama en el aire.
	#define t_ask (t_byte * (float)SIZE_ASK)		// Tiempo de trama acuso recibo en el aire.
    #define ESPERA_Tt (t_fifo_trama + t_tx + t_trama + t_fifo_trama + t_fifo_ask + t_rx + t_ask + t_fifo_ask)
   #else
    #ifdef __50kbps
	 #define t_byte	0.316875						// Tiempo de un byte en el aire.
	 #define t_trama (t_byte * (float)SIZE_TRAMA)	// Tiempo de una trama en el aire.
	 #define t_ask (t_byte * (float)SIZE_ASK)		// Tiempo de trama acuso recibo en el aire.
	 #define ESPERA_Tt (t_fifo_trama + t_tx + t_trama + t_fifo_trama + t_fifo_ask + t_rx + t_ask + t_fifo_ask)
    #else
     #error "Undefined data rate"
    #endif //_50kbps
   #endif //_100kbps
  #endif //_200kbps
#endif //_300kbps
#endif /* SIMULAR_PROTOCOLO_COM_X_USB */

 #define ESPERA_RECEPCION_MAX ((float) SIZE_METADATA_SPBP / (float) SIZE_TRAMA)

 #define ID_ASK 'A'
 enum ask_{
	ID_ASK_pos,
	MENSAJE_pos
 };

 enum trama_{
	ID_TRAMA_TIPO_pos,
	ID_TRAMA_NUM_pos,
	METADATOS_pos
 };

 #define TRAMA_INICIAL		'S' // START
 #define TRAMA_INTERMEDIA	'I' // INTERMEDIATE
 #define TRAMA_FINAL			'E' // END


 enum resultado_resepcion{
	EXITO,
	RECIBIENDO,
	FRACASO,
 };

/* Mapeo de pines */


 #ifdef __cplusplus
 extern "C" {
 #endif

	char resepcion_trama(unsigned char* trama_);
	char resepcion_metadatos(struct data_task_0 *metadatos);

 #ifdef __cplusplus
 }
 #endif
#endif /* COM_H_ */