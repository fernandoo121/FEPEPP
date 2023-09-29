/*
 * release_management.h
 * Consult document  "Proyecto SARAPICO - Integración de firmware" https://trello.com/c/vpQju4Ef
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */ 


#ifndef RELEASE_MANAGEMENT_H_
#define RELEASE_MANAGEMENT_H_

#define identifier_		"FEPEPP"

/******************************************************************************************************/
/*   A continuación, el listado de los cambios de diseño, características y grupos de requerimientos. */
/******************************************************************************************************/

	#ifndef version_
	 #define version_		"1.0"
	#endif // version_
	#ifndef revision_
	 #define revision_		"DA"
	#endif // revision_
	#ifndef release_date
	 #define release_date	"¿?/¿?/¿?"
	#endif // release_date 
	/*
	//////////////////////////////////////////////////////////////////////////{
	
	#Requerimientos
	.	Firmware de Integración.
	.	Firmware de Procesamiento.
	.	Firmware de Comunicación.
	.	Firmware de Descarga de Datos.
	.	Firmware de Vinculación.
	.	Firmware de Fuente.
	
		#FWE_INT 1.0-DA
			.0
			-	Sistema operativo en tiempo real FreeRTOS Kernel V10.2.1.
				.	APIs para comunicación entre tareas: Queue, EventGroup y TaskNotify
				.	APIs para utilización de periféricos: no implementa
				.	APIs para definir esperas: TaskDelay (solo mili segundos, para microsegundos conteo de reloj)
			-	Funciones y definiciones de aplicación generales para todo el sistema.
				.	Funciones para control de desbordamiento en adición e incremento.
			-	Funciones y definiciones portables generales para todo el sistema.
				.	Para uso de periféricos PORT, EIC, SERCOM y RTC.
			-	Implementa las rutinas de software para inicialización del microcontrolador.
				.	Ajustes de reloj y memoria por núcleo Arduino.
						Generic Clock Generator 0 at 48MHz
						Generic Clock Generator 1 at 32.768kHz
						Generic Clock Generator 3 at 8MHz
				.	Inicialización de periféricos
						PORT, propio.
						EIC, propio.
						SERCOM:
							I2C_1,   propio.
							SPI_1,   Arduino en SD.h.
							SPI_2,   propio.
							USART_¡?, Arduino en ¡?.h.
						RTC, propio.
			-	Tarea de inactividad SOTR.
				.	Comunicación serial para ejecución de comandos.
				.	Ejecución de indicaciones para operario.

			DA
			- Liberación para evaluación.
			
		#FWE_PRO 1.0-DA
			.0
			-	Funciones y definiciones de aplicación para generación de metadatos.
				.	Según Metadatos Rev.06.
			-	Funciones y definiciones portables para el respaldo de metadatos.
				.	Respaldo FAT32 con librería SD, núcleo Arduino.
			DA
			- Liberación para evaluación.

		#FWE_COM 1.0-DA
			.0
			-	Funciones y definiciones de aplicación para utilización de red local.
				.	Implementación protocolo CSMA/CA con ASK.
				.	Con transmisión de metadatos (+700 bytes) subdividido en tramas de 64 bytes.
			-	Funciones y definiciones portables para el modem de radiofrecuencia ISM.
				.	Chip CMT2300A, lib. de desarrollo propio.
			DA
			- Liberación para evaluación.
			
		#FWE_DDA 1.0-DA
			.0
			-	Funciones y definiciones de aplicación para comunicación con servidor.
				.	...
			-	Funciones y definiciones portables para el módulo celular.
				.	Módulo SIM868, lib. de terceros <nombre_version>.
			DA
			- Liberación para evaluación.
			
	}////////////////////////////////////////////////////////////////////////////////////////////////*/

#endif /* RELEASE_MANAGEMENT_H_ */