/*
 * Interrupt_ASM.asm
 *
 *  Created on: Nov 26, 2017
 *      Author: aidan
 */

#include "blackfin.h"

.section L1_data;
	.extern _timer;								//volatile int timer = 0;
		
#define timer_P0 P0
#define TCNTL_R0 R0
#define TINT_R1 R1

.section program;
.global _ISR_ASM;

_ISR_ASM:											//extern "C" void ISR_ASM()
	//Special code to handle silicon race issues	//{
	
	[--SP] = RETS;
	[--SP] = FP;
	[--SP] = ASTAT;
	
	[--SP] = P0;
	[--SP] = R0;
	[--SP] = R1;
	
	LINK 16; //Since we are calling subroutines
	
	P0.L = lo(_timer);						
	P0.H = hi(_timer);
		
	R0 = 10;	
	R1 = [timer_P0];							// if (timer == 10)
	CC = R1 == R0;								// {
	IF !CC JUMP ELSE;
	
	R0 = [timer_P0];								// timer = 0;
	R0 = 0;
	[timer_P0] = R0;
	/*
	.extern __Z12printNewLinev						// printf("\n");
		CALL __Z12printNewLinev;
		
	.extern __Z23UpdateSimulationDisplayv
		CALL __Z23UpdateSimulationDisplayv;			// UdateSimulationDisplay();
		*/											// }
	
	JUMP DONE;
	
	ELSE:
	/*
	 												// else
	.extern __Z14CoffeePot_Syncv					// {
		CALL __Z14CoffeePot_Syncv;					//	CoffeePot_Sync();
	*/	
	R0 = [timer_P0];								// 	timer++;
	R0 += 1;
	[timer_P0] = R0;
													// }
	DONE:
	
	P0.L = lo(TCNTL);				
	P0.H = hi(TCNTL);
	TCNTL_R0 = [P0];
	R1 = ~TINT;
	TCNTL_R0 = TCNTL_R0 & R1;				
	[P0] = R0;										//*pTCNTL &= ~0x8;
						
	ssync;											//ssync();
	
	UNLINK;
	R1 = [SP++];
	R0 = [SP++];
	P0 = [SP++];
	ASTAT = [SP++];
	FP = [SP++];
	RETS = [SP++];
	
_ISR_ASM.END:										// } //end of function
	RTI;


