/*
 * Interruptions.h
 *
 *  Created on: 6 nov. 2018
 *      Author: migue
 */
/********************************************************************************
* File:             Interruptions.h
* Owner:            Eduardo Cruz, Jorge Peña, Miguel Sanchez
* Version:          1.1
* Date:             Nov-06-2018
* Classification:   Window Lifter Information
* Brief:            Interruptions, internal and external
********************************************************************************/

#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "s32_core_cm4.h"
#include "Movement.h"
#include "Definitions.h"

#ifndef INTERRUPTIONS_H_
#define INTERRUPTIONS_H_

void LPIT0_Ch0_IRQHandler (__IO uint32_t );
void PORTC_IRQHandler(void);

#endif /* INTERRUPTIONS */
