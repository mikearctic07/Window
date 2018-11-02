/*
 * header.h
 *
 *  Created on: 1 nov. 2018
 *      Author: migue
 */
/********************************************************************************
* File:             header.h
* Owner:            Eduardo Cruz, Jorge Peña, Miguel Sanchez
* Version:          1.0
* Date:             Nov-01-2018
* Classification:   Window Lifter Information
* Brief:            Functions Used in Window Lifter Project Part 1
********************************************************************************/
#ifndef HEADER_H_
#define HEADER_H_

void SOSC_init_8MHz(void);
void SPLL_init_160MHz(void);
void clock_setup_80MHz(void);
void WDOG_disable (void);
void init_GPIO(void);
void LPIT0_Ch0_IRQHandler (__IO uint32_t );
void PORTC_IRQHandler(void);
void PORTA_IRQHandler(void);
void RegisterUp(__IO uint32_t);
void RegisterDown(__IO uint32_t);
void UpMovement(void);
void DownMovement(void);
void UpTransition(__IO uint32_t);
void DownTransition(__IO uint32_t);

#endif /* HEADER_H_ */
