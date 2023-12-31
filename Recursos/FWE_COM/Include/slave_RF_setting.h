/*
 * slave_RF_setting.h
 *
 * Hardware: CMT2300A	Consult Datasheet http://www.pdf
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */


#ifndef SLAVE_RF_SETTING_H_
#define SLAVE_RF_SETTING_H_

#warning "Se desconoce la tolerancia del cristal montado en el RFM300, los parámetros RFPDK TX/RX Xtal. Tol. se dejan por defecto en +/-20, en AN141 se recomienda implementar uno con +/-10ppm (El usuario debe considerar el peor de los casos para establecer estos dos valores de tolerancia, que afectan a todos los ajustes de ancho de banda dentro del receptor.)"

#ifndef FSK_ 
 #ifndef GFSK
 #error "Undefined modulation scheme"
 #endif // GFSK
#endif // FSK_

typedef const unsigned char Bank;

/* ---------- CMT2300A Banks Configuration, configuration by specification ----------

	Generated by CMOSTEK RFPDK 1.53_Update4
	2023.02.11 17:00

	Data Rate                 = [300.0, 200.0, 100.0, 50.0] kbps	configurable en app_spbp_set.h
	Deviation                 = [100.0, 150.0, 200.0, 100.0] kHz	configurable en app_spbp_set.h
	
	Demodulation              = FSK, GFSK							configurable en app_spbp_set.h
	Gaussian BT (solo GFSK)   = [0.5, 0.8, 1.0]						configurable en app_spbp_set.h
	
	TRx Matching Network Type = [13, 20] dBm						configurable en app_spbp_set.h
	Tx Power                  = [+13, +20] dBm						configurable en app_spbp_set.h
	
    RF Performance            = LOW, MEDIUM, HIGH					configurable en task.h
	
	Packet Type               = 0 Fixed, 1 = Variable				configurable en task.h
    Payload Length            =										configurable en task.h
	
	Preamble Rx Size          = 0-31								configurable en task.h
	Preamble Tx Size          = 0-65535								configurable en task.h
    Preamble Unit             = [8, 4] bits							configurable en task.h
	Preamble Value            = 0-(2^(Preamble Unit)-1)				configurable en task.h

    Sync Size                 = [1, 8] byte							configurable en task.h
	Sync Value                = 0-(2^(Sync Size*8)-1)				configurable en task.h
	
    CRC Options               = CCITT-16, IBM-16, ITU-16			configurable en task.h
    CRC Seed                  = 0-32767								configurable en task.h

    RSSI Detect Mode          = always, at [PREAM, SYNC,PKT] _OK	configurable en task.h
    RSSI Filter Setting       = none, [4th, 8th, 16th, 32th] order	configurable en task.h
	RSSI Valid Source         =	PJD, RSSI, PJD & RSSI				configurable en task.h
	PJD Window                = [4, 6, 8 ,10] Jumps					configurable en task.h
--------------------------------------------------------------------*/

#ifdef FSK_
/* ---------- CMT2300A Banks Configuration, settings for all in modulation FSK ----------

     Generated by CMOSTEK RFPDK 1.53_Update4
     2023.02.11 17:00

     Mode                      = Advanced
     Part Number               = CMT2300A
     Frequency                 = 915.000 MHz
     Xtal Frequency            = 26.0000 MHz
     AGC                       = On
     Tx Xtal Tol.              = 20 ppm
     Rx Xtal Tol.              = 20 ppm
     Bandwidth                 = Auto-Select kHz
     CDR Type                  = Tracing
     CDR DR Range              = +/-6.3%
     AFC                       = On
     AFC Method                = Auto-Select
     Data Representation       = 0:F-low 1:F-high
     Rx Duty-Cycle             = Off
     Tx Duty-Cycle             = Off
     Sleep Timer               = Off
     Rx Timer                  = Off
     Rx Exit State             = STBY
     Tx Exit State             = STBY
     SLP Mode                  = Disable
     LFOSC Calibration         = On
     Xtal Stable Time          = 155 us
     RSSI Compare TH           = NA
     Data Mode                 = Packet
     Whitening                 = Disable
     Manchester                = Disable
     FEC                       = Enable
     FEC Type                  = x^3+x+1
     Tx Prefix Type            = 0
     Tx Packet Number          = 1
     Tx Packet Gap             = 32
     Payload Bit Order         = Start from msb
     Sync Tolerance            = None
     Sync Manchester           = Disable
     Node ID Mode              = None
     Node ID Err Mask          = Disable
     Node ID Free              = Disable
     CRC Range                 = Only Data
     CRC Swap                  = Start from MSB
     CRC Bit Invert            = Normal
     CRC Bit Order             = Start from bit 15
     Dout Mute                 = Off
     Dout Adjust Mode          = Disable
     Collision Detect          = Off
     LBD Threshold             = 2.4 V
     RSSI Offset               = 0
     RSSI Offset Sign          = 0
	 
-----------------------------------------------------------------------------------------*/

