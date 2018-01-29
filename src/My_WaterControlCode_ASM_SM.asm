/*
 * My_WaterControlCode_ASM_SM.asm
 *
 *  Created on: Oct 30, 2017
 *      Author: aidan
 */

 
#include "My_CoffeePot_2016main.h"
#include <blackfin.h>
 
 //#define LED_WATERPOWER LED4
 //#define LED_LEDPOWER LED3
 
 
 .section L1_data;
 
 
 #define INPAR1_R0 R0
 #define INPAR2_R1 R1
 #define INPAR3_R2 R2
 #define INPAR1_R4 R4
 #define INPAR2_R5 R5
 #define INPAR3_R6 R6
 #define returnValue_R0 R0

 
 #define baseAddress_P0 P0
 #define waterLevel_R7 R7
 #define ninety_R0 R0
 
 
 #define waterFlowOffset 7 //Because waterInFlowRegister is offset 7 bits from base address
 
 .section program;
 .global _MyWaterControlCode_ASM_SM;
 
 _MyWaterControlCode_ASM_SM:
 
 	//Saving parameters into non-volatile registers
 	[--SP] = R4;						// extern "C" bool WaterControlCode_ASM_SM(
 	INPAR1_R4 = INPAR1_R0;				// COFFEEPOT_DEVICE *coffeePot_BaseAddress,
 										// 		^ this is passed into the function as R0, which 
 										//		  is a volatile register. Since this is not a leaf
 										//		  function, we must save the parameters. 
 	
 	[--SP] = R5;						// unsigned short int waterLevelRequired, 
 	INPAR2_R5 = INPAR2_R1;				//		^ this is passed into the function as R1,
 										// 		  and it must be saved into a non-volatile register.
 										
 	[--SP] = R6;						// unsigned short int tenPercent)
 	INPAR3_R6 = INPAR3_R2;		
 	
 	[--SP] = R7;						// Used for waterLevel_R7
 						
 	LINK 20;
 	
 	R0 = INPAR1_R4;
 	.extern __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE		
 		CALL __Z21CurrentWaterLevel_CPPP16COFFEEPOT_DEVICE;		// unsigned int currentLevel = CurrentWaterLevel(coffeePot_BaseAddress);
 																// 					^ will be stored in R0
 	waterLevel_R7 = returnValue_R0;								// Saving the value of R0, since another function will be called																					
						
	ninety_R0 = INPAR2_R5 - INPAR3_R6;					// //Computing 90% of water level required
	
	CC = waterLevel_R7 < ninety_R0; 				
														// if
														// 		 (currentLevel < (waterLevelRequired - tenPercent))
															
	IF !CC JUMP ELSE;									// {					
	baseAddress_P0 = INPAR1_R4;							// 	 coffeePot_BaseAddress->waterInFlowRegister = 100;
	R2 = INPAR3_R6;//100; 											
	B[baseAddress_P0 + waterFlowOffset] = R2;

	JUMP ENDFUNCTION;
														// } //end if
	
ELSE:		
 				
 	baseAddress_P0 = INPAR1_R4;							// 	coffeePot_BaseAddress->waterInFlowRegister = 0;
	R2 = 0; 											//  SAVING 0 INTO A VOLATILE REGISTER
	B[baseAddress_P0 + waterFlowOffset] = R2;		
					
ENDFUNCTION:
																													
 _MyWaterControlCode_ASM_SM.END:
 UNLINK;
 
//Recover registers saved on stack
R7 = [SP++];
R6 = [SP++];
R5 = [SP++];
R4 = [SP++];

RTS;
 
 