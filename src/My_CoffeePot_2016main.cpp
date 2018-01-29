/*****************************************************************************
 * My_CoffeePot_2017Assignment.cpp
 *****************************************************************************/



#include <sys/platform.h>
#include "adi_initialize.h"
#include <stdio.h>

#include "CoffeePotSimulatorFunctions2016.h"
#include "CoffeePot_SimulatorStructures.h"
#include "My_CoffeePot_2016main.h"
#include "MyCoffeePotFunctions.h"
#include "MyCoffeePotFunctions_forCPP.h"

#include "Assignment2Update.h"
#include "Interrupt.h"



/*
 * NOTE:
 * Please see My_CoffeePot_2016main.h for compilation instructions
 */


/** 
 * If you want to use command program arguments, then place them in the following string. 
 */
char __argv_string[] = "";


int main(int argc, char *argv[])
{
	/**
	 * Initialize managed drivers and/or services that have been added to 
	 * the project.
	 * @return zero on success 
	 */
	adi_initComponents();
	
	/* Begin adding your custom code here */

// Use mathematical paragraphs to separate ideas
	printf("\n");
	printf("About to start my coffee pot simulator\n");

	int numCoffeePots = 4;// Plan ahead to control 2

	WHICHDISPLAY whichDisplay = USE_TEXT_GUI;
	/*
	WHICHDISPLAY whichDisplay = USE_CCES_GUI;
	WHICHDISPLAY whichDisplay = (USE_TEXT_GUI | USE_CCES_GUI);
	*/

	Init_CoffeePotSimulation(numCoffeePots, (WHICHDISPLAY) whichDisplay);

	char uniqueCoffeePotName1[] = "AL1";// Name characteristics sets coffee-pot size
	char uniqueCoffeePotName2[] = "AL2";
	char uniqueCoffeePotName3[] = "AL3";
	char uniqueCoffeePotName4[] = "K9"; //Dr. Who's companion


	//Assignment 2 in CPP
	setUpCoreTimer();
	setUpIMask();
	setUpSIC_IMask();
	#if CPPinterrupt
	setISR_EVT_CPP();
	#endif
	#if !CPPinterrupt
	setISR_EVT_ASM();
	#endif


// Simulate plugging in new plug-and-play coffee pot control device into USB port
	COFFEEPOT_DEVICE *coffeePot1_BaseAddress = (COFFEEPOT_DEVICE*) NULL; // PSP Always initialize pointers to NULL
	coffeePot1_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT1, uniqueCoffeePotName1);

// NOTHING HAPPENS UNTIL YOU MAKE 1 SECOND OF MOCK TIME PASS;
#if Parts12345
	My_SimulatedOneSecondPassing(true);   // Shows detail
	//Assignment2Update();
#endif
// Going to call the code to fill a coffee pot to a desired water level, but no heating
	unsigned short int waterLevelRequired1 = 690 * 0.9;
	unsigned short int waterTemperatureRequired1 = 90;

// Parts 1, 2, 3, 4, 5
#if Parts12345
	My_DemonstrateCoffeePotAction(coffeePot1_BaseAddress, uniqueCoffeePotName1, waterLevelRequired1, waterTemperatureRequired1);
#endif

#if MultiplePots
// Simulate plugging in new plug-and-play coffee pot control device into USB port
	COFFEEPOT_DEVICE *coffeePot2_BaseAddress = (COFFEEPOT_DEVICE *) NULL; // PSP Always initialize pointers to NULL
	coffeePot2_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT2, uniqueCoffeePotName2);


// NOTHING HAPPENS UNTIL YOU MAKE 1 SECOND OF MOCK TIME PASS;
	#if !Part7
	My_SimulatedOneSecondPassing(true);
	//Assignment2Update();
	#endif

