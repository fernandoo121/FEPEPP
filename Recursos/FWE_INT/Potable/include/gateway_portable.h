/*
 * gateway_portable.h
 *
 * Created: 30/08/2023
 * Author : Andres Mezquida
 */

#include "samd21_init.h"

#include "port.h"
#include "eic.h"
#include "sercom.h"
#include "rtc.h"

#ifndef GATEWAY_PORTABLE_H_
#define GATEWAY_PORTABLE_H_
/* Arduino Core error_hooks set */
#ifdef PCB_ULT
 #define Error_Led_crashes_rtos		(31ul), LOW		//(pinArduino, activeState) 31 = PB23
#endif /* PCB_ULT */
 #define Error_Serial_crashes_rtos	SerialUSB

/*
	Priority Levels Nested Vectored Interrupt Controller (NVIC) with IRQs

	Cortex-M0+ processors support three fixed highest priority levels for three of the system exceptions, 
	and four programmable levels for all other exceptions, including interrupts. An 8-bit Priority Level 
	Register is associated with each exception having programmable priority, however, note that only the 
	two MSBs are implemented.

	With this configuration we have four possible programmable priority levels defined in IRQn_priority.
*/

 /* Setting interrupt priority for application */
enum IRQn_priority_application{
	
	SERCOM0_IRQn_app_priority	= _highest______________,	// I2C bus	[CDC, IMU, ...]
	EIC_IRQn_app_priority		= _highest_intermediate_,	// Overall	[RF, SWITCH, ...]
	SERCOM2_IRQn_app_priority	= _lowest_intermediate__,	// SPI2 bus [RF, ...]
	ADC_IRQn_app_priority		= _lowest_______________,	//
	RTC_IRQn_app_priority		= _lowest_______________,
};

/*
 * Control de fallas del sistema.
 */

#define SD_MMC_FailureAttention_begin	SET_indication_vector_(ID_SD_MMC_FailureWarning_begin)
#define SD_MMC_FailureAttention_open	SET_indication_vector_(ID_SD_MMC_FailureWarning_open)

#define I2C_1_FailureAttention_	I2C_1_FAILURE()
#define SPI_2_FailureAttention_	SPI_2_FAILURE()

#define RF_FailureAttention_	SPI_2_SLAVE_1__FAILURE()

/*
 * Definiciones para enlace de hardware con aplicación.
 */

#include "slave_RF_operation.h"

#ifndef FPRO_sim_on
 #define  SLAVE_1_HARDWARE_SPI_1()
#else
 #define  SLAVE_1_HARDWARE_SPI_1() asm("nop")
#endif //

#ifndef FCOM_sim_on
 #define  SPI_2_FAILURE() SPI_2_failure()
 #define  SPI_2_SLAVE_1__FAILURE() failure_attention_cmt2300()
#else
 #define  SPI_2_FAILURE() asm("nop")
 #define  SPI_2_SLAVE_1__FAILURE() asm("nop")
#endif // FCOM_sim_on

#ifndef FDDA_sim_on
 #define  SLAVE_1_HARDWARE_USART_2() ¡?
#else
 #define  SLAVE_1_HARDWARE_USART_2() asm("nop")
#endif // FGEO_sim_on

#ifndef FVIN_sim_on
 #define  SLAVE_1_HARDWARE_I2C_1() ¡?
#else
 #define  SLAVE_1_HARDWARE_I2C_1() asm("nop")
#endif // FVIN_sim_on

#ifndef FFTE_sim_on
 #define  SLAVE_2_HARDWARE_I2C_1() ¡?
#else
 #define  SLAVE_2_HARDWARE_I2C_1() asm("nop")
#endif // FFTE_sim_on

#ifdef __cplusplus
extern "C" {
#endif

	
 
#ifdef __cplusplus
}
#endif

#endif /* GATEWAY_PORTABLE_H_ */