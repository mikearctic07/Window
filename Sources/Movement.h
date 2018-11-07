/*
 * Movement.h
 *
 *  Created on:  6 nov. 2018
 *      Author: alex
 */
/********************************************************************************
* File:             Movement.h
* Owner:            Eduardo Cruz, Jorge Peña, Miguel Sanchez
* Version:          1.1
* Date:             Nov-06-2018
* Classification:   Window Lifter Information
* Brief:            Implement Algorithm to up and down.
********************************************************************************/

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "s32_core_cm4.h"
#include "Definitions.h"
#include "Clocks.h"

#ifndef MOVEMENT_H_
#define MOVEMENT_H_


uint32_t MOVEMENT_Breaking_Bits(uint32_t currentLedStateBreaking);
void MOVEMENT_Up_Movement(void);
void MOVEMENT_Down_Movement(void);
void MOVEMENT_Up_Transition(uint32_t counter);
void MOVEMENT_Down_Transition(uint32_t counter);

#endif /* MOVEMENT_H_ */
