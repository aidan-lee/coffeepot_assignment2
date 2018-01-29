/*
 * My_CoffeePotFunctions_CPP.cpp
 *
 *  Created on: Oct 23, 2017
 *      Author: aidan
 */

#include "MyCoffeePotFunctions_forCPP.h"
#include "CoffeePotSimulatorFunctions2016.h"
#include "MyCoffeePotFunctions.h"
#include "My_CoffeePot_2016main.h"
#include "Assignment2Update.h"
#include "Interrupt.h"
#include <stdio.h>

#include <GPIO2017/ADSP_GPIO_Interface.h>

//Macros are in MyCoffeePotFunctions_forCPP.h file

void DoQuickCheck(COFFEEPOT_DEVICE *coffeePot_baseAddress);

void turnOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | TURNON;
}

void LEDPowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | LEDPOWER;
}

void LED1PowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | LED1;
}


void insertPod(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | COFFEEPOD;
}

void removePod(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister & ~COFFEEPOD;
}

void pumpOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | WATERPUMP;
}

void LED2PowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | LED2;
}

void heatOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | HEATER;
}

void LED3PowerOn(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	coffeePot_baseAddress->controlRegister = coffeePot_baseAddress->controlRegister | LED3;
}

void printNewLine()
{
	printf("\n");
}

void My_MakeCoffeepot_ReadyForAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char *uniqueCoffeePotName)
{
	turnOn(coffeePot_BaseAddress);
	printf("\n");
	printf("I turn on the coffee pot and wait until ready\n");
	while ((coffeePot_BaseAddress->controlRegister & READYBIT) != READYBIT)
	{
		//My_SimulatedOneSecondPassing(true);
		Assignment2Update();
	}
	printf("Ready!\n");
}

void My_MakeTwoCoffeepots_ReadyForAction(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, COFFEEPOT_DEVICE *coffeePot2_BaseAddress)
{
	turnOn(coffeePot1_BaseAddress);
	turnOn(coffeePot2_BaseAddress);
	while(((coffeePot1_BaseAddress->controlRegister & READYBIT) != READYBIT) && ((coffeePot2_BaseAddress->controlRegister & READYBIT) != READYBIT))
	{
		//My_SimulatedOneSecondPassing(false);
		Assignment2Update();
	}
	printf("Ready!\n");
}

//Following code was completed because of planning ahead
#if 0
void Do_Simulation_CPP(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	//Turn on coffee pot by writing 1's to the control register
	turnOn(coffeePot_baseAddress);

	//Read the control ready bit of the register in a loop until coffee pot is ready
	//Ready: we must wait 2 seconds for the coffee pot to turn on
	//Using bitwise AND function

	printf("\n");
	printf("I turn on the coffee pot and wait until ready\n");
	while ((coffeePot_baseAddress->controlRegister & READYBIT) != READYBIT)
	{
		//My_SimulatedOneSecondPassing(true);
		Assignment2Update();
	}
	printf("Ready!\n");

	DoQuickCheck(coffeePot_baseAddress);
}

