/*
 * AlcoholSensor.hpp
 *
 *  Created on: Aug 6, 2016
 *      Author: gochaudhari
 */

#ifndef ALCOHOLSENSOR_HPP_
#define ALCOHOLSENSOR_HPP_

#include "mraa.hpp"

using namespace mraa;

class AlcoholSensor
{
	public:

		AlcoholSensor();
		bool IsAlcoholDetected();

		int ReadData();
		void SendData();
		void PublishAlcoholSensordata();

		bool isAlcoholPresent;

	private:
		Aio aioValue;
};



#endif /* ALCOHOLSENSOR_HPP_ */
