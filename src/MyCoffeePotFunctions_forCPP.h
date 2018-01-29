/*
 * MyCoffePotFunctions_forCPP.h
 *
 *  Created on: Oct 23, 2017
 *      Author: aidan
 */

#ifndef MYCOFFEEPOTFUNCTIONS_FORCPP_H_
#define MYCOFFEEPOTFUNCTIONS_FORCPP_H_

#include "CoffeePotSimulatorFunctions2016.h"
#include "CoffeePot_SimulatorStructures.h"
#include "MyCoffeePotFunctions.h"

#define TURNON 0x1
#define READYBIT 0x10
#define LEDPOWER 0x2

#define LED1 0x1000
#define LED2 0x2000
#define LED3 0X4000
#define LED4 0x8000

#define WATERPUMP 0x4
#define HEATER 0x8

#define COFFEEPOD 0x800

#define SW1 0x0010
#define SW2 0x0020
#define SW3 0x0040

#define LEDMASK 0xF000


void DoQuickCheck(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void Do_Simulation_CPP(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void turnOn(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void LEDPowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void LED1PowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void insertPod(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void pumpOn(COFFEEPOT_DEVICE *coffeePot_baseAddress);
void LED2PowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress);

void MyWaterControlCode_CPP(COFFEEPOT_DEVICE *coffeePot_baseAddress, unsigned short int waterLevelRequired);


#endif /* MYCOFFEEPOTFUNCTIONS_FORCPP_H_ */
