/*
 * Interrupt.cpp
 *
 *  Created on: Nov 23, 2017
 *      Author: aidan
 */

#include "CoffeePotSimulatorFunctions2016.h"
#include "stdio.h"
#include "blackfin.h"

volatile int timer = 0;
//extern volatile int timer;
void setUpCoreTimer()
{
	//TCNTL
	//Turn timer power on, set 1 in bit 0
	*pTCNTL |= TMPWR;
	//Enable auto-reload, set 1 in bit 2
	*pTCNTL |= TAUTORLD;
	//Timer has not generated an interrupt, set 0 in bit 3
	*pTCNTL &= ~TINT;

	//TCOUNT
	*pTCOUNT = 0x0;//0x1000;

	//TPERIOD
	*pTPERIOD = 0x3000;

	ssync();
}

void activateTimer()
{
	//Enable timer, set 1 in bit 1
	*pTCNTL |= TMREN;

	ssync();
}

void setUpIMask()
{
	// Who knows if this will work
	//*pIMASK = 0x00000040;

	//Taking into account the 0x0000 001F thats supposed to be there...
	*pIMASK = 0x0000005F;

	ssync();
}

void setUpSIC_IMask()
{
	*pSIC_IMASK = 0x0;

	ssync();
}

#pragma interrupt
extern "C" void ISR()
{
	//printf("inside interrupt service routine\n");
	//printf("Timer: %d\n", timer);
	//asm("raise 6;");
/*
	if((TCNTL & TINT) == 0)
		return;
*/

	/*
	if(counter >= 10)
		counter = 0;
	else

		timer++;
*/


	if(timer == 10)
	{
		timer = 0;
		printf("\n");
		UpdateSimulationDisplay();
	}
	else
	{
		CoffeePot_Sync();
		timer++;
	}


	// Turn off interrupt bit in TCNTL
	*pTCNTL &= ~0x8;

	ssync();
	//return;

	/*
	if(counter < 10)
	{
		CoffeePot_Sync();
		counter++;
	}
	else //Here, counter == 10
	{
		printf("\n");
		UpdateSimulationDisplay();
		counter = 0;
	}*/

}


