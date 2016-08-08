/*
 * AccelerometerModule.cpp
 *
 *  Created on: Aug 7, 2016
 *      Author: gochaudhari
 */


#include <unistd.h>
#include <signal.h>
#include <iostream>
#include "upm/mma7660.hpp"
#include "AccelerometerModule.hpp"

using namespace upm;
using namespace std;

float* GetAccelerometerData()
{
	int x, y, z;
	float ax, ay, az;

	static float returnValue[3];

	// Instantiate an MMA7660 on I2C bus 0

	MMA7660 *accel = new MMA7660(MMA7660_I2C_BUS, MMA7660_DEFAULT_I2C_ADDR);

	// place device in standby mode so we can write registers
	accel->setModeStandby();

	// enable 64 samples per second
	accel->setSampleRate(MMA7660::AUTOSLEEP_64);

	// place device into active mode
	accel->setModeActive();

	accel->getRawValues(&x, &y, &z);
	cout << "Raw values: x = " << x << " y = " << y << " z = " << z << endl;

	accel->getAcceleration(&ax, &ay, &az);
	cout << "Acceleration: x = " << ax << "g y = " << ay << "g z = " << az << "g" << endl;
	returnValue[0] = ax;
	returnValue[1] = ay;
	returnValue[2] = az;

	delete accel;
	return returnValue;
}
