/*
 * SetEVT_ASM.asm
 *
 *  Created on: Nov 26, 2017
 *      Author: aidan
 */

#include <blackfin.h>

.section L1_data;

#define EVT6 0xFFE02018

.section program
.global _setISR_EVT_ASM

_setISR_EVT_ASM:

	P0.L = lo(EVT6);
	P0.H = hi(EVT6);
	
	.extern _ISR
	R0.L = lo(_ISR_ASM);
	R0.H = hi(_ISR_ASM);
	
	[P0] = R0;
	
	ssync;  

_setISR_EVT_ASM.END:
	RTS;





