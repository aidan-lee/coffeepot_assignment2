/*
 * My_waterControlCode_CPP.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: aidan
 */

#include "MyCoffeePotFunctions.h"
#include "MyCoffeePotFunctions_forCPP.h"
#include "CoffeePotSimulatorFunctions2016.h"
#include "Assignment2Update.h"


void MyWaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int waterLevelRequired)
{
	//Set water flow rate
	int tenPercent = waterLevelRequired * 0.1;
	unsigned short int currentLevel = CurrentWaterLevel_CPP(coffeePot_baseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();


	while (currentLevel <= waterLevelRequired)
	{
		coffeePot_baseAddress->waterInFlowRegister = 100;
		//My_SimulatedOneSecondPassing(true);
		Assignment2Update();
		currentLevel = CurrentWaterLevel_CPP(coffeePot_baseAddress);
		if ((currentLevel <= waterLevelRequired + tenPercent) &&
								(currentLevel >= waterLevelRequired - tenPercent))
		{
			break;
		}
	}

	coffeePot_baseAddress->waterInFlowRegister = 0;
}

bool MyWaterControlCode_CPP_SM(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int waterLevelRequired)
{
	unsigned short int currentLevel = CurrentWaterLevel_CPP(coffeePot_baseAddress);
	int tenPercent = waterLevelRequired / 10;
	bool result;

	if(currentLevel < (waterLevelRequired - tenPercent))
	{
		coffeePot_baseAddress->waterInFlowRegister = tenPercent;//100;
		result = false;
	}
	else
	{
		coffeePot_baseAddress->waterInFlowRegister = 0;
		result = true;
	}

	return result;
}




