/*
 * slave_RF_operation.c
 *
 * Created: 14/8/2023 17:38:12
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "slave_RF_operation.h"

enum buffer_{
	ADDRESS,
	DATA,
	LENG_BUFF,
};

#define LENG_BYTE 1

/*
 * Especifica la llamada a funciones de firmware SPI para marco de escritura de los bancos de registros
 */
void marco_escritura_banco(unsigned char base_addr, const unsigned char bank[], unsigned char len){
	
    for(unsigned char i = 0; i < len; i++)
		marco_escritura_registros(base_addr + i, bank[i]);
}

/*
 * Especifica la llamada a funciones de firmware SPI para marco de escritura de registros individuales 
 */
void marco_escritura_registros(unsigned char addr_register, unsigned char data_){

 	unsigned char buffer_[LENG_BUFF];
 	
 	buffer_[ADDRESS]  = (addr_register & ~(1 << 7)); // r/w = 0 + Address Register
 	buffer_[DATA] = data_;
	   
    RF_FCSB_HIGH;

    while(SPI_2_transaction(buffer_, buffer_, LENG_BUFF, PIN_RF_CSB, PORT_RF_CSB) != SPI_DONE){
		SPI_2_FailureAttention_;
	}
}

/*
 * Especifica la llamada a funciones de firmware SPI para marco de lectura de registros individuales 
 */
void marco_lectura_registros(unsigned char addr_register, unsigned char *ptr_data){
	
	unsigned char buffer_[LENG_BUFF];
	
	buffer_[ADDRESS]  = (addr_register | (1 << 7)); // r/w = 1 + Address Register
	buffer_[DATA] = 0x00;
	
    RF_FCSB_HIGH;
   
    while(SPI_2_transaction(buffer_, buffer_, LENG_BUFF, PIN_RF_CSB, PORT_RF_CSB) != SPI_DONE){
		SPI_2_FailureAttention_;
	}
   *ptr_data = buffer_[DATA];
}

/*
 * Especifica la llamada a funciones de firmware SPI para marco de escritura del FIFO
 */
void marco_escritura_FIFO(unsigned char* data_, unsigned char data_len){	

	for(unsigned int i = 0; i < data_len; i++){
		
	    RF_CSB_HIGH;

		while(SPI_2_transaction(&data_[i], &data_[i], LENG_BYTE, PIN_RF_FCSB, PORT_RF_FCSB) != SPI_DONE){
			SPI_2_FailureAttention_;
		}
#if RETARDOS_SPI3_RF == 1
		DELAY_US(4); /* FCSB = HIGH t > 4 us */
#endif
    }
}

/*
 * Especifica la llamada a funciones de firmware SPI para marco de lectura del FIFO
 */
unsigned char marco_lectura_FIFO(unsigned char* data_, unsigned char data_len){

#if PKT_TYPE_VALUE == 1
	unsigned char payload_length_byte;
	
	while(SPI_2_transaction(&payload_length_byte, &payload_length_byte, LENG_BYTE, PIN_RF_FCSB, PORT_RF_FCSB) != SPI_DONE){
		SPI_2_FailureAttention_;
	}
#endif

	for(unsigned int i = 0; i < data_len; i++){
		
		RF_CSB_HIGH;

		while(SPI_2_transaction(&data_[i], &data_[i], LENG_BYTE, PIN_RF_FCSB, PORT_RF_FCSB) != SPI_DONE){
			SPI_2_FailureAttention_;
		}
#if RETARDOS_SPI3_RF == 1
		DELAY_US(4); /* FCSB = HIGH t > 4 us */
#endif
	}
	
#if PKT_TYPE_VALUE == 1
	return payload_length_byte;
#else
	return data_len;
#endif
}

/*
 * ...
 */
void soft_reset(){
	
	unsigned char reg_tmp;
	
	marco_escritura_registros(SOFT_RESET_ADDR, SOFT_RESET_MASK); // Soft reset command
	DELAY_MS(20);

retry:
	marco_lectura_registros(CUS_MODE_STA, &reg_tmp);
	
	if((reg_tmp & MASK_CHIP_MODE_STA) != STA_SLEEP){	// Confirm that the chip is reset and remains in the SLEEP state
		RF_FailureAttention_;
		DELAY_US(10);
		goto retry;
	}
}

/*
 * ...
 */
