/*
 * GPSModule.hpp
 *
 *  Created on: Aug 6, 2016
 *      Author: gochaudhari
 */

#ifndef GPSMODULE_HPP_
#define GPSMODULE_HPP_

#include "string"
#include "mraa.hpp"

using namespace std;
using namespace mraa;

class GPSData
{
	public:
		GPSData();
		void InitializaGPSCommunication();
		string ReadDataFromGPS();

	private:
		Uart uartHandle;
		string gpsData;
};



#endif /* GPSMODULE_HPP_ */