/* CMT Bank */
Bank rfpdk_cmt_bank[CMT_BANK_SIZE] = {
	0x00,
	0x66,
	0xEC,
#ifdef _13dbm
	0x1C,
#else
	#ifdef _20dbm
		0x1D,
	#else
		#error "Undefined TX power"
	#endif //_13dbm
#endif //_20dbm
	0x30,
	0x80,
	0x14,
	0x08,
	0x11,
	0x02,
	0x02,
	0x00,
};

/* System Bank */
Bank rfpdk_system_bank[SYSTEM_BANK_SIZE] = {
	0xAE,
	0xE0,
	0x35,
	0x00,
	0x00,
	0xF4,
	0x10,
	0xE2,
	0x42,
	0x20,
	0x18,
	0x81,
};

/* Frequency Bank */
Bank rfpdk_frequency_bank[FREQUENCY_BANK_SIZE] = {
	0x46,
	0x6D,
	0x80,
	0x86,
	0x46,
	0x62,
	0x27,
	0x16,
};

/* Data Rate Bank */
Bank rfpdk_data_rate_bank[DATA_RATE_BANK_SIZE] = {
#ifdef _300kbps
	0xBD,
	0xD0,
	0x7B,
	0x10,
	0x2C,
	0x20,
	0x0F,
	0x0B,
	0x1F,
	0x7D,
	0x29,
	0x20,
	0xE0,
	0x56,
	0x00,
	0x53,
	0x30,
	0x00,
	0xB4,
	0x00,
	0x00,
	0x01,
	0x00,
	0x00,
#else
	#ifdef _200kbps
		0x7E,
		0xE0,
		0x77,
		0x10,
		0x6C,
		0x12,
		0x17,
		0x0B,
		0x9F,
		0x7D,
		0x29,
		0x20,
		0xE0,
		0x82,
		0x00,
		0x53,
		0x28,
		0x00,
		0xB4,
		0x00,
		0x00,
		0x01,
		0x00,
		0x00,
	#else
			#ifdef _100kbps
			0x3F,
			0xF0,
			0x73,
			0x10,
			0xEC,
			0x24,
			0x1F,
			0x0B,
			0x9F,
			0x5A,
			0x29,
			0x29,
			0xC0,
			0x04,
			0x01,
			0x53,
			0x20,
			0x00,
			0xB4,
			0x00,
			0x00,
			0x01,
			0x00,
			0x00,
		#else
			#ifdef __50kbps
				0x1F,
				0xF8,
				0x71,
				0x10,
				0xEB,
				0x24,
				0x1F,
				0x0B,
				0x9F,
				0x4B,
				0x29,
				0x29,
				0xC0,
				0x08,
				0x02,
				0x53,
				0x18,
				0x00,
				0xB4,
				0x00,
				0x00,
				0x01,
				0x00,
				0x00,
			#else
				#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
};

/* Baseband Bank */
Bank rfpdk_baseband_bank[BASEBAND_BANK_SIZE] = {
	0x42,
	0x08,
	0x00,
	0x97,
	0x04,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0xCA,
	0x11,
	0xCA,
	0x00,
	0x3F,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x43,
	0x11,
	0xCA,
	0x60,
	0xFF,
	0x00,
	0x00,
	0x1F,
	0x10,
};

