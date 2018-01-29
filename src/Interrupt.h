/*
 * Interrupt.h
 *
 *  Created on: Nov 23, 2017
 *      Author: aidan
 */

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

//For CPP interrupt control
extern "C" void ISR();
void setUpCoreTimer();
void setUpIMask();
void setUpSIC_IMask();
extern "C" void setISR_EVT_CPP();
void activateTimer();


//For ASM interrupt control
extern "C" void ISR_ASM();
extern "C" void setISR_EVT_ASM();


#endif /* INTERRUPT_H_ */