void ack_packet_format(char state){
		
	unsigned char reg_tmp;
		
	// Back AUTO_ACK_EN
	marco_lectura_registros(CUS_PKT14, &reg_tmp);
	
	if (state == FALSE)
		reg_tmp &= (~MASK_AUTO_ACK_EN); // clean AUTO_ACK_EN
	else
		reg_tmp |= MASK_AUTO_ACK_EN;  // set AUTO_ACK_EN
	marco_escritura_registros(CUS_PKT14, reg_tmp);
}

/*
 * ...
 */
void packet_length(unsigned char length){
	
	marco_escritura_registros(CUS_PKT15, (length - 1));
}

/*
 * ...
 */
void go_sleep(){
	
	unsigned char reg_tmp;
	unsigned long time_ = CURRENT_TIME_MS;

retry:
	marco_escritura_registros(CUS_MODE_CTL, GO_SLEEP); // Send the go_sleep command

	marco_lectura_registros(CUS_MODE_STA, &reg_tmp);
	
	if((reg_tmp & MASK_CHIP_MODE_STA) != STA_SLEEP){ // Confirm that the chip is in the SLEEP state
		DELAY_US(90);
		
		if (CURRENT_TIME_MS - time_ > 500){
			RF_FailureAttention_;
		}
		goto retry;
	}	
}

/*
 * ...
 */
void go_stby(){
	
	unsigned char reg_tmp;
	unsigned long time_ = CURRENT_TIME_MS;
	
retry:
	marco_escritura_registros(CUS_MODE_CTL, GO_STBY); // Send the go_stby command

	marco_lectura_registros(CUS_MODE_STA, &reg_tmp);

	if((reg_tmp & MASK_CHIP_MODE_STA) != STA_STBY){ // Confirm that the chip is in the STBY state
		DELAY_US(90);
		
		if (CURRENT_TIME_MS - time_ > 500){
			RF_FailureAttention_;
		}
		goto retry;
	}
}

/*
 * ...
 */
void go_tx(){
	
	unsigned char reg_tmp;
	unsigned long time_ = CURRENT_TIME_MS;
	
retry:
	marco_escritura_registros(CUS_MODE_CTL, GO_TX); // Send the go_tx command

	marco_lectura_registros(CUS_MODE_STA, &reg_tmp);

	if((reg_tmp & MASK_CHIP_MODE_STA) != STA_TX){ // Confirm that the chip is in the TX state
		DELAY_US(90);
		
		if (CURRENT_TIME_MS - time_ > 500){
			RF_FailureAttention_;
		}
		goto retry;
	}
}

/*
 * ...
 */
void go_rx(){
	
	unsigned char reg_tmp;
	unsigned long time_ = CURRENT_TIME_MS;
	
retry:
	marco_escritura_registros(CUS_MODE_CTL, GO_RX); // Send the go_rx command

	marco_lectura_registros(CUS_MODE_STA, &reg_tmp);

	if((reg_tmp & MASK_CHIP_MODE_STA) != STA_RX){ // Confirm that the chip is in the RX state
		DELAY_US(90);
		
		if (CURRENT_TIME_MS - time_ > 500){
			RF_FailureAttention_;
		}
		goto retry;
	}
}

void go_switch(){
	
	unsigned char reg_tmp;
	unsigned char current_state;
	
	marco_lectura_registros(CUS_MODE_STA, &current_state);
	
retry:
	marco_escritura_registros(CUS_MODE_CTL, GO_SWITCH); // Send the go_switch command

	marco_lectura_registros(CUS_MODE_STA, &reg_tmp);
	
	switch ((current_state & MASK_CHIP_MODE_STA)){
	case STA_RX:
				if((reg_tmp & MASK_CHIP_MODE_STA) != STA_TX){ // Confirm that the chip is in the TX state
					RF_FailureAttention_;
					DELAY_US(10);
					goto retry;
				}				
				break;
	case STA_TX:
				if((reg_tmp & MASK_CHIP_MODE_STA) != STA_RX){ // Confirm that the chip is in the RX state
					RF_FailureAttention_;
					DELAY_US(10);
					goto retry;
				}				
				break;
	default: 
			while(1){
				RF_FailureAttention_;
			}
	}
}

/*
 * ...
 */
