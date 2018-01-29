/*
 * My_HeaterControlCode_ASM_SM.asm
 *
 *  Created on: Oct 30, 2017
 *      Author: aidan
 */

 
#include "My_CoffeePot_2016main.h"
#include <blackfin.h>
 
 .section L1_data;
 
 
 #define INPAR1_R0 R0
 #define INPAR2_R1 R1
 #define INPAR3_R2 R2
 #define INPAR1_R4 R4
 #define INPAR2_R5 R5
 #define INPAR3_R6 R6
 #define returnValue_R0 R0

 
 #define baseAddress_P0 P0
 #define waterTemp_R7 R7
 #define ninety_R0 R0
 
 
 #define heaterOffset 6 		//Because heaterRegister is offset 6 bits from base address
 #define heaterBoostOffset 8 	//Because heaterBoostregister is offset 8 bits from base address
 
 .section program;
 .global _MyHeaterControlCode_ASM_SM;
 
 _MyHeaterControlCode_ASM_SM:
 
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
 	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE		
 		CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;		// unsigned int currentTemp = CurrentWaterLevel(coffeePot_BaseAddress);
 																// 					^ will be stored in R0
 	waterTemp_R7 = returnValue_R0;								// Saving the value of R0, since another function will be called																					
						
	ninety_R0 = INPAR2_R5 - INPAR3_R6;					// //Computing 90% of water temperature required
	
	CC = waterTemp_R7 < ninety_R0; 				
														// if
														// 		 (currentTemp < (waterTemperatureRequired - tenPercent))
															
	IF !CC JUMP ELSE;									// {					
	baseAddress_P0 = INPAR1_R4;							// 	 coffeePot_BaseAddress->heaterRegister = 100;
	R2 = 100; 											
	B[baseAddress_P0 + heaterOffset] = R2;
	
	baseAddress_P0 = INPAR1_R4;							// 	 coffeePot_BaseAddress->heaterBoostRegister = 15;
	R2 = 15; 											
	B[baseAddress_P0 + heaterBoostOffset] = R2;
	
	JUMP ENDFUNCTION;
														// } //end if
	
ELSE:		
 				
 	baseAddress_P0 = INPAR1_R4;							// 	coffeePot_BaseAddress->heaterRegister = 0;
	R2 = 0; 											//  SAVING 0 INTO A VOLATILE REGISTER
	B[baseAddress_P0 + heaterOffset] = R2;	
	B[baseAddress_P0 + heaterBoostOffset] = R2;			//  coffeePot_BaseAddress->heaterBoostRegister = 0;
					
ENDFUNCTION:
																													
 _MyHeaterControlCode_ASM_SM.END:						// } //end of function
 UNLINK;
 
//Recover registers saved on stack
R7 = [SP++];
R6 = [SP++];
R5 = [SP++];
R4 = [SP++];

RTS;
 
 