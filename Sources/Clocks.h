/*
 * Clocks.h
 *
 *  Created on: 6 nov. 2018
 *      Author: migue
 */
/********************************************************************************
* File:             header.h
* Owner:            Eduardo Cruz, Jorge Peña, Miguel Sanchez
* Version:          1.1
* Date:             Nov-06-2018
* Classification:   Window Lifter Information
* Brief:            Clock Functions
********************************************************************************/

#include "S32K144.h" 
#include "s32_core_cm4.h"
#include "Definitions.h"

#ifndef CLOCKS_H_
#define CLOCKS_H_

void CLOCKS_SOSC_init_8MHz(void);
void CLOCKS_SPLL_init_160MHz(void);
void CLOCKS_Clock_setup_80MHz(void);
void CLOCKS_WDOG_disable (void);
void CLOCKS_Init(void);

#endif /* CLOCKS_H_ */
