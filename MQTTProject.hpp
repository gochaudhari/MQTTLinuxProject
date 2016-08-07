/*
 * MQTTProject.hpp
 *
 *  Created on: Aug 6, 2016
 *      Author: gochaudhari
 */

#ifndef MQTTPROJECT_HPP_
#define MQTTPROJECT_HPP_

#include "MQTTClient.hpp"
#include "string"

using namespace std;


typedef struct MQTTMessage
{
	char* host;
	string shortMessage;
	float lattitude;
	float longitude;
	string messageTitle;
	string message;
}mqttMessageType;

void InitializeMQTTCommunication();
bool SubscribeToTopic(const char* topic, MQTT::QoS qos);
bool PublishToTopic(mqttMessageType& mqttMessagePack, const char* topic, MQTT::QoS qos);
bool UnsubscribeFromTopic(const char* topic);
void ReceiveData();
void Disconnect();


#endif /* MQTTPROJECT_HPP_ */
