/*
#ifndef MYCOFFEEPOTCONTROLFUNCTIONS_H_
#define MYCOFFEEPOTCONTROLFUNCTIONS_H_
*/

#ifndef MYCOFFEEPOTFUNCTIONS_H_
#define MYCOFFEEPOTFUNCTIONS_H_

#include "CoffeePotSimulatorFunctions2016.h"
#include <stdio.h>

void My_SimulatedOneSecondPassing(bool showDetail);
void My_SimulatedOneSecondPassing_CPP(bool showDetail);
extern "C" void My_SimulatedOneSecondPassing_ASM(bool showDetail);

void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char *uniqueCoffeePotName,
unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired);

void My_MakeCoffeepot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char *uniqueCoffeePotName);

void MyWaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired);
extern "C" void MyWaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired, unsigned short int tenPercent);
bool MyWaterControlCode_CPP_SM(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int waterLevelRequired);
extern "C" bool MyWaterControlCode_ASM_SM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired, unsigned short int tenPercent);



void MyHeaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterTemperatureRequired);
extern "C" void MyHeaterControlCode_ASM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int tenPercent);
void printNewLine();
bool MyHeaterControlCode_CPP_SM(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int temperatureRequired);
extern "C" bool MyHeaterControlCode_ASM_SM(COFFEEPOT_DEVICE *coffeePot_BaseAddress, unsigned short int waterLevelRequired, unsigned short int tenPercent);


void waitTillReadyTwoPots(COFFEEPOT_DEVICE *coffeePot_baseAddress1, unsigned short int waterLevel1, unsigned short int waterTemperature1,
		COFFEEPOT_DEVICE *coffeePot_baseAddress2, unsigned short int waterLevel2, unsigned short int waterTemperature2);

void pollTillReadyThreePots(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, unsigned short int waterLevel1, unsigned short int waterTemperature1,
			COFFEEPOT_DEVICE *coffeePot2_BaseAddress, unsigned short int waterLevel2, unsigned short int waterTemperature2,
			COFFEEPOT_DEVICE *coffeePot3_BaseAddress, unsigned short int waterLevel3, unsigned short int waterTemperature3);


void pollTillReadyFourPots(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, unsigned short int waterLevel1, unsigned short int waterTemperature1,
			COFFEEPOT_DEVICE *coffeePot2_BaseAddress, unsigned short int waterLevel2, unsigned short int waterTemperature2,
			COFFEEPOT_DEVICE *coffeePot3_BaseAddress, unsigned short int waterLevel3, unsigned short int waterTemperature3,
			COFFEEPOT_DEVICE *coffeePot4_BaseAddress, unsigned short int waterLevel4, unsigned short int waterTemperature4);

void switchesPollTillReadyFourPots(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, unsigned short int waterLevel1, unsigned short int waterTemperature1,
			COFFEEPOT_DEVICE *coffeePot2_BaseAddress, unsigned short int waterLevel2, unsigned short int waterTemperature2,
			COFFEEPOT_DEVICE *coffeePot3_BaseAddress, unsigned short int waterLevel3, unsigned short int waterTemperature3,
			COFFEEPOT_DEVICE *coffeePot4_BaseAddress, unsigned short int waterLevel4, unsigned short int waterTemperature4);

#endif /* MYCOFFEEPOTFUNCTIONS_H_ */
