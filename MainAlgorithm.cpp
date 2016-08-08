/*
 * MainAlgorithm.cpp
 *
 *  Created on: Aug 7, 2016
 *      Author: gochaudhari
 */


#include "MainAlgorithm.hpp"
#include "AccelerometerModule.hpp"

MainAlgorithmProcess::MainAlgorithmProcess()
{
	gpsDataVar = GPSData();
	alcoholDataVar = AlcoholSensor();
	isRashDriving = false;
	isSpeeding = false;
	alcoholData = 0;
	allAcclerations = NULL;
	speed = 0;
	finalDrivingScore = 100;
}

void MainAlgorithmProcess::AlgorithmProcessing()
{
	finalDrivingScore = 100;

	// Term 1 - Read Speed Data
	speed = gpsDataVar.GetCurrentSpeed();

	// Term 2 - Read Aclcohol Data
	alcoholData = alcoholDataVar.ReadData();

	// Term 3 - Read Acceleration Data
	allAcclerations = GetAccelerometerData();
	maxAcceleration = max(max(allAcclerations[0], allAcclerations[1]), allAcclerations[2]);

	// High Speed check
	if(speed > DANGER_SPEED)
	{
		isSpeeding = true;
		individualDrivingScore.speedScore = 30;
	}
	else
	{
		isSpeeding = false;
		individualDrivingScore.speedScore = 0;
	}

	// High Acceleration check
	if(maxAcceleration > DANGER_ACCELERATION)
	{
		isAccelerating = true;
		individualDrivingScore.accelerationScore = 30;
	}
	else
	{
		isAccelerating = false;
		individualDrivingScore.accelerationScore = 0;
	}

	// High Alcohol content
	if(alcoholData > DANGER_ALCOHOL_CONTENT)
	{
		individualDrivingScore.alcoholScore = 30;
	}
	else
	{
		individualDrivingScore.alcoholScore = 0;
	}

	if(isSpeeding && isAccelerating)
	{
		isRashDriving = true;
	}
	else
	{
		isRashDriving = false;
	}

	finalDrivingScore = finalDrivingScore -
			(individualDrivingScore.alcoholScore +
			individualDrivingScore.accelerationScore +
			individualDrivingScore.speedScore
			);
}

bool MainAlgorithmProcess::IsRashDriving()
{
	AlgorithmProcessing();
	return isRashDriving;
}

bool MainAlgorithmProcess::IsSpeeding()
{
	AlgorithmProcessing();
	return isSpeeding;
}

bool MainAlgorithmProcess::IsAccelerating()
{
	AlgorithmProcessing();
	return isAccelerating;
}

int MainAlgorithmProcess::GetDrivingScore()
{
	AlgorithmProcessing();
	return finalDrivingScore;
}
