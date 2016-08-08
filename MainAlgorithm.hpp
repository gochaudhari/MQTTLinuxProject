/*
 * MainAlgorithm.hpp
 *
 *  Created on: Aug 7, 2016
 *      Author: gochaudhari
 */

#ifndef MAINALGORITHM_HPP_
#define MAINALGORITHM_HPP_

#include "GPSModule.hpp"
#include "AlcoholSensor.hpp"
#include "AccelerometerModule.hpp"

#define DANGER_ACCELERATION		323
#define DANGER_SPEED			123
#define DANGER_ALCOHOL_CONTENT	128

typedef struct DrivingScore
{
	int speedScore;
	int accelerationScore;
	int alcoholScore;
};

class MainAlgorithmProcess
{
	public:
		MainAlgorithmProcess();
		void AlgorithmProcessing();
		bool IsRashDriving();
		bool IsSpeeding();
		bool IsAccelerating();
		int GetDrivingScore();

	private:
		GPSData gpsDataVar;
		AlcoholSensor alcoholDataVar;
		bool isRashDriving;
		bool isSpeeding;
		bool isAccelerating;
		int alcoholData;
		float* allAcclerations;
		float maxAcceleration;
		int speed;
		DrivingScore individualDrivingScore;
		int finalDrivingScore;
};



#endif /* MAINALGORITHM_HPP_ */
