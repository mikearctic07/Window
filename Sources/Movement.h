/*
 * ButtonsLogic.h
 *
 *  Created on:  6 nov. 2018
 *      Author: migue
 */
/********************************************************************************
* File:             ButtonsLogic.h
* Owner:            Eduardo Cruz, Jorge Peña, Miguel Sanchez
* Version:          1.1
* Date:             Nov-06-2018
* Classification:   Window Lifter Information
* Brief:            Implement Algorithm to up and down.
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

void RegisterUp(__IO uint32_t);
void RegisterDown(__IO uint32_t);
void UpMovement(void);
void DownMovement(void);
void UpTransition(__IO uint32_t);
void DownTransition(__IO uint32_t);

#endif /* HEADER_H_ */
