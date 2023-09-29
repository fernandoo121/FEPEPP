/*
 * spi_2.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
 
/* SERCOM_SPI_2 bus private definition */
#if defined(PCB_ULT)
 #define SPI_SERCOM			SERCOM2
 #define SPI_Handler		SERCOM2_Handler
 #define SPI_GCLK_			GCLK_CLKCTRL_ID_SERCOM2_CORE
 #define SPI_IRQn			SERCOM2_IRQn
 #define SPI_IRQn_priority	SERCOM2_IRQn_app_priority
 
 // SPI_PAD3 SERCOM2/PAD[3]_C  (Pin PA15/D5)
 #define PORT_MISO		PORT_PA15
 #define PIN_MISO		PIN_PA15
 #define PMUX_SPI_MISO	PORT_PMUX_PMUXO(PORT_PMUX_PMUXO_C_Val)

 // SPI_PAD0 SERCOM2/PAD[0]_D  (Pin PA08/D4)
 #define PORT_MOSI		PORT_PA08
 #define PIN_MOSI		PIN_PA08
 #define PMUX_SPI_MOSI	PORT_PMUX_PMUXE(PORT_PMUX_PMUXO_D_Val)

 // SPI_SCK SERCOM2/PAD[1]_D  (Pin PA09/D3)
 #define PORT_SCK		PORT_PA09
 #define PIN_SCK		PIN_PA09
 #define PMUX_SPI_SCK	PORT_PMUX_PMUXO(PORT_PMUX_PMUXO_D_Val)
#endif /* PCB_ULT */

 #define SPI_TRANS_us  (((float) 1000000 / (float) F_SPI_2) * (float) 8) // Tiempo de transaccion estimado
 #define SPI_MAX_WAIT_us	((float) 3 * (SPI_TRANS_us * (float) data_packet_size))

 #if defined(PCB_ULT)
  // SPI Bus variables
  static unsigned char *ptr_spi_buf_tx;
  static unsigned char *ptr_spi_buf_rx;
  static unsigned char pos_spi_buf_tx;
  static unsigned char pos_spi_buf_rx;
  static unsigned char spi_buf_size;
  static signed char state_spi_bus = SPI_DOING;
 #endif /* PCB_ULT */


/*
 * SPI_2 bus private functions
 */

void PORT_SPI_2_int(){
#if defined(PCB_ULT)
	// SPI1_MOSI SERCOMx (Pin SDIO Módulo Radiofrecuencia)
	PORT->Group[PIN_MOSI/32].DIRSET.reg											= PORT_MOSI;	// Data Direction: Output.
	PORT->Group[PIN_MOSI/32].PINCFG[(PIN_MOSI - ((PIN_MOSI/32)*32))].bit.INEN	= LOW;	// Read-Back Input Enable.
	PORT->Group[PIN_MOSI/32].PINCFG[(PIN_MOSI - ((PIN_MOSI/32)*32))].bit.PULLEN	= LOW;	// Pull Enable.
	PORT->Group[PIN_MOSI/32].PINCFG[(PIN_MOSI - ((PIN_MOSI/32)*32))].bit.PMUXEN	= HIGH;	// Peripheral Multiplexer Enable (REG_OUT control).
	PORT->Group[PIN_MOSI/32].PMUX[(PIN_MOSI - ((PIN_MOSI/32)*32))/2].reg		|= PMUX_SPI_MOSI;	// Peripheral Multiplexing Selection
	
	// SPI1_MISO SERCOMx (Pin SDIO Módulo Radiofrecuencia)
	PORT->Group[PIN_MISO/32].DIRCLR.reg											= PORT_MISO;	// Data Direction: Input.
	PORT->Group[PIN_MISO/32].PINCFG[(PIN_MISO - ((PIN_MISO/32)*32))].bit.INEN	= LOW;	// Read-Back Input Enable.
	PORT->Group[PIN_MISO/32].PINCFG[(PIN_MISO - ((PIN_MISO/32)*32))].bit.PULLEN	= LOW;	// Pull Enable.
	PORT->Group[PIN_MISO/32].PINCFG[(PIN_MISO - ((PIN_MISO/32)*32))].bit.PMUXEN	= HIGH;	// Peripheral Multiplexer Enable (REG_OUT control).
	PORT->Group[PIN_MISO/32].PMUX[(PIN_MISO - ((PIN_MISO/32)*32))/2].reg		|= PMUX_SPI_MISO;	// Peripheral Multiplexing Selection
	
	// SPI1_SCK SERCOMx (Pin SCLK Módulo Radiofrecuencia)
	PORT->Group[PIN_SCK/32].DIRSET.reg										 = PORT_SCK;	// Data Direction: Output.
	PORT->Group[PIN_SCK/32].PINCFG[(PIN_SCK - ((PIN_SCK/32)*32))].bit.INEN	 = LOW;	// Read-Back Input Enable.
	PORT->Group[PIN_SCK/32].PINCFG[(PIN_SCK - ((PIN_SCK/32)*32))].bit.PULLEN = LOW;	// Pull Enable.
	PORT->Group[PIN_SCK/32].PINCFG[(PIN_SCK - ((PIN_SCK/32)*32))].bit.PMUXEN = HIGH;	// Peripheral Multiplexer Enable (REG_OUT control).
	PORT->Group[PIN_SCK/32].PMUX[(PIN_SCK - ((PIN_SCK/32)*32))/2].reg		 |= PMUX_SPI_SCK;	// Peripheral Multiplexing Selection

#endif /* PCB_ULT */
 }