void DoQuickCheck(COFFEEPOT_DEVICE *coffeePot_baseAddress)
{
	//Check to see if the LED lights work

	//Turn on LED power using bitwise OR function
	printf("\n");
	printf("I turn on the LED power without turning off the device\n");
	LEDPowerOn(coffeePot_baseAddress);
	printf("After LED power on: %d\n", coffeePot_baseAddress->controlRegister);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();
	printf("After LED power on: %d\n", coffeePot_baseAddress->controlRegister);

	//Turn on LED1 to show system is powered up
	if ((coffeePot_baseAddress->controlRegister & LEDPOWER) == LEDPOWER)
		LED1PowerOn(coffeePot_baseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	//Insert coffee pod
	printf("\n");
	printf("I insert a coffee pod\n");
	insertPod(coffeePot_baseAddress);
	//My_SimulatedOneSecondPassing(true);

	//Remove coffee pod
	printf("\n");
	printf("I remove the coffee pod\n");
	removePod(coffeePot_baseAddress);
	My_SimulatedOneSecondPassing(true);

	/*
	//Try turning on the heater (Use a do looop here)
	UpdateSimulationDisplay();

	*/
}
#endif


void My_SimulatedOneSecondPassing(bool showDetail)
{
	if (showDetail)
		UpdateSimulationDisplay();
	else
		CoffeePot_Sync();
}


void My_DemonstrateCoffeePotAction(COFFEEPOT_DEVICE *coffeePot_BaseAddress, char *uniqueCoffeePotName,
unsigned short int waterLevelRequired, unsigned short int waterTemperatureRequired)
{
	//Turns on the coffee pot and initializes it
	My_MakeCoffeepot_ReadyForAction(coffeePot_BaseAddress, uniqueCoffeePotName);

	//Powering up LED display
	printf("\n");
	printf("I turn on the LED power without turning off the device\n");
	LEDPowerOn(coffeePot_BaseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	//Turn on LED1 to show system is powered up
	if ((coffeePot_BaseAddress->controlRegister & LEDPOWER) == LEDPOWER)
		LED1PowerOn(coffeePot_BaseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	//Turn on the power to the water pump and turn on LED2 to indicate
	printf("\n");
	printf("I activate the water pump power, and turn on LED 2 to indicate water pump power is on\n");
	pumpOn(coffeePot_BaseAddress);
	LED2PowerOn(coffeePot_BaseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	// Part 2
	#if Part2
	MyWaterControlCode_CPP(coffeePot_BaseAddress, waterLevelRequired);
	#endif

	// Part 3
	#if Part3
	MyWaterControlCode_ASM(coffeePot_BaseAddress, waterLevelRequired, waterLevelRequired * 0.1);
	#endif

	//Turn on the power to the heat and turn on LED3 to indicate
	printf("\nI activate the heater power, and turn on LED 3 to indicate heater power is on\n");
	heatOn(coffeePot_BaseAddress);
	LED3PowerOn(coffeePot_BaseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	// Part 4
	#if Part4
	MyHeaterControlCode_CPP(coffeePot_BaseAddress, waterTemperatureRequired);
	#endif

	// Part 5
	#if Part5
	MyHeaterControlCode_ASM(coffeePot_BaseAddress, waterTemperatureRequired / 10);
	#endif

}

void waitTillReadyTwoPots(COFFEEPOT_DEVICE *coffeePot_baseAddress1, unsigned short int waterLevel1, unsigned short int waterTemperature1,
		COFFEEPOT_DEVICE *coffeePot_baseAddress2, unsigned short int waterLevel2, unsigned short int waterTemperature2)
{
	// Turning coffee pots on and waiting until ready
	printf("\n");
	printf("I turn on the coffee pots and wait until ready\n");
	My_MakeTwoCoffeepots_ReadyForAction(coffeePot_baseAddress1, coffeePot_baseAddress2);

	//Powering up LED display and turning LED 1 on to indicate
	printf("\n");
	printf("I turn on the LED power without turning off the device\n");
	LEDPowerOn(coffeePot_baseAddress1);
	LEDPowerOn(coffeePot_baseAddress2);
	LED1PowerOn(coffeePot_baseAddress1);
	LED1PowerOn(coffeePot_baseAddress2);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	//Filling both pots with water

	//Turning on the water pump for pot 1 and turning on LED2 to indicate
	printf("\n");
	printf("I activate the water pump power for coffee pot 1, and turn on LED 2 to indicate water pump power is on\n");
	pumpOn(coffeePot_baseAddress1);
	LED2PowerOn(coffeePot_baseAddress1);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();
	//Filling pot 1 until it is 85% full
	printf("\n");
	printf("I fill coffee pot 1 until it is 85%% full\n");
	MyWaterControlCode_CPP(coffeePot_baseAddress1, waterLevel1 * 0.85);

	//Turning on the water pump for pot 2 and turning on LED2 to indicate
	printf("\n");
	printf("I activate the water pump power for coffee pot 2, and turn on LED 2 to indicate water pump power is on\n");
	pumpOn(coffeePot_baseAddress2);
	LED2PowerOn(coffeePot_baseAddress2);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();
	//Filling pot 2 until it is 95% full
	printf("\n");
	printf("I fill coffee pot 2 until it is 95%% full\n");
	MyWaterControlCode_CPP(coffeePot_baseAddress2, waterLevel2 * 0.95);

	//Heating both pots to desired level

	//Turn on the power to the heat for pot 1 and turn on LED3 to indicate
	printf("\nI activate the heater power for coffee pot 1, and turn on LED 3 to indicate heater power is on\n");
	heatOn(coffeePot_baseAddress1);
	LED3PowerOn(coffeePot_baseAddress1);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();
	//Heating pot 1 until it is 90 degrees
	MyHeaterControlCode_CPP(coffeePot_baseAddress1, waterTemperature1);
	unsigned short int temp = CurrentTemperature_CPP(coffeePot_baseAddress1);

	//Turn on the power to the heat for pot 2 and turn on LED3 to indicate
	printf("\n\nI activate the heater power for coffee pot 2, and turn on LED 3 to indicate heater power is on\n");
	heatOn(coffeePot_baseAddress2);
	LED3PowerOn(coffeePot_baseAddress2);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();
	//Heating pot 2 until it is 85 degrees
	MyHeaterControlCode_CPP(coffeePot_baseAddress2, waterTemperature2);
	temp = CurrentTemperature_CPP(coffeePot_baseAddress2);

	//Maintaining levels of both pots
	printf("\n\nMaintaining levels of both pots\n");
	while(1)
	{
		bool maintained = false;
		printf("\n---------------------------------------------------------\n");
		unsigned short int level1 = CurrentWaterLevel_CPP(coffeePot_baseAddress1);
		int tenPercentLevel1 = (waterLevel1 * 0.85) / 10;
		unsigned short int level2 = CurrentWaterLevel_CPP(coffeePot_baseAddress2);
		int tenPercentLevel2 = (waterLevel2 * 0.95) / 10;
		unsigned short int temp1 = CurrentTemperature_CPP(coffeePot_baseAddress1);
		int tenPercentTemp1 = waterTemperature1 / 10;
		unsigned short int temp2 = CurrentTemperature_CPP(coffeePot_baseAddress2);
		int tenPercentTemp2 = waterTemperature2 / 10;

		if (level1 < ((waterLevel1 * 0.85) - tenPercentLevel1))
		{
			printf("\nMaintain water of coffee pot 1\n");
			MyWaterControlCode_CPP(coffeePot_baseAddress1, waterLevel1 * 0.85);
			maintained = true;
			printf("\n");
		}

		if (level2 < ((waterLevel2 * 0.95) - tenPercentLevel2))
		{
			printf("\nMaintain water of coffee pot 2\n");
			MyWaterControlCode_CPP(coffeePot_baseAddress2, waterLevel2 * 0.95);
			maintained = true;
			printf("\n");
		}

		if (temp1 < (waterTemperature1 - tenPercentTemp1))
		{
			printf("\nMaintain heat of coffee pot 1\n");
			MyHeaterControlCode_CPP(coffeePot_baseAddress1, waterTemperature1);
			maintained = true;
			printf("\n");
		}

		if (temp2 < (waterTemperature2 - tenPercentTemp2))
		{
			printf("\nMaintain heat of coffee pot 2\n");
			MyHeaterControlCode_CPP(coffeePot_baseAddress2, waterTemperature2);
			maintained = true;
			printf("\n");
		}

		if (!maintained)
		{
			printf("\nNothing maintained\n");
			//My_SimulatedOneSecondPassing(true);
			Assignment2Update();
		}
	}

}


// Part 7, 3 pots
extern volatile int timer;
void pollTillReadyThreePots(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, unsigned short int waterLevel1, unsigned short int waterTemperature1,
			COFFEEPOT_DEVICE *coffeePot2_BaseAddress, unsigned short int waterLevel2, unsigned short int waterTemperature2,
			COFFEEPOT_DEVICE *coffeePot3_BaseAddress, unsigned short int waterLevel3, unsigned short int waterTemperature3)
{
	printf("\nTurning on coffee pots\n");
	//Turning on
	turnOn(coffeePot1_BaseAddress);
	turnOn(coffeePot2_BaseAddress);
	turnOn(coffeePot3_BaseAddress);
	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	printf("\nEnabling LED display, water pump, heater, and the associated LEDs for all coffee pots\n");
	//Turning on LED display
	LEDPowerOn(coffeePot1_BaseAddress);
	LEDPowerOn(coffeePot2_BaseAddress);
	LEDPowerOn(coffeePot3_BaseAddress);
	//Turn on LED1 to show pot is on
	LED1PowerOn(coffeePot1_BaseAddress);
	LED1PowerOn(coffeePot2_BaseAddress);
	LED1PowerOn(coffeePot3_BaseAddress);
	//Turn on water pump
	pumpOn(coffeePot1_BaseAddress);
	pumpOn(coffeePot2_BaseAddress);
	pumpOn(coffeePot3_BaseAddress);
	//Turn on LED 2 to show water pump is on
	LED2PowerOn(coffeePot1_BaseAddress);
	LED2PowerOn(coffeePot2_BaseAddress);
	LED2PowerOn(coffeePot3_BaseAddress);
	//Turn on heater
	heatOn(coffeePot1_BaseAddress);
	heatOn(coffeePot2_BaseAddress);
	heatOn(coffeePot3_BaseAddress);
	//Turn on LED 3 to show heater is on
	LED3PowerOn(coffeePot1_BaseAddress);
	LED3PowerOn(coffeePot2_BaseAddress);
	LED3PowerOn(coffeePot3_BaseAddress);

	//My_SimulatedOneSecondPassing(true);
	Assignment2Update();

	bool pot1Ready = false;
	bool pot2Ready = false;
	bool pot3Ready = false;

	unsigned short int level1 = CurrentWaterLevel_CPP(coffeePot1_BaseAddress);
	unsigned short int level2 = CurrentWaterLevel_CPP(coffeePot2_BaseAddress);
	unsigned short int level3 = CurrentWaterLevel_CPP(coffeePot3_BaseAddress);

	unsigned short int temp1 = CurrentTemperature_CPP(coffeePot1_BaseAddress);
	unsigned short int temp2 = CurrentTemperature_CPP(coffeePot2_BaseAddress);
	unsigned short int temp3 = CurrentTemperature_CPP(coffeePot3_BaseAddress);

	int counter = 0;
	//Super loop
	while(1)
	{
		bool display = false;

		//Waiting until pots are ready

		//Waiting until pot 1 is ready
		if (((coffeePot1_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot1Ready)
		{
			pot1Ready = true;
			display = true;
		}
		if (((coffeePot2_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot2Ready)
		{
			pot2Ready = true;
			display = true;
		}
		if (((coffeePot3_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot3Ready)
		{
			pot3Ready = true;
			display = true;
		}

		//If all pots are ready
		if(pot1Ready && pot2Ready && pot3Ready)
		{
			bool pot1Filled = MyWaterControlCode_CPP_SM(coffeePot1_BaseAddress, waterLevel1);
			bool pot2Filled = MyWaterControlCode_CPP_SM(coffeePot2_BaseAddress, waterLevel2);
			bool pot3Filled = MyWaterControlCode_ASM_SM(coffeePot3_BaseAddress, waterLevel3, waterLevel3 / 10);


			bool pot1Heated = MyHeaterControlCode_CPP_SM(coffeePot1_BaseAddress, waterTemperature1);
			bool pot2Heated = MyHeaterControlCode_CPP_SM(coffeePot2_BaseAddress, waterTemperature2);
			bool pot3Heated = MyHeaterControlCode_ASM_SM(coffeePot3_BaseAddress, waterTemperature3, waterTemperature3 / 10);


			if(counter % 8 == 0)
			{
				display = true;
			}
			counter++;
		}

		if(display)
			printf("\n");
		//My_SimulatedOneSecondPassing(display);
		Assignment2Update();
		#if !CPP_Interrupt
		if(timer == 10)
			UpdateSimulationDisplay();
		else
			CoffeePot_Sync();
		#endif


	}

}

// Part 7, 4 pots
extern volatile int timer;
void pollTillReadyFourPots(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, unsigned short int waterLevel1, unsigned short int waterTemperature1,
			COFFEEPOT_DEVICE *coffeePot2_BaseAddress, unsigned short int waterLevel2, unsigned short int waterTemperature2,
			COFFEEPOT_DEVICE *coffeePot3_BaseAddress, unsigned short int waterLevel3, unsigned short int waterTemperature3,
			COFFEEPOT_DEVICE *coffeePot4_BaseAddress, unsigned short int waterLevel4, unsigned short int waterTemperature4)
{
	printf("\nTurning on coffee pots\n");
		//Turning on
		turnOn(coffeePot1_BaseAddress);
		turnOn(coffeePot2_BaseAddress);
		turnOn(coffeePot3_BaseAddress);
		turnOn(coffeePot4_BaseAddress);
		My_SimulatedOneSecondPassing(true);
		//Assignment2Update();

		printf("\nEnabling LED display, water pump, heater, and the associated LEDs for all coffee pots\n");
		//Turning on LED display
		LEDPowerOn(coffeePot1_BaseAddress);
		LEDPowerOn(coffeePot2_BaseAddress);
		LEDPowerOn(coffeePot3_BaseAddress);
		LEDPowerOn(coffeePot4_BaseAddress);
		//Turn on LED1 to show pot is on
		LED1PowerOn(coffeePot1_BaseAddress);
		LED1PowerOn(coffeePot2_BaseAddress);
		LED1PowerOn(coffeePot3_BaseAddress);
		LED1PowerOn(coffeePot4_BaseAddress);
		//Turn on water pump
		pumpOn(coffeePot1_BaseAddress);
		pumpOn(coffeePot2_BaseAddress);
		pumpOn(coffeePot3_BaseAddress);
		pumpOn(coffeePot4_BaseAddress);
		//Turn on LED 2 to show water pump is on
		LED2PowerOn(coffeePot1_BaseAddress);
		LED2PowerOn(coffeePot2_BaseAddress);
		LED2PowerOn(coffeePot3_BaseAddress);
		LED2PowerOn(coffeePot4_BaseAddress);
		//Turn on heater
		heatOn(coffeePot1_BaseAddress);
		heatOn(coffeePot2_BaseAddress);
		heatOn(coffeePot3_BaseAddress);
		heatOn(coffeePot4_BaseAddress);
		//Turn on LED 3 to show heater is on
		LED3PowerOn(coffeePot1_BaseAddress);
		LED3PowerOn(coffeePot2_BaseAddress);
		LED3PowerOn(coffeePot3_BaseAddress);
		LED3PowerOn(coffeePot4_BaseAddress);

		My_SimulatedOneSecondPassing(true);
		//Assignment2Update();

		bool pot1Ready = false;
		bool pot2Ready = false;
		bool pot3Ready = false;
		bool pot4Ready = false;

		unsigned short int level1 = CurrentWaterLevel_CPP(coffeePot1_BaseAddress);
		unsigned short int level2 = CurrentWaterLevel_CPP(coffeePot2_BaseAddress);
		unsigned short int level3 = CurrentWaterLevel_CPP(coffeePot3_BaseAddress);
		unsigned short int level4 = CurrentWaterLevel_CPP(coffeePot4_BaseAddress);

		unsigned short int temp1 = CurrentTemperature_CPP(coffeePot1_BaseAddress);
		unsigned short int temp2 = CurrentTemperature_CPP(coffeePot2_BaseAddress);
		unsigned short int temp3 = CurrentTemperature_CPP(coffeePot3_BaseAddress);
		unsigned short int temp4 = CurrentTemperature_CPP(coffeePot4_BaseAddress);

		int counter = 0;
		//Super loop
		while(1)
		{
			bool display = false;

			//Waiting until pots are ready

			//Waiting until pot 1 is ready
			if (((coffeePot1_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot1Ready)
			{
				pot1Ready = true;
				display = true;
			}
			if (((coffeePot2_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot2Ready)
			{
				pot2Ready = true;
				display = true;
			}
			if (((coffeePot3_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot3Ready)
			{
				pot3Ready = true;
				display = true;
			}
			if (((coffeePot4_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot4Ready)
			{
				pot4Ready = true;
				display = true;
			}

			//If all pots are ready
			//printf("Pot1: %d, Pot2: %d, Pot3: %d, Pot4: %d\n", pot1Ready, pot2Ready, pot3Ready, pot4Ready);
			if(pot1Ready && pot2Ready && pot3Ready && pot4Ready)
			{
				bool pot1Filled = MyWaterControlCode_CPP_SM(coffeePot1_BaseAddress, waterLevel1);
				bool pot2Filled = MyWaterControlCode_CPP_SM(coffeePot2_BaseAddress, waterLevel2);
				bool pot3Filled = MyWaterControlCode_ASM_SM(coffeePot3_BaseAddress, waterLevel3, waterLevel3 / 10);
				bool pot4Filled = MyWaterControlCode_CPP_SM(coffeePot4_BaseAddress, waterLevel4);

				bool pot1Heated = MyHeaterControlCode_CPP_SM(coffeePot1_BaseAddress, waterTemperature1);
				bool pot2Heated = MyHeaterControlCode_CPP_SM(coffeePot2_BaseAddress, waterTemperature2);
				bool pot3Heated = MyHeaterControlCode_ASM_SM(coffeePot3_BaseAddress, waterTemperature3, waterTemperature3 / 10);
				bool pot4Heated = MyHeaterControlCode_CPP_SM(coffeePot4_BaseAddress, waterTemperature4);

				if(counter % 8 == 0)
				{
					display = true;
				}
				counter++;
			}

			Assignment2Update();

			#if !CPPinterrupt
			if ((timer % 10) == 0 || timer == 0)
			{
				printf("\n");
				UpdateSimulationDisplay();
			}
			else
				CoffeePot_Sync();
			#endif


		}

}

void switchesPollTillReadyFourPots(COFFEEPOT_DEVICE *coffeePot1_BaseAddress, unsigned short int waterLevel1, unsigned short int waterTemperature1,
			COFFEEPOT_DEVICE *coffeePot2_BaseAddress, unsigned short int waterLevel2, unsigned short int waterTemperature2,
			COFFEEPOT_DEVICE *coffeePot3_BaseAddress, unsigned short int waterLevel3, unsigned short int waterTemperature3,
			COFFEEPOT_DEVICE *coffeePot4_BaseAddress, unsigned short int waterLevel4, unsigned short int waterTemperature4)
{
	Init_Input_GPIOInterface();
	Init_LED_GPIOInterface();
	Write_LED_GPIOInterface(0x0);

	unsigned short int readValue = Read_Input_GPIOInterface();

	if((readValue & SW1) != 0)
	{
		printf("\nTurning on coffee pots\n");
		//Turning on
		turnOn(coffeePot1_BaseAddress);
		turnOn(coffeePot2_BaseAddress);
		turnOn(coffeePot3_BaseAddress);
		turnOn(coffeePot4_BaseAddress);
		My_SimulatedOneSecondPassing(true);
		//Assignment2Update();

		printf("\nEnabling LED display, water pump, heater, and the associated LEDs for all coffee pots\n");
		//Turning on LED display
		LEDPowerOn(coffeePot1_BaseAddress);
		LEDPowerOn(coffeePot2_BaseAddress);
		LEDPowerOn(coffeePot3_BaseAddress);
		LEDPowerOn(coffeePot4_BaseAddress);
		//Turn on LED1 to show pot is on
		LED1PowerOn(coffeePot1_BaseAddress);
		LED1PowerOn(coffeePot2_BaseAddress);
		LED1PowerOn(coffeePot3_BaseAddress);
		LED1PowerOn(coffeePot4_BaseAddress);
		//Turn on water pump
		pumpOn(coffeePot1_BaseAddress);
		pumpOn(coffeePot2_BaseAddress);
		pumpOn(coffeePot3_BaseAddress);
		pumpOn(coffeePot4_BaseAddress);
		//Turn on LED 2 to show water pump is on
		LED2PowerOn(coffeePot1_BaseAddress);
		LED2PowerOn(coffeePot2_BaseAddress);
		LED2PowerOn(coffeePot3_BaseAddress);
		LED2PowerOn(coffeePot4_BaseAddress);
		//Turn on heater
		heatOn(coffeePot1_BaseAddress);
		heatOn(coffeePot2_BaseAddress);
		heatOn(coffeePot3_BaseAddress);
		heatOn(coffeePot4_BaseAddress);
		//Turn on LED 3 to show heater is on
		LED3PowerOn(coffeePot1_BaseAddress);
		LED3PowerOn(coffeePot2_BaseAddress);
		LED3PowerOn(coffeePot3_BaseAddress);
		LED3PowerOn(coffeePot4_BaseAddress);

		My_SimulatedOneSecondPassing(true);
		//Assignment2Update();

		//Write into LED interface
		//unsigned short int oldValue1 = Read_LED_GPIOInterface();
		unsigned short int result1 = coffeePot1_BaseAddress->controlRegister & LEDMASK;
		result1 = result1 >> 12;
		Write_LED_GPIOInterface(result1);//oldValue1 | result1);

		bool pot1Ready = false;
	bool pot2Ready = false;
		bool pot3Ready = false;
		bool pot4Ready = false;

		unsigned short int level1 = CurrentWaterLevel_CPP(coffeePot1_BaseAddress);
		unsigned short int level2 = CurrentWaterLevel_CPP(coffeePot2_BaseAddress);
		unsigned short int level3 = CurrentWaterLevel_CPP(coffeePot3_BaseAddress);
		unsigned short int level4 = CurrentWaterLevel_CPP(coffeePot4_BaseAddress);

		unsigned short int temp1 = CurrentTemperature_CPP(coffeePot1_BaseAddress);
		unsigned short int temp2 = CurrentTemperature_CPP(coffeePot2_BaseAddress);
		unsigned short int temp3 = CurrentTemperature_CPP(coffeePot3_BaseAddress);
		unsigned short int temp4 = CurrentTemperature_CPP(coffeePot4_BaseAddress);

		int counter = 0;
		//Super loop
		while(1)
		{
			bool display = false;

			//Waiting until pots are ready

			//Waiting until pot 1 is ready
			if (((coffeePot1_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot1Ready)
			{
				pot1Ready = true;
				display = true;
			}
			if (((coffeePot2_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot2Ready)
			{
				pot2Ready = true;
				display = true;
			}
			if (((coffeePot3_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot3Ready)
			{
				pot3Ready = true;
				display = true;
			}
			if (((coffeePot4_BaseAddress->controlRegister & READYBIT) == READYBIT) && !pot4Ready)
			{
				pot4Ready = true;
				display = true;
			}

			//If all pots are ready
			//printf("Pot1: %d, Pot2: %d, Pot3: %d, Pot4: %d\n", pot1Ready, pot2Ready, pot3Ready, pot4Ready);
			if(pot1Ready && pot2Ready && pot3Ready && pot4Ready)
			{
				//Turn on water
				if((readValue & SW2) != 0)
				{
					bool pot1Filled = MyWaterControlCode_CPP_SM(coffeePot1_BaseAddress, waterLevel1);
					bool pot2Filled = MyWaterControlCode_CPP_SM(coffeePot2_BaseAddress, waterLevel2);
					bool pot3Filled = MyWaterControlCode_ASM_SM(coffeePot3_BaseAddress, waterLevel3, waterLevel3 / 10);
					bool pot4Filled = MyWaterControlCode_CPP_SM(coffeePot4_BaseAddress, waterLevel4);
				}

				if((readValue & SW3) != 0)
				{
					bool pot1Heated = MyHeaterControlCode_CPP_SM(coffeePot1_BaseAddress, waterTemperature1);
					bool pot2Heated = MyHeaterControlCode_CPP_SM(coffeePot2_BaseAddress, waterTemperature2);
					bool pot3Heated = MyHeaterControlCode_ASM_SM(coffeePot3_BaseAddress, waterTemperature3, waterTemperature3 / 10);
					bool pot4Heated = MyHeaterControlCode_CPP_SM(coffeePot4_BaseAddress, waterTemperature4);
				}

			}

			//if(display)
				//printf("\n");
			//My_SimulatedOneSecondPassing(display);
			//printf("Calling assignment 2 update\n");
			Assignment2Update();

			/*
			if ((timer % 10) == 0)
				UpdateSimulationDisplay();
			else
				CoffeePot_Sync();
				*/

			//Write into LED interface
			unsigned short int oldValue2 = Read_LED_GPIOInterface();
			unsigned short int result2 = coffeePot1_BaseAddress->controlRegister & LEDMASK;
			result2 = result2 >> 12;
			Write_LED_GPIOInterface(oldValue2 | result2);
		}
	}
}





