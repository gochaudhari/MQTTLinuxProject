/*
 * AcclerometerModule.hpp
 *
 *  Created on: Aug 7, 2016
 *      Author: gochaudhari
 */

#ifndef ACCLEROMETERMODULE_HPP_
#define ACCLEROMETERMODULE_HPP_

#include "string"
#include "upm/mma7660.hpp"

using namespace upm;

/*class AccelerometerData : public MMA7660
{
	public:
		AccelerometerData();
		void InitializeAccelerometer();
		string ReadDataFromAccelerometer();

	private:
		float ax, ay, az;
};*/
void ReadDataFromAccelerometer();



#endif /* ACCLEROMETERMODULE_HPP_ */