void SERCOM_SPI_2_int(){
#if defined(PCB_ULT)

	// SERCOMx disable
	SPI_SERCOM->SPI.CTRLA.bit.ENABLE = LOW;
	
	// NVIC config
	NVIC_DisableIRQ(SPI_IRQn);	
	
	// Setting Generic Clock SERCOMx (CORE)
	GCLK->CLKCTRL.reg = GCLK_CLKCTRL_ID(SPI_GCLK_) | GCLK_CLKCTRL_GEN_GCLK3 | GCLK_CLKCTRL_CLKEN;
	while(GCLK->STATUS.bit.SYNCBUSY == HIGH);		// Wait for synchronization of registers between the clock domains
	
	// SERCOMx software reset
	SPI_SERCOM->SPI.CTRLA.bit.SWRST = HIGH;
	while(SPI_SERCOM->SPI.SYNCBUSY.bit.SWRST);

	// SERCOMx Operating Mode
	SPI_SERCOM->SPI.CTRLA.bit.MODE = SERCOM_SPI_CTRLA_MODE_SPI_MASTER_Val;

	// SERCOMx Transfer Mode
	SPI_SERCOM->SPI.CTRLA.bit.CPOL = LOW;	// Leading Edge  = Rising, sample
	SPI_SERCOM->SPI.CTRLA.bit.CPHA = LOW;	// Trailing Edge = Falling, change

	// SERCOMx Frame Format
	SPI_SERCOM->SPI.CTRLA.bit.FORM = 0x00;	// SPI frame without address
	
	// SERCOMx Data I/O Pinout
	SPI_SERCOM->SPI.CTRLA.bit.DIPO = (0x03);	// MISO = PAD[3]
	SPI_SERCOM->SPI.CTRLA.bit.DOPO = (0x00);	// MOSI = PAD[0] SCK = PAD[1] 
	
	// SERCOMx Data Order
	SPI_SERCOM->SPI.CTRLA.bit.DORD = LOW;	// MSB is transferred first.
	
	// 	// SERCOMx Control B
	SPI_SERCOM->SPI.CTRLB.reg = SERCOM_SPI_CTRLB_CHSIZE(0x00) |	// Character Size 8 bits
							 /*SERCOM_SPI_CTRLB_MSSEN |*/		// Master Hardware Slave Select Enable
							 SERCOM_SPI_CTRLB_RXEN;				// Receiver Enable
	while(SPI_SERCOM->SPI.SYNCBUSY.bit.CTRLB == HIGH);		// Wait for synchronization of registers between the clock domains
	
	// SERCOMx Baud Rate
	SPI_SERCOM->SPI.BAUD.reg = SERCOM_SPI_BAUD_BAUD((F_GCLK_SERCOMx_CORE/(2*F_SPI_2))-1);	// = (F_GCLK_SERCOMx_CORE/(2*F_BAUS))-1 : F_GCLK_SERCOMx_CORE = 8MHz y F_BAUS = 500KHz [min. 15KHz (BAUD = 255) max. 4MHz (BAUD = 0)]
	
	// SERCOMx Debug Run Mode
	SPI_SERCOM->SPI.DBGCTRL.bit.DBGSTOP = HIGH;

	// NVIC config
	NVIC_DisableIRQ(SPI_IRQn);
	NVIC_ClearPendingIRQ(SPI_IRQn);
	NVIC_SetPriority(SPI_IRQn, SPI_IRQn_priority);
	NVIC_EnableIRQ(SPI_IRQn);
	
	// SERCOMx enable
	SPI_SERCOM->SPI.CTRLA.bit.ENABLE = HIGH;
	while(SPI_SERCOM->SPI.SYNCBUSY.bit.ENABLE == HIGH);		// Wait for synchronization of registers between the clock domains
	
#endif /* PCB_ULT */
}


/*
 * SPI_2 bus public functions
 */


