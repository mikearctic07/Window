/*
 * Movement.h
 *
 *  Created on:  6 nov. 2018
 *      Author: migue
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

void RegisterUp(__IO uint32_t);
void RegisterDown(__IO uint32_t);
void UpMovement(void);
void DownMovement(void);
void UpTransition(__IO uint32_t);
void DownTransition(__IO uint32_t);

#endif /* MOVEMENT_H_ */