/* Tx Bank */
Bank rfpdk_tx_bank[TX_BANK_SIZE] = {
	0x50, // Implicit in demodulation type configuration
#ifdef _300kbps
	0x81,
	0x1F,
#else
	#ifdef _200kbps
		0x42,
		0x2F,
	#else
		#ifdef _100kbps
			0x03,
			0x3F,
		#else
			#ifdef __50kbps
				0x81,
				0x1F,
			#else
			#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
	0x00,
#ifdef _300kbps
	0x00,
#else
	#ifdef _200kbps
		0x00,
	#else
		#ifdef _100kbps
			0x00,
		#else
			#ifdef __50kbps
				0x02,
			#else
			#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
	0x30,
	0x00,
#ifdef _13dbm
	0x35,
	0x07,
#else
	#ifdef _20dbm
		0xC8,
		0x10,
	#else
		#error "Undefined TX power"
	#endif //_13dbm
#endif //_20dbm
#ifdef _300kbps
	0xFF,
#else
	#ifdef _200kbps
		0xFF,
	#else
		#ifdef _100kbps
			0x7F,
		#else
			#ifdef __50kbps
				0x3F,
			#else
			#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
	0x7F,
};
#endif // FSK_

#ifdef GFSK
/* ---------- CMT2300A Banks Configuration, settings for all in modulation GFSK ----------

     Generated by CMOSTEK RFPDK 1.53_Update4
     2023.02.11 17:00

     Mode                      = Advanced
     Part Number               = CMT2300A
     Frequency                 = 915.000 MHz
     Xtal Frequency            = 26.0000 MHz
     AGC                       = On
     Tx Xtal Tol.              = 20 ppm
     Rx Xtal Tol.              = 20 ppm
     Bandwidth                 = Auto-Select kHz
     CDR Type                  = Tracing
     CDR DR Range              = +/-6.3%
     AFC                       = On
     AFC Method                = Auto-Select
     Data Representation       = 0:F-low 1:F-high
     Rx Duty-Cycle             = Off
     Tx Duty-Cycle             = Off
     Sleep Timer               = Off
     Rx Timer                  = Off
     Rx Exit State             = STBY
     Tx Exit State             = STBY
     SLP Mode                  = Disable
     LFOSC Calibration         = On
     Xtal Stable Time          = 155 us
     RSSI Compare TH           = NA
     Data Mode                 = Packet
     Whitening                 = Disable
     Manchester                = Disable
     FEC                       = Enable
     FEC Type                  = x^3+x+1
     Tx Prefix Type            = 0
     Tx Packet Number          = 1
     Tx Packet Gap             = 32
     Payload Bit Order         = Start from msb
     Sync Tolerance            = None
     Sync Manchester           = Disable
     Node ID Mode              = None
     Node ID Err Mask          = Disable
     Node ID Free              = Disable
     CRC Range                 = Only Data
     CRC Swap                  = Start from MSB
     CRC Bit Invert            = Normal
     CRC Bit Order             = Start from bit 15
     Dout Mute                 = Off
     Dout Adjust Mode          = Disable
     Collision Detect          = Off
     LBD Threshold             = 2.4 V
     RSSI Offset               = 0
     RSSI Offset Sign          = 0
	 
-----------------------------------------------------------------------------------------*/

/* CMT Bank */
Bank rfpdk_cmt_bank[CMT_BANK_SIZE] = {
	0x00,
	0x66,
	0xEC,
#ifdef _13dbm
	0x1C,
#else
	#ifdef _20dbm
		0x1D,
	#else
		#error "Undefined TX power"
	#endif //_13dbm
#endif //_20dbm
	0x30,
	0x80,
	0x14,
	0x08,
	0x11,
	0x02,
	0x02,
	0x00,
};

/* System Bank */
Bank rfpdk_system_bank[SYSTEM_BANK_SIZE] = {
	0xAE,
	0xE0,
	0x35,
	0x00,
	0x00,
	0xF4,
	0x10,
	0xE2,
	0x42,
	0x20,
	0x18,
	0x81,
};

