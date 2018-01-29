/*
 * SetEVT_CPP.asm
 *
 *  Created on: Nov 25, 2017
 *      Author: aidan
 */

#include <blackfin.h>

.section L1_data;

#define EVT6 0xFFE02018

.section program
.global _setISR_EVT_CPP

_setISR_EVT_CPP:

	P0.L = lo(EVT6);
	P0.H = hi(EVT6);
	
	.extern _ISR
	R0.L = lo(_ISR);
	R0.H = hi(_ISR);
	
	[P0] = R0;
	
	ssync;  

_setISR_EVT_CPP.END:
	RTS;


