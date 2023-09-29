/*
 * link_arduinocore.h
 *
 * Created: 30/8/2023
 * Author : Andres Mezquida
 */

#ifndef LINK_MQTT_H_
#define LINK_MQTT_H_


 #ifdef __cplusplus
 extern "C" {

 #endif
 	 void init_sim868();
 	 char connect_gprs();
 	 char connect_mqtt();
 	 //void send_data(struct data_task_0 *metadatos);
 	 void send_data_link();
 	 char NetworkConnected_link();
 	 char isMqttConnected_link();
	 char isGprsConnected_link();
 
 #ifdef __cplusplus
 }
 #endif
	
#endif /* LINK_MQTT_H_ */