void clear_interrupt_flags(){
	
	unsigned char nFlag1, nFlag2;
	unsigned char nClr1 = 0;
	unsigned char nClr2 = 0;

	marco_lectura_registros(CUS_INT_FLAG, &nFlag1);
	marco_lectura_registros(CUS_INT_CLR1, &nFlag2);

	if(MASK_LBD_FLG & nFlag1)
		nClr2 |= MASK_LBD_CLR;         /* Clear LBD_FLG */

	if(MASK_COL_ERR_FLG & nFlag1)
		nClr2 |= MASK_PKT_DONE_CLR;    /* Clear COL_ERR_FLG by PKT_DONE_CLR */

	if(MASK_PKT_ERR_FLG & nFlag1)
		nClr2 |= MASK_PKT_DONE_CLR;    /* Clear PKT_ERR_FLG by PKT_DONE_CLR */

	if(MASK_PREAM_OK_FLG & nFlag1) 
		nClr2 |= MASK_PREAM_OK_CLR;    /* Clear PREAM_OK_FLG */
		
	if(MASK_SYNC_OK_FLG & nFlag1)
		nClr2 |= MASK_SYNC_OK_CLR;    /* Clear SYNC_OK_FLG */

	if(MASK_NODE_OK_FLG & nFlag1)
		nClr2 |= MASK_NODE_OK_CLR;    /* Clear NODE_OK_FLG */

	if(MASK_CRC_OK_FLG & nFlag1)
		nClr2 |= MASK_CRC_OK_CLR;    /* Clear CRC_OK_FLG */

	if(MASK_PKT_OK_FLG & nFlag1)
		nClr2 |= MASK_PKT_DONE_CLR;  /* Clear PKT_OK_FLG */

	if(MASK_SL_TMO_FLG & nFlag2)
		nClr1 |= MASK_SL_TMO_CLR;    /* Clear SL_TMO_FLG */

	if(MASK_RX_TMO_FLG & nFlag2)
		nClr1 |= MASK_RX_TMO_CLR;    /* Clear RX_TMO_FLG */

	if(MASK_TX_DONE_FLG & nFlag2)
		nClr1 |= MASK_TX_DONE_CLR;   /* Clear TX_DONE_FLG */
	    
	marco_escritura_registros(CUS_INT_CLR1, nClr1);
	marco_escritura_registros(CUS_INT_CLR2, nClr2);
}

/*
 * ...
 */
void switch_interruption(unsigned char int_sel){
		
	unsigned char reg_tmp;
	
	// Config interrupt INT2
	marco_lectura_registros(CUS_INT2_CTL, &reg_tmp);
		
	reg_tmp &= (~MASK_INT2_SEL); // clean INT2_SEL
	reg_tmp |= int_sel;  // set INT2_SEL
	marco_escritura_registros(CUS_INT2_CTL, reg_tmp);
}

/*
 * ...
 */
char interrupt_check(unsigned char flag_){
	
	unsigned char reg_tmp;
	
	marco_lectura_registros(CUS_INT_FLAG, &reg_tmp); // Read flag
					
	return (reg_tmp & flag_);
}

/*
 * ...
 */
void enable_write_fifo(){
	
	unsigned char reg_tmp;
	
    marco_lectura_registros(CUS_FIFO_CTL, &reg_tmp);
	
    reg_tmp |= MASK_SPI_FIFO_RD_WR_SEL;
    reg_tmp |= MASK_FIFO_RX_TX_SEL;
    marco_escritura_registros(CUS_FIFO_CTL, reg_tmp);
}

/*
 * ...
 */
void enable_read_fifo(){
	
	unsigned char reg_tmp;
	
    marco_lectura_registros(CUS_FIFO_CTL, &reg_tmp);
	
    reg_tmp &= ~MASK_SPI_FIFO_RD_WR_SEL;
    reg_tmp &= ~MASK_FIFO_RX_TX_SEL;
    marco_escritura_registros(CUS_FIFO_CTL, reg_tmp);
}

/*
 * ...
 */
void clear_tx_fifo(){
	
	unsigned char reg_tmp;
	
    marco_lectura_registros(CUS_FIFO_FLAG, &reg_tmp);
	
	reg_tmp |= MASK_FIFO_CLR_TX;
    marco_escritura_registros(CUS_FIFO_CLR, reg_tmp);
}

/*
 * ...
 */
void clear_rx_fifo(){
	
	unsigned char reg_tmp;
	
    marco_lectura_registros(CUS_FIFO_FLAG, &reg_tmp);
	
	reg_tmp |= MASK_FIFO_CLR_RX;
    marco_escritura_registros(CUS_FIFO_CLR, reg_tmp);
}

/*
 * Define las acciones a tomar ante una falla critica.
 */
void failure_attention_cmt2300(){
	
	SET_indication_vector_(ID_RF_FailureWarning);
	DELAY_MS(10);
	
	if(cmt2300_init_OK == TRUE)
		init_cmt2300a();
}