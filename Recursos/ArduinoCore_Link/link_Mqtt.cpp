/*
 * link_mqtt.cpp
 *
 * Created: 12/9/2023 17:08:29
 *  Author: Fernando
 */ 

#include "Arduino.h"
#include "gateway.h"

#define TINY_GSM_MODEM_SIM7080
#define GSM_AUTOBAUD_MIN 9600
#define GSM_AUTOBAUD_MAX 115200
#define GSM_PIN "2361"

#include "TinyGsmClient.h"
#include "PubSubClient.h"

 const char apn[] = "antel.lte";
 const char* broker = "mqtt-dashboard.com"; // link de MQTT
 const char* topic = "PruebaSarapico";

// #define  apn "antel.lte"
// #define  broker "mqtt-dashboard.com" // link de MQTT
// #define  topic "PruebaSarapico"


TinyGsm modem(Serial_GNSS);
TinyGsmClient client(modem);
PubSubClient  mqtt(client);

uint32_t lastReconnectAttempt = 0;

void init_sim868(){
	/*DELAY_MS(5000);*/
	modem.restart();
	DELAY_MS(1000);
	//TinyGsmAutoBaud(Serial_GNSS, GSM_AUTOBAUD_MIN, GSM_AUTOBAUD_MAX);
	modem.init();
	SerialUSB.print("Modulo iniciado\n");
	DELAY_MS(500);
	modeminformation();
	DELAY_MS(1000);
	modem.simUnlock("2361");
	
	DELAY_MS(1000);
	connect_gprs();
	DELAY_MS(500);
	connect_mqtt();
	DELAY_MS(500);

	
}

char connect_gprs(){
	
	/////////////////////////////////////
	
	
	SerialUSB.print("Intentando conectar GPRS\n");
	if (!modem.gprsConnect(apn)) {
		SerialUSB.print("Falló la conexion GPRS\n");
		return 0;
	}
	SerialUSB.print("Conexion exitosa GPRS\n");
	return 1;
}

char connect_mqtt(){
	DELAY_MS(500);
	if(!modem.isNetworkConnected()){
		return 0;
		
	}
	mqtt.setServer(broker, 1883);
	boolean status = mqtt.connect("GsmClientName");
	if(!status){
		return 0;
		SerialUSB.print("Fallo la conexion MQTT\n");
	}
	SerialUSB.print("Conexxion exitosa MQTT\n");
	return 1;
}

// void send_data(struct data_task_0 *metadatos) {
//	mqtt.publish(topic, (char *)metadatos);
//}

char send_data_link(){
	DELAY_MS(100);
 	if(!mqtt.publish(topic, "hola mundo")){
		 DELAY_MS(100);
		 return 0;
	 }
	 DELAY_MS(100);
	 return 1;
 }

char NetworkConnected_link(){
	if(modem.isNetworkConnected()){
		SerialUSB.print("Network conectado\n");
		return 1;
	}
	SerialUSB.print("sin conexion Network \n");
	return 0;
}

char isMqttConnected_link(){
	if(mqtt.connected()){
		SerialUSB.print("MQTT conectado\n");
		return 1;
	}
	SerialUSB.print("Sin conexion MQTT\n");
	return 0;
}

char isGprsConnected_link(){
	if(modem.isGprsConnected()){
		SerialUSB.print("GPRS conectado\n");
		return 1;
	}
	SerialUSB.print("Sin conexion GPRS\n");
	return 0;
}

void modeminformation(){
	char modemInfo[128]; // Declarar un arreglo de caracteres para almacenar la información del módem

	// Obtener la información del módem y copiarla en el arreglo de caracteres
	modem.getModemInfo().toCharArray(modemInfo, sizeof(modemInfo));

	// Imprimir la información del módem
	SerialUSB.print("Modem Info: ");
	SerialUSB.print(modemInfo);
	SerialUSB.print("\n");
}



char prueba_Ard_original(){
 	int csq = modem.getSignalQuality();
 	char string_[25];
 	sprintf(string_, "Signal quality: %i \n", csq);
 	SerialUSB.print(string_);
	DELAY_MS(100);
	if(!mqtt.connected()){
		SerialUSB.print("Sin conexion MQTT\n");
		connect_mqtt();
		return 0;
	}
	DELAY_MS(100);
	
	if(!send_data_link()){
		SerialUSB.print("Fallo en el envio MQTT");
	}
	SerialUSB.print("Enviado correctamente\n");
	DELAY_MS(200);
	return 1;
}


	