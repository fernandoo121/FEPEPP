/*
 * slave_RF_operation.h
 *
 * Hardware: CMT2300A	Consult Datasheet https://www.hoperf.com/data/upload/portal/20230704/CMT2300A%20Datasheet%20EN-V1.7-202307.pdf
 *
 * Created: 16/8/2023 10:12:31
 * Author : Andres Mezquida
 */  


#ifndef SLAVE_RF_OPERATION_H_
#define SLAVE_RF_OPERATION_H_

 /* ---------- CMT2300AW soft reset ---------- */
 #define SOFT_RESET_ADDR 0x7F
 #define SOFT_RESET_MASK 0xFF

 /* ---------- CMT bank defines ---------- */
 #define CMT_BANK_ADDR           0x00
 #define CMT_BANK_SIZE           12
 #define CUS_CMT1                0x00
 #define CUS_CMT2                0x01
 #define CUS_CMT3                0x02
 #define CUS_CMT4                0x03
 #define CUS_CMT5                0x04
 #define CUS_CMT6                0x05
 #define CUS_CMT7                0x06
 #define CUS_CMT8                0x07
 #define CUS_CMT9                0x08
 #define CUS_CMT10               0x09
 #define CUS_CMT11               0x0A
 #define CUS_RSSI                0x0B

 /* ---------- System bank defines ---------- */
 #define SYSTEM_BANK_ADDR        0x0C
 #define SYSTEM_BANK_SIZE        12
 #define CUS_SYS1                0x0C
 #define CUS_SYS2                0x0D
 #define CUS_SYS3                0x0E
 #define CUS_SYS4                0x0F
 #define CUS_SYS5                0x10
 #define CUS_SYS6                0x11
 #define CUS_SYS7                0x12
 #define CUS_SYS8                0x13
 #define CUS_SYS9                0x14
 #define CUS_SYS10               0x15
 #define CUS_SYS11               0x16
 #define CUS_SYS12               0x17

 /* ---------- Frequency bank defines ---------- */
 #define FREQUENCY_BANK_ADDR     0x18
 #define FREQUENCY_BANK_SIZE     8
 #define CUS_RF1                 0x18
 #define CUS_RF2                 0x19
 #define CUS_RF3                 0x1A
 #define CUS_RF4                 0x1B
 #define CUS_RF5                 0x1C
 #define CUS_RF6                 0x1D
 #define CUS_RF7                 0x1E
 #define CUS_RF8                 0x1F

 /* ---------- Data rate bank defines ---------- */
 #define DATA_RATE_BANK_ADDR     0x20
 #define DATA_RATE_BANK_SIZE     24
 #define CUS_RF9                 0x20
 #define CUS_RF10                0x21
 #define CUS_RF11                0x22
 #define CUS_RF12                0x23
 #define CUS_FSK1                0x24
 #define CUS_FSK2                0x25
 #define CUS_FSK3                0x26
 #define CUS_FSK4                0x27
 #define CUS_FSK5                0x28
 #define CUS_FSK6                0x29
 #define CUS_FSK7                0x2A
 #define CUS_CDR1                0x2B
 #define CUS_CDR2                0x2C
 #define CUS_CDR3                0x2D
 #define CUS_CDR4                0x2E
 #define CUS_AGC1                0x2F
 #define CUS_AGC2                0x30
 #define CUS_AGC3                0x31
 #define CUS_AGC4                0x32
 #define CUS_OOK1                0x33
 #define CUS_OOK2                0x34
 #define CUS_OOK3                0x35
 #define CUS_OOK4                0x36
 #define CUS_OOK5                0x37

 /* ---------- Baseband bank defines ---------- */
 #define BASEBAND_BANK_ADDR      0x38
 #define BASEBAND_BANK_SIZE      29
 #define CUS_PKT1                0x38
 #define CUS_PKT2                0x39
 #define CUS_PKT3                0x3A
 #define CUS_PKT4                0x3B
 #define CUS_PKT5                0x3C
 #define CUS_PKT6                0x3D
 #define CUS_PKT7                0x3E
 #define CUS_PKT8                0x3F
 #define CUS_PKT9                0x40
 #define CUS_PKT10               0x41
 #define CUS_PKT11               0x42
 #define CUS_PKT12               0x43
 #define CUS_PKT13               0x44
 #define CUS_PKT14               0x45
 #define CUS_PKT15               0x46
 #define CUS_PKT16               0x47
 #define CUS_PKT17               0x48
 #define CUS_PKT18               0x49
 #define CUS_PKT19               0x4A
 #define CUS_PKT20               0x4B
 #define CUS_PKT21               0x4C
 #define CUS_PKT22               0x4D
 #define CUS_PKT23               0x4E
 #define CUS_PKT24               0x4F
 #define CUS_PKT25               0x50
 #define CUS_PKT26               0x51
 #define CUS_PKT27               0x52
 #define CUS_PKT28               0x53
 #define CUS_PKT29               0x54

 /* ---------- Tx bank defines ---------- */
 #define TX_BANK_ADDR            0x55
 #define TX_BANK_SIZE            11
 #define CUS_TX1                 0x55
 #define CUS_TX2                 0x56
 #define CUS_TX3                 0x57
 #define CUS_TX4                 0x58
 #define CUS_TX5                 0x59
 #define CUS_TX6                 0x5A
 #define CUS_TX7                 0x5B
 #define CUS_TX8                 0x5C
 #define CUS_TX9                 0x5D
 #define CUS_TX10                0x5E
 #define CUS_LBD                 0x5F

 /* ---------- Control1 bank defines ---------- */
 #define CONTROL1_BANK_ADDR      0x60
 #define CONTROL1_BANK_SIZE      11
 #define CUS_MODE_CTL            0x60
 #define CUS_MODE_STA            0x61
 #define CUS_EN_CTL              0x62
 #define CUS_FREQ_CHNL           0x63
 #define CUS_FREQ_OFS            0x64
 #define CUS_IO_SEL              0x65
 #define CUS_INT1_CTL            0x66
 #define CUS_INT2_CTL            0x67
 #define CUS_INT_EN              0x68
 #define CUS_FIFO_CTL            0x69
 #define CUS_INT_CLR1            0x6A

 /* ---------- Control2 bank defines ---------- */
 #define CONTROL2_BANK_ADDR      0x6B
 #define CONTROL2_BANK_SIZE      7
 #define CUS_INT_CLR2            0x6B
 #define CUS_FIFO_CLR            0x6C
 #define CUS_INT_FLAG            0x6D
 #define CUS_FIFO_FLAG           0x6E
 #define CUS_RSSI_CODE           0x6F
 #define CUS_RSSI_DBM            0x70
 #define CUS_LBD_RESULT          0x71


 /* ********** CUS_CMT2 registers ********** */
 #define MASK_PRODUCT_ID         0xFF

 /* ********** CUS_CMT5 registers ********** */
 #define MASK_LMT_CODE           0xC0

 /* ********** CUS_CMT9 registers ********** */
 #define MASK_RSSI_OFFSET_SIGN   0x80
 #define MASK_DIG_CLKDIV         0x1F

 /* ********** CUS_RSSI registers ********** */
 #define MASK_RSSI_OFFSET        0xF8
 #define MASK_RSSI_SLOPE         0x07

 /* ********** CUS_SYS1 registers ********** */
 #define MASK_LMT_VTR            0xC0
 #define MASK_MIXER_BIAS         0x30
 #define MASK_LNA_MODE           0x0C
 #define MASK_LNA_BIAS           0x03

 /* ********** CUS_SYS2 registers ********** */
 #define MASK_LFOSC_RECAL_EN     0x80
 #define MASK_LFOSC_CAL1_EN      0x40
 #define MASK_LFOSC_CAL2_EN      0x20
 #define MASK_RX_TIMER_EN        0x10
 #define MASK_SLEEP_TIMER_EN     0x08
 #define MASK_TX_DC_EN           0x04
 #define MASK_RX_DC_EN           0x02
 #define MASK_DC_PAUSE           0x01

 /* ********** CUS_SYS3 registers ********** */
 #define MASK_SLEEP_BYPASS_EN    0x80
 #define MASK_XTAL_STB_TIME      0x70
 #define MASK_TX_EXIT_STATE      0x0C
 #define MASK_RX_EXIT_STATE      0x03

 /* ********** CUS_SYS4 registers ********** */
 #define MASK_SLEEP_TIMER_M_7_0  0xFF

 /* ********** CUS_SYS5 registers ********** */
 #define MASK_SLEEP_TIMER_M_10_8 0x70
 #define MASK_SLEEP_TIMER_R      0x0F

 /* ********** CUS_SYS6 registers ********** */
 #define MASK_RX_TIMER_T1_M_7_0  0xFF

 /* ********** CUS_SYS7 registers ********** */
 #define MASK_RX_TIMER_T1_M_10_8 0x70
 #define MASK_RX_TIMER_T1_R      0x0F

 /* ********** CUS_SYS8 registers ********** */
 #define MASK_RX_TIMER_T2_M_7_0  0xFF

 /* ********** CUS_SYS9 registers ********** */
 #define MASK_RX_TIMER_T2_M_10_8 0x70
 #define MASK_RX_TIMER_T2_R      0x0F

 /* ********** CUS_SYS10 registers ********** */
 #define MASK_COL_DET_EN         0x80
 #define MASK_COL_OFS_SEL        0x40
 #define MASK_RX_AUTO_EXIT_DIS   0x20
 #define MASK_DOUT_MUTE          0x10
 #define MASK_RX_EXTEND_MODE     0x0F

 /* ********** CUS_SYS11 registers ********** */
 #define MASK_PJD_TH_SEL         0x80
 #define MASK_CCA_INT_SEL        0x60
 #define MASK_RSSI_DET_SEL       0x18
 #define MASK_RSSI_AVG_MODE      0x07

 /* ********** CUS_SYS12 registers ********** */
 #define MASK_PJD_WIN_SEL        0xC0
 #define MASK_CLKOUT_EN          0x20
 #define MASK_CLKOUT_DIV         0x1F

 /* ********** CUS_RF1 registers ********** */
 #define MASK_FREQ_RX_N          0xFF

 /* ********** CUS_RF2 registers ********** */
 #define MASK_FREQ_RX_K_7_0      0xFF

 /* ********** CUS_RF3 registers ********** */
 #define MASK_FREQ_RX_K_15_8     0xFF

 /* ********** CUS_RF4 registers ********** */
 #define MASK_FREQ_PALDO_SEL     0x80
 #define MASK_FREQ_DIVX_CODE     0x70
 #define MASK_FREQ_RX_K_19_16    0x0F

 /* ********** CUS_RF5 registers ********** */
 #define MASK_FREQ_TX_N          0xFF

 /* ********** CUS_RF6 registers ********** */
 #define MASK_FREQ_TX_K_7_0      0xFF

 /* ********** CUS_RF7 registers ********** */
 #define MASK_FREQ_TX_K_15_8     0xFF

 /* ********** CUS_RF8 registers ********** */
 #define MASK_FSK_SWT            0x80
 #define MASK_FREQ_VCO_BANK      0x70
 #define MASK_FREQ_TX_K_19_16    0x0F

 /* ********** CUS_PKT1 registers ********** */
 #define MASK_RX_PREAM_SIZE      0xF8
 #define MASK_PREAM_LENG_UNIT    0x04
 #define MASK_DATA_MODE          0x03
 /* MASK_PREAM_LENG_UNIT options */
 #define PREAM_LENG_UNIT_8_BITS  0x00
 #define PREAM_LENG_UNIT_4_BITS  0x04
 /* MASK_DATA_MODE options */
 #define DATA_MODE_DIRECT        0x00
 #define DATA_MODE_PACKET        0x02

 /* ********** CUS_PKT2 registers ********** */
 #define MASK_TX_PREAM_SIZE_7_0  0xFF

 /* ********** CUS_PKT3 registers ********** */
 #define MASK_TX_PREAM_SIZE_15_8 0xFF

 /* ********** CUS_PKT4 registers ********** */
 #define MASK_PREAM_VALUE        0xFF

 /* ********** CUS_PKT5 registers ********** */
 #define MASK_SYNC_TOL           0x70
 #define MASK_SYNC_SIZE          0x0E
 #define MASK_SYNC_MAN_EN        0x01

 /* ********** CUS_PKT6 registers ********** */
 #define MASK_SYNC_VALUE_7_0     0xFF

 /* ********** CUS_PKT7 registers ********** */
 #define MASK_SYNC_VALUE_15_8    0xFF

 /* ********** CUS_PKT8 registers ********** */
 #define MASK_SYNC_VALUE_23_16   0xFF

 /* ********** CUS_PKT9 registers ********** */
 #define MASK_SYNC_VALUE_31_24   0xFF

 /* ********** CUS_PKT10 registers ********** */
 #define MASK_SYNC_VALUE_39_32   0xFF

 /* ********** CUS_PKT11 registers ********** */
 #define MASK_SYNC_VALUE_47_40   0xFF

 /* ********** CUS_PKT12 registers ********** */
 #define MASK_SYNC_VALUE_55_48   0xFF

 /* ********** CUS_PKT13 registers ********** */
 #define MASK_SYNC_VALUE_63_56   0xFF

 /* ********** CUS_PKT14 registers ********** */
 #define MASK_PAYLOAD_LENG_10_8  0x70
 #define MASK_AUTO_ACK_EN        0x08
 #define MASK_NODE_LENG_POS_SEL  0x04
 #define MASK_PAYLOAD_BIT_ORDER  0x02
 #define MASK_PKT_TYPE           0x01
 /* MASK_NODE_LENG_POS_SEL options */
 #define NODE_LENG_FIRST_NODE    0x00
 #define NODE_LENG_FIRST_LENGTH  0x04
 /* MASK_PAYLOAD_BIT_ORDER options */
 #define PAYLOAD_BIT_ORDER_MSB   0x00
 #define PAYLOAD_BIT_ORDER_LSB   0x02
 /* MASK_PKT_TYPE options */
 #define PKT_TYPE_FIXED          0x00
 #define PKT_TYPE_VARIABLE       0x01

 /* ********** CUS_PKT15 registers ********** */
 #define MASK_PAYLOAD_LENG_7_0   0xFF

 /* ********** CUS_PKT16 registers ********** */
 #define MASK_NODE_FREE_EN       0x20
 #define MASK_NODE_ERR_MASK      0x10
 #define MASK_NODE_SIZE          0x0C
 #define MASK_NODE_DET_MODE      0x03
 /* MASK_NODE_DET_MODE options */
 #define NODE_DET_NODE           0x00
 #define NODE_DET_VALUE          0x01
 #define NODE_DET_VALUE_0        0x02
 #define NODE_DET_VALUE_0_1      0x03

 /* ********** CUS_PKT17 registers ********** */
 #define MASK_NODE_VALUE_7_0     0xFF

 /* ********** CUS_PKT18 registers ********** */
 #define MASK_NODE_VALUE_15_8    0xFF

 /* ********** CUS_PKT19 registers ********** */
 #define MASK_NODE_VALUE_23_16   0xFF

 /* ********** CUS_PKT20 registers ********** */
 #define MASK_NODE_VALUE_31_24   0xFF

 /* ********** CUS_PKT21 registers ********** */
 #define MASK_FEC_TYPE           0x80
 #define MASK_FEC_EN             0x40
 #define MASK_CRC_BYTE_SWAP      0x20
 #define MASK_CRC_BIT_INV        0x10
 #define MASK_CRC_RANGE          0x08
 #define MASK_CRC_TYPE           0x06
 #define MASK_CRC_EN             0x01
 /* MASK_CRC_BYTE_SWAP options */
 #define CRC_ORDER_HBYTE         0x00
 #define CRC_ORDER_LBYTE         0x20
 /* MASK_CRC_RANGE options */
 #define CRC_RANGE_PAYLOAD       0x00
 #define CRC_RANGE_DATA          0x08
 /* MASK_CRC_TYPE options */
 #define CRC_TYPE_CCITT16        0x00
 #define CRC_TYPE_IBM16          0x02
 #define CRC_TYPE_ITU16          0x04

 /* ********** CUS_PKT22 registers ********** */
 #define MASK_CRC_SEED_7_0       0xFF

 /* ********** CUS_PKT23 registers ********** */
 #define MASK_CRC_SEED_15_8      0xFF

 /* ********** CUS_PKT24 registers ********** */
 #define MASK_CRC_BIT_ORDER      0x80
 #define MASK_WHITEN_SEED_8_8    0x40
 #define MASK_WHITEN_SEED_TYPE   0x20
 #define MASK_WHITEN_TYPE        0x18
 #define MASK_WHITEN_EN          0x04
 #define MASK_MANCH_TYPE         0x02
 #define MASK_MANCH_EN           0x01
 /* MASK_CRC_BIT_ORDER options */
 #define CRC_BIT_ORDER_MSB       0x00
 #define CRC_BIT_ORDER_LSB       0x80
 /* MASK_WHITEN_SEED_TYPE options */
 #define WHITEN_SEED_TYPE_1      0x00
 #define WHITEN_SEED_TYPE_2      0x20
 /* MASK_WHITEN_TYPE options */
 #define WHITEN_TYPE_PN9_CCITT   0x00
 #define WHITEN_TYPE_PN9_IBM     0x08
 #define WHITEN_TYPE_PN7         0x10
 /* MASK_MANCH_TYPE options */
 #define MANCH_TYPE_ONE_01       0x00
 #define MANCH_TYPE_ONE_10       0x02

 /* ********** CUS_PKT25 registers ********** */
 #define MASK_WHITEN_SEED_7_0    0xFF

 /* ********** CUS_PKT26 registers ********** */
 #define MASK_TX_PREFIX_TYPE     0x03

 /* ********** CUS_PKT27 registers ********** */
 #define MASK_TX_PKT_NUM         0xFF

 /* ********** CUS_PKT28 registers ********** */
 #define MASK_TX_PKT_GAP         0xFF

 /* ********** CUS_PKT29 registers ********** */
 #define MASK_FIFO_AUTO_RES_EN   0x80
 #define MASK_FIFO_TH            0x7F

 /* ********** CUS_MODE_CTL registers ********** */
 #define MASK_CHIP_MODE_SWT      0xFF
 /* MASK_CHIP_MODE_SWT options */
 #define GO_EEPROM               0x01
 #define GO_STBY                 0x02
 #define GO_RFS                  0x04
 #define GO_RX                   0x08
 #define GO_SLEEP                0x10
 #define GO_TFS                  0x20
 #define GO_TX                   0x40
 #define GO_SWITCH               0x80

 /* ********** CUS_MODE_STA registers ********** */
 #define MASK_RSTN_IN_EN         0x20
 #define MASK_CFG_RETAIN         0x10
 #define MASK_CHIP_MODE_STA      0x0F
 /* MASK_CHIP_MODE_STA options */
 #define STA_IDLE                0x00
 #define STA_SLEEP               0x01
 #define STA_STBY                0x02
 #define STA_RFS                 0x03
 #define STA_TFS                 0x04
 #define STA_RX                  0x05
 #define STA_TX                  0x06
 #define STA_EEPROM              0x07
 #define STA_ERROR               0x08
 #define STA_CAL                 0x09

 /* ********** CUS_EN_CTL registers ********** */
 #define MASK_LOCKING_EN         0x20

 /* ********** CUS_FREQ_CHNL registers ********** */
 #define MASK_FH_CHANNEL         0xFF

 /* ********** CUS_FREQ_OFS registers ********** */
 #define MASK_FH_OFFSET          0xFF

 /* ********** CUS_IO_SEL registers ********** */
 #define MASK_GPIO4_SEL          0xC0
 #define MASK_GPIO3_SEL          0x30
 #define MASK_GPIO2_SEL          0x0C
 #define MASK_GPIO1_SEL          0x03
 /* MASK_GPIO4_SEL options */
 #define GPIO4_SEL_RSTIN         0x00
 #define GPIO4_SEL_INT1          0x40
 #define GPIO4_SEL_DOUT          0x80
 #define GPIO4_SEL_DCLK          0xC0
 /* MASK_GPIO3_SEL options */
 #define GPIO3_SEL_CLKO          0x00
 #define GPIO3_SEL_DOUT          0x10
 #define GPIO3_SEL_DIN           0x10
 #define GPIO3_SEL_INT2          0x20
 #define GPIO3_SEL_DCLK          0x30
 /* MASK_GPIO2_SEL options */
 #define GPIO2_SEL_INT1          0x00
 #define GPIO2_SEL_INT2          0x04
 #define GPIO2_SEL_DOUT          0x08
 #define GPIO2_SEL_DIN           0x08
 #define GPIO2_SEL_DCLK          0x0C
 /* MASK_GPIO1_SEL options */
 #define GPIO1_SEL_DOUT          0x00
 #define GPIO1_SEL_DIN           0x00
 #define GPIO1_SEL_INT1          0x01
 #define GPIO1_SEL_INT2          0x02
 #define GPIO1_SEL_DCLK          0x03

 /* ********** CUS_INT1_CTL registers ********** */
 #define MASK_RF_SWT1_EN         0x80
 #define MASK_RF_SWT2_EN         0x40
 #define MASK_INT_POLAR          0x20
 #define MASK_INT1_SEL           0x1F
 /* MASK_INT_POLAR options */
 #define INT_POLAR_SEL_0         0x00
 #define INT_POLAR_SEL_1         0x20
 /* MASK_INT1_SEL options */
 #define INT_SEL_RX_ACTIVE       0x00
 #define INT_SEL_TX_ACTIVE       0x01
 #define INT_SEL_RSSI_VLD        0x02
 #define INT_SEL_PREAM_OK        0x03
 #define INT_SEL_SYNC_OK         0x04
 #define INT_SEL_NODE_OK         0x05
 #define INT_SEL_CRC_OK          0x06
 #define INT_SEL_PKT_OK          0x07
 #define INT_SEL_SL_TMO          0x08
 #define INT_SEL_RX_TMO          0x09
 #define INT_SEL_TX_DONE         0x0A
 #define INT_SEL_RX_FIFO_NMTY    0x0B
 #define INT_SEL_RX_FIFO_TH      0x0C
 #define INT_SEL_RX_FIFO_FULL    0x0D
 #define INT_SEL_RX_FIFO_WBYTE   0x0E
 #define INT_SEL_RX_FIFO_OVF     0x0F
 #define INT_SEL_TX_FIFO_NMTY    0x10
 #define INT_SEL_TX_FIFO_TH      0x11
 #define INT_SEL_TX_FIFO_FULL    0x12
 #define INT_SEL_STATE_IS_STBY   0x13
 #define INT_SEL_STATE_IS_FS     0x14
 #define INT_SEL_STATE_IS_RX     0x15
 #define INT_SEL_STATE_IS_TX     0x16
 #define INT_SEL_LED             0x17
 #define INT_SEL_TRX_ACTIVE      0x18
 #define INT_SEL_PKT_DONE        0x19

 /* ********** CUS_INT2_CTL registers ********** */
 #define MASK_LFOSC_OUT_EN       0x40
 #define MASK_TX_DIN_INV         0x20
 #define MASK_INT2_SEL           0x1F

 /* ********** CUS_INT_EN registers ********** */
 #define MASK_SL_TMO_EN          0x80
 #define MASK_RX_TMO_EN          0x40
 #define MASK_TX_DONE_EN         0x20
 #define MASK_PREAM_OK_EN        0x10
 #define MASK_SYNC_OK_EN         0x08
 #define MASK_NODE_OK_EN         0x04
 #define MASK_CRC_OK_EN          0x02
 #define MASK_PKT_DONE_EN        0x01

 /* ********** CUS_FIFO_CTL registers ********** */
 #define MASK_TX_DIN_EN          0x80
 #define MASK_TX_DIN_SEL         0x60
 #define MASK_FIFO_AUTO_CLR_DIS  0x10
 #define MASK_FIFO_TX_RD_EN      0x08
 #define MASK_FIFO_RX_TX_SEL     0x04
 #define MASK_FIFO_MERGE_EN      0x02
 #define MASK_SPI_FIFO_RD_WR_SEL 0x01
 /* MASK_TX_DIN_SEL options */
 #define TX_DIN_SEL_GPIO1        0x00
 #define TX_DIN_SEL_GPIO2        0x20
 #define TX_DIN_SEL_GPIO3        0x40

 /* ********** CUS_INT_CLR1 registers ********** */
 #define MASK_SL_TMO_FLG         0x20
 #define MASK_RX_TMO_FLG         0x10
 #define MASK_TX_DONE_FLG        0x08
 #define MASK_TX_DONE_CLR        0x04
 #define MASK_SL_TMO_CLR         0x02
 #define MASK_RX_TMO_CLR         0x01

 /* ********** CUS_INT_CLR2 registers ********** */
 #define MASK_LBD_CLR            0x20
 #define MASK_PREAM_OK_CLR       0x10
 #define MASK_SYNC_OK_CLR        0x08
 #define MASK_NODE_OK_CLR        0x04
 #define MASK_CRC_OK_CLR         0x02
 #define MASK_PKT_DONE_CLR       0x01

 /* ********** CUS_FIFO_CLR registers ********** */
 #define MASK_FIFO_RESTORE       0x04
 #define MASK_FIFO_CLR_RX        0x02
 #define MASK_FIFO_CLR_TX        0x01

 /* ********** CUS_INT_FLAG registers ********** */
 #define MASK_LBD_FLG            0x80
 #define MASK_COL_ERR_FLG        0x40
 #define MASK_PKT_ERR_FLG        0x20
 #define MASK_PREAM_OK_FLG       0x10
 #define MASK_SYNC_OK_FLG        0x08
 #define MASK_NODE_OK_FLG        0x04
 #define MASK_CRC_OK_FLG         0x02
 #define MASK_PKT_OK_FLG         0x01

 /* ********** CUS_FIFO_FLAG registers ********** */
 #define MASK_RX_FIFO_FULL_FLG   0x40
 #define MASK_RX_FIFO_NMTY_FLG   0x20
 #define MASK_RX_FIFO_TH_FLG     0x10
 #define MASK_RX_FIFO_OVF_FLG    0x08
 #define MASK_TX_FIFO_FULL_FLG   0x04
 #define MASK_TX_FIFO_NMTY_FLG   0x02
 #define MASK_TX_FIFO_TH_FLG     0x01

 /* ********** CUS_RSSI_CODE registers ********** */
 #define MASK_RSSI_CODE          0xFF

 /* ********** CUS_RSSI_DBM registers ********** */
 #define MASK_RSSI_DBM           0xFF

 /* ********** CUS_LBD_RESULT registers ********** */
 #define MASK_LBD_RESULT         0xFF

 
 extern char cmt2300_init_OK;

#ifdef __cplusplus
extern "C" {
#endif

	void init_cmt2300a();
	void prueba_cmt2300a();
	void failure_attention_cmt2300();

	void marco_escritura_banco(unsigned char base_addr, const unsigned char bank[], unsigned char len);
	void marco_escritura_registros(unsigned char addr_register, unsigned char data_);
	void marco_lectura_registros(unsigned char addr_register, unsigned char *ptr_data);
	void marco_escritura_FIFO(unsigned char* data_, unsigned char data_len);
	unsigned char marco_lectura_FIFO(unsigned char* data_, unsigned char data_len);

	void soft_reset();

	void ack_packet_format(char state);
	void packet_length(unsigned char length);

	void go_sleep();
	void go_stby();
	void go_tx();
	void go_rx();
	void go_switch();

	void clear_interrupt_flags();
	void switch_interruption(unsigned char int_sel);
	char interrupt_check(unsigned char int_sel);
	void enable_write_fifo();
	void enable_read_fifo();
	void clear_tx_fifo();
	void clear_rx_fifo();

#ifdef __cplusplus
}
#endif

#endif /* SLAVE_RF_OPERATION_H_ */