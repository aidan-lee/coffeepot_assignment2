/*
 * My_HeaterCode_ASM.asm
 *
 *  Created on: Oct 23, 2017
 *      Author: aidan
 */

//#include "My_CoffeePotFunctions_forASM.h"

#include "My_CoffeePot_2016main.h"
#include <blackfin.h>
 
 //#define LED_WATERPOWER LED4
 //#define LED_LEDPOWER LED3
 
 
 .section L1_data;
 
 
 #define INPAR1_R0 R0
 #define INPAR2_R1 R1
 #define INPAR1_R4 R4
 #define INPAR2_R5 R5
 #define returnValue_R0 R0

 
 #define baseAddress_P0 P0
 #define waterTemp_R6 R6
 #define counter_R7 R7
 #define ninety_R0 R0
 
 
 #define heaterOffset 6		 	//Because heaterRegister is offset 6 bits from base address
 #define heaterBoostOffset 8	//Because heaterBoostRegister is offset 8 bits from base address
 
 
 .section program;
 .global _MyHeaterControlCode_ASM;
 
 _MyHeaterControlCode_ASM:
 
 	//Saving parameters into non-volatile registers
 	[--SP] = R4;						// extern "C" void MyHeaterCode_ASM(
 	INPAR1_R4 = INPAR1_R0;				// COFFEEPOT_DEVICE *coffeePot_BaseAddress,
 										// 		^ this is passed into the function as R0, which 
 										//		  is a volatile register. Since this is not a leaf
 										//		  function, we must save the parameters. 
 	
 	[--SP] = R5;						// unsigned short int tenPercent)
 	INPAR2_R5 = INPAR2_R1;				//		^ this is passed into the function as R1,
 										// 		  and it must be saved into a non-volatile register.
 										
 	[--SP] = R6;						// Used for waterTemp_R6	
 	
 	[--SP] = R7;						// Used for counter_R7
 						
 	LINK 20;
 	
 	R0 = INPAR1_R4;
 	.extern __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE		
 		CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;	// unsigned int currentTemp = CurrentTemperature(coffeePot_BaseAddress);
 																// 					^ will be stored in R0
 	waterTemp_R6 = returnValue_R0;								// Saving the value of R0, since another function will be called																					
				
	baseAddress_P0 = INPAR1_R4;							// 	coffeePot_BaseAddress->heaterRegister = 200;
	R2 = 200; 											//  SAVING 200 INTO A VOLATILE REGISTER
	B[baseAddress_P0 + heaterOffset] = R2;
			
	R2 = 15;											// coffeePot_BaseAddress->heaterBoostRegister = 15;
	B[baseAddress_P0 + heaterBoostOffset] = R2;	
	
	counter_R7 = 0;
						
WHILE:	
	R0 = 10;
	R0 *= INPAR2_R5;								// 	//Calculating waterTemperatureRequired
														// while
	CC = waterTemp_R6 <= R1;							// 		 (waterTemp_R1 <= waterTemperatureRequired)	
	IF !CC JUMP ENDWHILE;								// EXIT LOOP IF NOT TRUE
														// {
														
	baseAddress_P0 = INPAR1_R4;							// 	coffeePot_BaseAddress->heaterRegister = 200;
	R2 = 200;
	B[baseAddress_P0 + heaterOffset] = R2;
	
	
	R0 = 5;
	CC = counter_R7 == R0;
	IF CC JUMP true;
	
	R0 = 0;
	counter_R7 += 1;										// counter++;
	JUMP SOSP;
	
	true:
	.extern __Z12printNewLinev
		CALL __Z12printNewLinev;
	R0 = 1;
	counter_R7 = 0;
	JUMP SOSP;
	
	SOSP:
	/*
	.extern __Z28My_SimulatedOneSecondPassingb		
 		CALL __Z28My_SimulatedOneSecondPassingb;			//  My_SimulatedOneSecondPassing(true);
 	*/
 	
 	.extern __Z17Assignment2Updatev							// Assignment2Update();
 		CALL __Z17Assignment2Updatev;
 		
 	R0 = INPAR1_R4;	
 	CALL __Z22CurrentTemperature_CPPP16COFFEEPOT_DEVICE;	//  currentTemp = CurrentTemperature_CPP(coffeePot_baseAddress);
	waterTemp_R6 = returnValue_R0;		
	
	R0 = 9;													//	//COMPUTING 90% of RequiredTemperature
	ninety_R0 *= INPAR2_R5;							
	
	CC = ninety_R0 <= waterTemp_R6; 						//  if (currentTemp >= (TemperatureRequired - tenPercent)
	IF CC JUMP ENDWHILE;									//		break;
	
	
	JUMP WHILE;
															// } //end while loop
		
ENDWHILE:		
 				
 				
 	baseAddress_P0 = INPAR1_R4;								// 	coffeePot_BaseAddress->heaterRegister = 0;
	R2 = 0; 												//  SAVING 0 INTO A VOLATILE REGISTER
	B[baseAddress_P0 + heaterOffset] = R2;
	B[baseAddress_P0 + heaterBoostOffset] = R2;					// coffeePot_BaseAddress->heaterBoostRegister = 0;
																												
 _MyHeaterControlCode_ASM.END:
 UNLINK;
 
//Recover registers saved on stack;
R7 = [SP++];
R6 = [SP++];
R5 = [SP++];
R4 = [SP++];

RTS;
 
 