/* Frequency Bank */
Bank rfpdk_frequency_bank[FREQUENCY_BANK_SIZE] = {
	0x46,
	0x6D,
	0x80,
	0x86,
	0x46,
	0x62,
	0x27,
	0x16,
};

/* Data Rate Bank */
Bank rfpdk_data_rate_bank[DATA_RATE_BANK_SIZE] = {
#ifdef _300kbps
	0xBD,
	0xD0,
	0x7B,
	0x10,
	0x2C,
	0x20,
	0x0F,
	0x0B,
	0x1F,
	0x7D,
	0x29,
	0x20,
	0xE0,
	0x56,
	0x00,
	0x53,
	0x30,
	0x00,
	0xB4,
	0x00,
	0x00,
	0x01,
	0x00,
	0x00,
#else
	#ifdef _200kbps
		0x7E,
		0xE0,
		0x77,
		0x10,
		0x6C,
		0x12,
		0x17,
		0x0B,
		0x9F,
		0x7D,
		0x29,
		0x20,
		0xE0,
		0x82,
		0x00,
		0x53,
		0x28,
		0x00,
		0xB4,
		0x00,
		0x00,
		0x01,
		0x00,
		0x00,
	#else
			#ifdef _100kbps
			0x3F,
			0xF0,
			0x73,
			0x10,
			0xEC,
			0x24,
			0x1F,
			0x0B,
			0x9F,
			0x5A,
			0x29,
			0x29,
			0xC0,
			0x04,
			0x01,
			0x53,
			0x20,
			0x00,
			0xB4,
			0x00,
			0x00,
			0x01,
			0x00,
			0x00,
		#else
			#ifdef __50kbps
				0x1F,
				0xF8,
				0x71,
				0x10,
				0xEB,
				0x24,
				0x1F,
				0x0B,
				0x9F,
				0x4B,
				0x29,
				0x29,
				0xC0,
				0x08,
				0x02,
				0x53,
				0x18,
				0x00,
				0xB4,
				0x00,
				0x00,
				0x01,
				0x00,
				0x00,
			#else
				#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
};

/* Baseband Bank */
Bank rfpdk_baseband_bank[BASEBAND_BANK_SIZE] = {
	0x42,
	0x08,
	0x00,
	0x97,
	0x04,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0xCA,
	0x11,
	0xCA,
	0x00,
	0x3F,
	0x00,
	0x00,
	0x00,
	0x00,
	0x00,
	0x43,
	0x11,
	0xCA,
	0x60,
	0xFF,
	0x00,
	0x00,
	0x1F,
	0x10,
};

/* Tx Bank */
Bank rfpdk_tx_bank[TX_BANK_SIZE] = {
#ifdef BT05_
	0x70,	// Implicit in demodulation type configuration
#else
	#ifdef BT08_
		0xB0,
	#else
		#ifdef BT10_
			0xF0,
		#else
			#error "Undefined Gaussian BT"
		#endif //BT10_
	#endif // BT08_
#endif // BT05_
#ifdef _300kbps
	0x81,
	0x1F,
#else
	#ifdef _200kbps
		0x42,
		0x2F,
	#else
		#ifdef _100kbps
			0x03,
			0x3F,
		#else
			#ifdef __50kbps
				0x81,
				0x1F,
			#else
			#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
	0x00,
#ifdef _300kbps
	0x00,
#else
	#ifdef _200kbps
		0x00,
	#else
		#ifdef _100kbps
			0x00,
		#else
			#ifdef __50kbps
				0x02,
			#else
			#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
	0x30,
	0x00,
#ifdef _13dbm
	0x35,
	0x07,
#else
	#ifdef _20dbm
		0xC8,
		0x10,
	#else
		#error "Undefined TX power"
	#endif //_13dbm
#endif //_20dbm
#ifdef _300kbps
	0xFF,
#else
	#ifdef _200kbps
		0xFF,
	#else
		#ifdef _100kbps
			0x7F,
		#else
			#ifdef __50kbps
				0x3F,
			#else
			#error "Undefined data rate"
			#endif //_50kbps
		#endif //_100kbps
	#endif //_200kbps
#endif //_300kbps
	0x7F,
};
#endif // GFSK

#endif /* SLAVE_RF_SETTING_H_ */