// Going to call the code to fill a coffee pot to a desired water level, but no heating
	unsigned short int waterLevelRequired2 = 691 * 0.9;
	unsigned short int waterTemperatureRequired2 = 85;

	// Part 6
	#if Part6
	// Use wait-till-ready ideas
	waitTillReadyTwoPots(coffeePot1_BaseAddress, waterLevelRequired1, waterTemperatureRequired1,
			coffeePot2_BaseAddress, waterLevelRequired2, waterTemperatureRequired2);
	#endif
#endif

#if DO_SECOND_POT
	My_DemonstrateCoffeePotAction(coffeePot2_BaseAddress, uniqueCoffeePotName2, waterLevelRequired2, waterTemperatureRequired2);
#endif

// Part 7
#if Part7
	// Simulate plugging in new plug-and-play coffee pot control device into USB port
		COFFEEPOT_DEVICE *coffeePot3_BaseAddress = (COFFEEPOT_DEVICE *) NULL; // PSP Always initialize pointers to NULL
		coffeePot3_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT3, uniqueCoffeePotName3);


	// NOTHING HAPPENS UNTIL YOU MAKE 1 SECOND OF MOCK TIME PASS;
	#if !fourPotsAtOnce
		//My_SimulatedOneSecondPassing(true);
		Assignment2Update();
	#endif

	// Going to call the code to fill a coffee pot to a desired water level, but no heating
		unsigned short int waterLevelRequired3 = 692 * 0.9;
		unsigned short int waterTemperatureRequired3 = 100;

	// Controlling 3 pots at the same time, 1 and 2 in C++ and 3 in ASM
		#if threePotsAtOnce
		pollTillReadyThreePots(coffeePot1_BaseAddress, waterLevelRequired1, waterTemperatureRequired1,
			coffeePot2_BaseAddress, waterLevelRequired2, waterTemperatureRequired2,
			coffeePot3_BaseAddress, waterLevelRequired3, waterTemperatureRequired3);
		#endif

	// Controlling 4 pots at the same time, 1 and 2 and 4 in C++ and 3 in ASM
		#if fourPotsAtOnce
		COFFEEPOT_DEVICE *coffeePot4_BaseAddress = (COFFEEPOT_DEVICE *) NULL; // PSP Always initialize pointers to NULL
		coffeePot4_BaseAddress = Add_CoffeePotToSystem_PlugAndPlay(COFFEEPOT4, uniqueCoffeePotName4);

		My_SimulatedOneSecondPassing(true);
		//Assignment2Update();

		unsigned short int waterLevelRequired4 = 632 * 0.9;
		unsigned short int waterTemperatureRequired4 = 100;

		#if !switches
		pollTillReadyFourPots(coffeePot1_BaseAddress, waterLevelRequired1, waterTemperatureRequired1,
					coffeePot2_BaseAddress, waterLevelRequired2, waterTemperatureRequired2,
					coffeePot3_BaseAddress, waterLevelRequired3, waterTemperatureRequired3,
					coffeePot4_BaseAddress, waterLevelRequired4, waterTemperatureRequired4);
		#endif

		#if switches
		switchesPollTillReadyFourPots(coffeePot1_BaseAddress, waterLevelRequired1, waterTemperatureRequired1,
						coffeePot2_BaseAddress, waterLevelRequired2, waterTemperatureRequired2,
						coffeePot3_BaseAddress, waterLevelRequired3, waterTemperatureRequired3,
						coffeePot4_BaseAddress, waterLevelRequired4, waterTemperatureRequired4);
		#endif

		#endif
#endif

/*
#if CONTROL_TWO_POTS_AT_SAME_TIME
// Here is an example of C++ function overloading causing name mangling
// Use poll-if-ready ideas
	My_DemonstrateCoffeePotAction(hardwareControl,
		coffeePot1_BaseAddress, uniqueCoffeePotName1, waterLevelRequired1, waterTemperatureRequired1,
		coffeePot2_BaseAddress, uniqueCoffeePotName2, waterLevelRequired2, waterTemperatureRequired2);
#endif
*/

	return 0;

}

