/*
 * GPSModule.cpp
 *
 *  Created on: Aug 6, 2016
 *      Author: gochaudhari
 */

#include "mraa.hpp"
#include "string"
#include "GPSModule.hpp"

using namespace std;
using namespace mraa;


// Since UART 0 of Intel Edison is connected to the Arduino
GPSData::GPSData() : uartHandle(0)
{
	gpsData = 0;
}

void GPSData::InitializaGPSCommunication()
{
	uartHandle.setBaudRate(9600);
}

float GPSData::ReadDataFromGPS()
{
	gpsData = 12.31;
	return gpsData;
}

int GPSData::GetCurrentSpeed()
{
	return 0;
}
