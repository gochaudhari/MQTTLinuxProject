/*
 * MainCode.cpp
 *
 *  Created on: Aug 6, 2016
 *      Author: gochaudhari
 */

#include "MQTTProject.hpp"
#include "string"
#include "AlcoholSensor.hpp"
#include "mraa.hpp"
#include "iostream"
#include "stdlib.h"
#include "GPSModule.hpp"

using namespace std;


int main(int argc, char* argv[])
{
	// Writing the code for MQTT communication
	// Initialize MQTT Communication
	InitializeMQTTCommunication();

	const char* topic = "gl/temp";
	string textMessage("This is a test message");

	mqttMessageType mqttMessagePack;
	mqttMessagePack.lattitude = 37.335798;
	mqttMessagePack.longitude = -121.8871945;
	mqttMessagePack.messageTitle = "Test Message";
	mqttMessagePack.message = "A test message is being sent from here";

	// Try Receiving the data from the broker
	SubscribeToTopic(topic, MQTT::QOS0);

	// Try Test publishing the data to MQTT Broker. This is a test publish to a test topic
	PublishToTopic(mqttMessagePack, topic, MQTT::QOS0);

	AlcoholSensor alcoholSensorVar;
	// This is the while loop of embedded controller
	GPSData gpsDataVar;
	gpsDataVar.InitializaGPSCommunication();

	while(1)
	{
		// Get the present GPS Data

		// Get the Accelerometer Data in Main Algorithm
		// Get Speed from the GPS Data in Main Algorithm
		///Todo: To Write an algorithm which gets the speed and acceleration data and decides whether
		/// it is rash driving.

		// Get Alcohol Data in the Main Algorithm

		//
		cout << gpsDataVar.ReadDataFromGPS();
		cout << alcoholSensorVar.ReadData() << endl;
		alcoholSensorVar.PublishAlcoholSensordata();

		PublishToTopic(mqttMessagePack, topic, MQTT::QOS0);


		sleep(1);
//		ReceiveData();
	}

	UnsubscribeFromTopic(topic);

	Disconnect();
	return 0;
}
