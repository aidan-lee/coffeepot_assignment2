/*
 * My_HeaterControlCode_CPP.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: aidan
 */

#include "MyCoffeePotFunctions.h"
#include "MyCoffeePotFunctions_forCPP.h"
#include "CoffeePotSimulatorFunctions2016.h"
#include "Assignment2Update.h"


void MyHeaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int temperatureRequired)
{
	//Set heating rate
	int tenPercent = temperatureRequired * 0.1;
	unsigned short int currentTemp = CurrentTemperature_CPP(coffeePot_baseAddress);
	coffeePot_baseAddress->heaterRegister = 255;
	coffeePot_baseAddress->heaterBoostRegister = 15;
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();
	int counter = 0;
	bool value = true;

	while (currentTemp <= temperatureRequired)
	{
		coffeePot_baseAddress->heaterRegister = 255;
		if (counter % 5 == 0)
		{
			value = true;
			printf("\n");
		}
		else
			value = false;
		//My_SimulatedOneSecondPassing(value);
		Assignment2Update();
		currentTemp = CurrentTemperature_CPP(coffeePot_baseAddress);
		if ((currentTemp <= temperatureRequired + tenPercent) &&
								(currentTemp >= temperatureRequired - tenPercent))
		{
			break;
		}
		counter++;
	}
	coffeePot_baseAddress->heaterRegister = 0;
	coffeePot_baseAddress->heaterBoostRegister = 0;
}

bool MyHeaterControlCode_CPP_SM(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int temperatureRequired)
{
	int currentTemp = CurrentTemperature_CPP(coffeePot_baseAddress);
	int tenPercent = temperatureRequired / 10;
	bool result;

	if(currentTemp < (temperatureRequired - tenPercent))
	{
		coffeePot_baseAddress->heaterRegister = 255;
		coffeePot_baseAddress->heaterBoostRegister = 15;
		result = false;
	}
	else
	{
		coffeePot_baseAddress->heaterRegister = 0;
		coffeePot_baseAddress->heaterBoostRegister = 0;
		result = true;
	}

	return result;
}

