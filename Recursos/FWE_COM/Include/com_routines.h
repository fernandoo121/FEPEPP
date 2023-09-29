/*
 * com_routines.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */


#ifndef COM_ROUTINES_H_
#define COM_ROUTINES_H_
 
 enum estado_fsm_protocolo{
	 VERIFICACION,
	 RELEVAMIENTO,
	 ASIGNACION_CANAL,
	 ESPERA,
	 NUM_ESTADOS
 };

 extern unsigned char estado_fsm_protocolo;

 enum estado_canal{
	 LIBRE,
	 ASIGNADO
 };

 #ifdef __cplusplus
 extern "C" {
 #endif

	 // Estados FSM
	 void verificacion();
	 void relevamiento(unsigned char* trama_);
	 void asignacion_canal();
	 void espera();

	 // Aciones FSM
	 char escucha_canal_ms(unsigned long espera_, unsigned char estado_canal_);
	 void envio_ask(unsigned char* ask);
	 void actividad_canal(unsigned char* trama_);

	 // Funciones de soporte
	 void dormir_hardware_rf();
	 void descartar_actividad();
	 void tramas_al_puerto_serial(unsigned char* trama_);

 #ifdef __cplusplus
 }
 #endif

#endif /* COM_ROUTINES_H_ */