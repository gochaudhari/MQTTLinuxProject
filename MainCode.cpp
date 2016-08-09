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
#include "AccelerometerModule.hpp"
#include "MainAlgorithm.hpp"

#define GPSModule
#define SpeedModule
#define AccelerometerModule
#define AlcoholModule
#define MainAlgorithmModule

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

#ifdef AlcoholModule
	AlcoholSensor alcoholSensorVar;
#endif

	// This is the while loop of embedded controller
	GPSData gpsDataVar;
	gpsDataVar.InitializaGPSCommunication();

#ifdef MainAlgorithmModule
	MainAlgorithmProcess mainAlgorithmVar;
#endif


	while(1)
	{
		PublishToTopic(mqttMessagePack, topic, MQTT::QOS0);

		// Get the present GPS Data
		/// Todo:: In every message, lat long would be published.
		mqttMessagePack.lattitude = gpsDataVar.ReadDataFromGPS();
		mqttMessagePack.longitude = gpsDataVar.ReadDataFromGPS();

#ifdef AccelerometerModule
		// Get the Accelerometer Data in Main Algorithm ( with location )
		/// Todo: sensor/accelerometer
		float *accelerometerData = GetAccelerometerData();
		float accelerometerDataToSend = max(max(accelerometerData[0], accelerometerData[1]), accelerometerData[2]);
		mqttMessagePack.messageTitle = "Accelerometer Data";
		mqttMessagePack.message = "acceleration";
		PublishToTopic(mqttMessagePack, "sensor/accelerometer", MQTT::QOS0);
#endif

#ifdef SpeedModule
		// Get Speed from the GPS Data in Main Algorithm
		/// Todo: sensor/speed
		int speedData = gpsDataVar.GetCurrentSpeed();
		mqttMessagePack.messageTitle = "Speed Data";
		mqttMessagePack.message = "speed";
		PublishToTopic(mqttMessagePack, "sensor/speed", MQTT::QOS0);
#endif

#ifdef AlcoholModule
		// Get Alcohol Data in the Main Algorithm ( with location)
		/// Todo: sensor/alcoholData
		int alcoholData = alcoholSensorVar.ReadData();
		mqttMessagePack.messageTitle = "Alcohol Data";
		mqttMessagePack.message = "alcohol";
		PublishToTopic(mqttMessagePack, "sensor/alcoholData", MQTT::QOS0);
#endif

#ifdef MainAlgorithmModule
		// To detect whether the driving is rash or not
		/// Todo: flags/IsRash
		mqttMessagePack.messageTitle = "Is Rash Flag";
		if(mainAlgorithmVar.IsRashDriving()) {
			mqttMessagePack.message = "TRUE";
		}
		else {
			mqttMessagePack.message = "FALSE";
		}
		PublishToTopic(mqttMessagePack, "flags/isRash", MQTT::QOS0);
#endif

#ifdef MainAlgorithmModule
		// To Write an algorithm which gets the speed and acceleration data and decides whether it is rash driving.
		/// Todo: vehicle/drivingScore
		mqttMessagePack.messageTitle = "Driving Score";
		mqttMessagePack.message = "56";
		PublishToTopic(mqttMessagePack, "vehicle/drivingScore", MQTT::QOS0);
#endif

		//Send emergency button to topic
		/// Todo: emergency/emergencyButton

		sleep(1);
//		ReceiveData();
	}

	UnsubscribeFromTopic(topic);

	Disconnect();
	return 0;
}
