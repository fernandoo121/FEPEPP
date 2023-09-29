/*
 * requests.c
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#include "gateway.h"
#include "user_interface.h"
#include "release_management.h"

#include <string.h>

#ifndef FPRO_sim_on
 #include "slave_FlashDrive.h"
#endif // FPRO_sim_on
 
 char estado_serial = FALSE;
 
 void terminal_interface();
 
 /*
  * Interface de usuario para terminal.
  */
 void capturar_solicitudes_usuario(char* solicitud_, QueueHandle_t QueueHandle_, const void * const struct_){

	if (serialUSB_Ready_link(FALSE)){
		
		if (serialUSB_available_link() != NOTHING){
			
			switch(serialUSB_read_link()){
				case VFSA_: *solicitud_ = VFSA_; break;
				case VFSH_: *solicitud_ = VFSH_; break;
				case ECUF_: *solicitud_ = ECUF_; break;
				case AHFS_: *solicitud_ = AHFS_; break;
				default: serialUSB_print_link("\n Comando inválido.\n"); return;
			}

			while (xQueueSend(QueueHandle_, struct_, NOTHING) != pdTRUE){
				// La lista se puede encontrar brevemente llena ...
			}
			
		} else {
			
			if (estado_serial == FALSE){
				#if METADATOS_AL_PUERTO_SERIAL != 1
				 terminal_interface();
				#endif /*METADATOS_AL_PUERTO_SERIAL*/
				estado_serial = TRUE;
			} 
			
			*solicitud_ = NADA_;
		}
		
	} else
		estado_serial = FALSE;
}

/*
 * Enruta el flujo de software para la ejecución de los comandos.
 */
void procesar_solicitudes_usuario(char* solicitud_){
	
	switch(*solicitud_){
		case VFSA_: VFSA_FUNCTION(); break;
		case VFSH_: VFSH_FUNCTION(); break;
		case ECUF_: ECUF_FUNCTION(); break;
		default: serialUSB_print_link("\n Solicitud no disponible.\n"); break;
	}
	
	DELAY_US(1000000);
	
	estado_serial = FALSE;
}

/*
 *	Representación visual de la interfaz grafica en terminal.
 */
void terminal_interface(){
	
	char short_string_[20];
	
	serialUSB_print_link("\n\n -------- Interfaz de terminal GATEWAY --------- ");

	serialUSB_print_link("\n\n Fecha del sistema: "); 
	sprintf(short_string_, "%d/%d/%d",	day_RTC(), month_RTC(), year_RTC());
	serialUSB_print_link(short_string_);
	serialUSB_print_link("\n Horario del sistema: ");
	sprintf(short_string_, "%d:%d:%d", hour_RTC(), minute_RTC(), second_RTC());
	serialUSB_print_link(short_string_);
	
	serialUSB_print_link("\n\n"
						 "\n FIRMWARE: " identifier_ "-" version_ "-" revision_
						 "\n Fecha de liberacion " release_date
						 "\n"
						 "\n--------------------------------------------"
						 "\n Codigos de solicitud de usuario:"
						 "\n\t "); // encabezado
	/* comandos */
					
	sprintf(short_string_, "%c", VFSA_);
	serialUSB_print_link(short_string_);
	serialUSB_print_link(" : Volcado de metadata a puerto serial en formato legible ASCII."
						"\n\t ");
						
	sprintf(short_string_, "%c", VFSH_);
	serialUSB_print_link(short_string_);
	serialUSB_print_link(" : Volcado de metadata a puerto serial en formato hexadecimal por caracteres ASCII."
						"\n\t ");
						 
	sprintf(short_string_, "%c", ECUF_);
	serialUSB_print_link(short_string_);
	serialUSB_print_link(" : Eliminacion de metadata."
						"\n\t ");
	
	sprintf(short_string_, "%c", AHFS_);
	serialUSB_print_link(short_string_);
	serialUSB_print_link(" : Actualizacion hora y fecha del sistema."
						"\n\t ");
	
	serialUSB_print_link("\n"); // fin
}