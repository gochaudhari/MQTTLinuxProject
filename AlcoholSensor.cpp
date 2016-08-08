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
#include "upm/mma7660.hpp"
#include "iostream"

using namespace std;
using namespace upm;
using namespace mraa;


AlcoholSensor::AlcoholSensor() : aioValue(0)
{
	isAlcoholPresent = false;
}

int AlcoholSensor::ReadData()
{
	return aioValue.read();
}
