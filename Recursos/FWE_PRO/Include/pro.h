/*
 * pro.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#ifndef PRO_H_
#define PRO_H_

 #include "pro_set.h"

 /* Parámetros configuración  */
 #define TIEMPO_BLOQUEO_OPERACION_FUERA_LINEA		500 // Tiempo definido para espera antes de verificar si la tarea comunicación vacío la lista

 #define FILE_NAME_ "DATABASE" // Maximo 8 caracteres
 #define DECREMENTO_DIRECCION_ULTIMO_RELEVO_ASEGURADO 2	// Para obtener última dirección que se puede garantisar como relevada ante un rst.

 /* 
  * Telemetría generada en Task 0 Procesameinto.
  * Consult appendix C document "Proyecto SARAPICO - Metadatos" https://trello.com/c/M6DWjpwr
  */

 // Telemetría generada en recepcion de metadatos.
 #ifdef FCOM_sim_on
  #define DATA_TLM_RF_EBPS	(1 << DATA_TLM_RF_EBPS_Pos)
 #else
  #if CAPTURAR_CRC_FAIL == 1
   extern unsigned char comunicacion_tlm_ = NOTHING;
   #define DATA_TLM_RF_EBPS	comunicacion_tlm_
  #else
   #define DATA_TLM_RF_EBPS	(0 << DATA_TLM_RF_EBPS_Pos)
  #endif
 #endif // FCOM_sim_on


 // Telemetría generada en escritura a unidad flas.
 #ifdef FPRO_sim_on
 #define DATA_TLM_FLASH_EBPS	(1 << DATA_TLM_FLASH_EBPS_Pos)
 #else
 #define DATA_TLM_FLASH_EBPS	((unidad_flash_init_ != TRUE ? HIGH : LOW) << DATA_TLM_FLASH_EBPS_Pos)
 #endif // FPRO_sim_on

 // Telemetría generada en relevamiento de metadatos.
 #if defined(FDDA_sim_on) || defined(FPRO_sim_on)
  #define DATA_TLM_CEL	(0b00 << DATA_TLM_CEL_Pos)
 #else
  extern unsigned char descarga_tlm_;
  #define DATA_TLM_CEL	(secuencia != NORMAL ? (0b00 << DATA_TLM_CEL_Pos) : descarga_tlm_)
 #endif // FDDA_sim_on

#endif /* PRO_H_ */