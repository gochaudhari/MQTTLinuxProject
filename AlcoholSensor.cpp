/*
 * AlcoholSensor.cpp
 *
 *  Created on: Aug 6, 2016
 *      Author: gochaudhari
 */

#include "AlcoholSensor.hpp"
#include "mraa.hpp"
#include "MQTTProject.hpp"
#include "MQTTClient.hpp"
#include "string"

using namespace mraa;


AlcoholSensor::AlcoholSensor() : aioValue(0)
{
	isAlcoholPresent = false;
}

int AlcoholSensor::ReadData()
{
	return aioValue.read();
}

void AlcoholSensor::PublishAlcoholSensordata()
{
	const char* topic = "sensor/alcohol";
	/*sensor/accelerometer
	sensor/GPSLocation
	sensor/isSpeeding
	sensor/*/
	int alcoholData = aioValue.read();

	string alcoholDataMessage;


}
