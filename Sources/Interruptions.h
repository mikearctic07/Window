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
#ifndef HEADER_H_
#define HEADER_H_

void LPIT0_Ch0_IRQHandler (__IO uint32_t );
void PORTC_IRQHandler(void);

#endif /* HEADER_H_ */