signed char SPI_2_transaction(unsigned char *tx_data_packet, unsigned char *rx_data_packet, unsigned char data_packet_size, unsigned char pin, unsigned int port){

	signed char result_;
	unsigned long wait_ = CURRENT_TIME_US;
	
#if defined(PCB_ULT)
	
	pos_spi_buf_tx = pos_spi_buf_rx = 0;
	ptr_spi_buf_tx = tx_data_packet;
	ptr_spi_buf_rx = rx_data_packet;
	spi_buf_size = data_packet_size;

	/* Slave_select line is made into low to start the communication */
	PORT->Group[pin/32].OUTCLR.reg = port;
#if RETARDOS_SPI3_RF == 1
	DELAY_US((1000000ul/F_SPI_2)*1.5); // CS = HIGH t > 1 clk (RF hardware requirement)
	#warning "RETARDOS_SPI3_RF ON"
#else
	#warning "RETARDOS_SPI3_RF OFF"
#endif

	SPI_SERCOM->SPI.INTENSET.reg = SERCOM_SPI_INTENSET_DRE | SERCOM_SPI_INTENSET_RXC;
	
	while(state_spi_bus == SPI_DOING && (CURRENT_TIME_US - wait_) < SPI_MAX_WAIT_us);
		
	DELAY_US((1000000ul/F_SPI_2)); // Wait for transaction complete

#if RETARDOS_SPI3_RF == 1
  	if(pin != PIN_RF_FCSB)
  		DELAY_US(((1000000ul/F_SPI_2)*1.5));	// CS = LOW t > 1 clk (RF hardware requirement)
   	else
   		DELAY_US(3);	// FCSB = LOW t > 2 us  (RF hardware requirement)
#endif
		 
	/* Slave_select line is made into high to end the communication */
	PORT->Group[pin/32].OUTSET.reg = port;
	
	result_ = state_spi_bus;
	
	#if RAW_TLM_TASK3_ENABLED == 1
		//declaración opcional
	#else
		#if DEPURACION_TASK3_ENABLED == 1
 		//sprintf(debug_string_, "%lu us = SPI_END (%d) \n", (CURRENT_TIME_US - wait_), state_spi_bus);
 		//serialUSB_print_link(debug_string_); /* DEBUGGING */
		#endif /*DEPURACION_TASKx_ENABLED*/
	#endif /*RAW_TLM_TASKx_ENABLED*/
	
	state_spi_bus = SPI_DOING;
#else
	result_ = SPI_FAIL; 
#endif /* PCB_ULT */

	return result_;
}

void SPI_2_failure(){

	static char intentos = NOTHING;

	if (state_spi_bus == SPI_DOING){
		SET_indication_vector_(ID_SPI_2_FailureWarning_master);
		SERCOM_SPI_2_int();
		
	} else if (state_spi_bus == SPI_FAIL){
		SET_indication_vector_(ID_SPI_2_FailureWarning_slave);
		
		if(intentos >= 3){
			SPI_2_SLAVE_1__FAILURE();
			intentos = NOTHING;
		} else
			intentos++;
		
	} else
		SET_indication_vector_(ID_SPI_2_FailureWarning_slave);

}

/*
 * NVIC Handler
 */
#if defined(PCB_ULT)
void SPI_Handler(void){
	
	// Data register empty interrupt checking
	if (SPI_SERCOM->SPI.INTFLAG.bit.DRE && SPI_SERCOM->SPI.INTENSET.bit.DRE){
		SPI_SERCOM->SPI.DATA.reg = ptr_spi_buf_tx[pos_spi_buf_tx++];
		if (pos_spi_buf_tx == spi_buf_size){
			SPI_SERCOM->SPI.INTENCLR.reg = SERCOM_SPI_INTENCLR_DRE;  // Data regsiter empty interrupt is disabled
		}
	}
	// Receive complete interrupt checking
	if (SPI_SERCOM->SPI.INTFLAG.bit.RXC && SPI_SERCOM->SPI.INTENSET.bit.RXC) {
		ptr_spi_buf_rx[pos_spi_buf_rx++] = SPI_SERCOM->SPI.DATA.reg;
		if (pos_spi_buf_rx == spi_buf_size) {
			SPI_SERCOM->SPI.INTENCLR.reg = SERCOM_SPI_INTENCLR_RXC; // Receive complete interrupt is disabled
			state_spi_bus = SPI_DONE;
		}
	}
	
	// Error interrupt checking
	if (SPI_SERCOM->SPI.INTFLAG.bit.ERROR){
 		state_spi_bus = SPI_FAIL;
		SPI_SERCOM->SPI.INTFLAG.reg |= SERCOM_SPI_INTFLAG_ERROR; // Error interrupt is cleaned
	}
}
#endif /* PCB_ULT */