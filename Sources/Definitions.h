/*
 * Definitions.h
 *
 *  Created on:  6 nov. 2018
 *      Author: alex
 */
/********************************************************************************
* File:             Definitions.h
* Owner:            Eduardo Cruz, Jorge Peña, Miguel Sanchez
* Version:          1.1
* Date:             Nov-06-2018
* Classification:   Window Lifter Information
* Brief:            Define Macros
********************************************************************************/
#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define SOSCDIV1_SOSCDIV2_DIV1					0x00000101
#define SOSC_RANGE_1MHZ_8MHZ					0x00000024
#define SOSCCSR_REGISTER_EN 					0x00000001
#define SPLL_DISABLED							0x00000000
#define SPLLDIV1_DIV2_SPLLDIV2_DIV4				0x00000302
#define PREDIV_SOSC_CLK_BY_1					0x00180000
#define SPLLCSR_CAN_BE_WRITTEN_NO_LK			0x00000001
#define SPLL_AS_CLKSOURCE						6
#define WATCH_DOG_COUNTER_MASK 					0xD928C520
#define WD_TIMEOUT_MAX 							0x0000FFFF
#define WD_DISABLE_WATCHDOG						0x00002100

#define PTD0 0    /*  Port PTD0, bit 0: output to blue LED*/
#define PTD15 15  /*  Port PTD15, bit 15: output to red LED*/
#define PTD16 16  /*  Port PTD16, bit 16: output to green LED*/
#define PTC12 12  /*  Port PTC12, bit 12: input [SW2], button UP*/
#define PTC13 13  /*  Port PTC13, bit 12: input [SW3], button Down*/
#define PTC8 8    /*  Port PTC12, bit 12: external push button input [SW3]*/
#define OUTPUT_LEDS 0xF3F    	/* Port B, Mask for designed output pins on for Red LED Bar*/
#define FIRST_5_BITS 0x3F    	/* Port B, First five bits for Red LED bar */
#define FIRST_10_BITS 0x3FF  	/* Port B, First ten bits for Red LED bar*/
#define GPIO_ACTIVE 0x00000100 	/*Port B, Mask for the desired outputs on port B*/
#define ANTIPINCH_INTERRUPTION 0x00000100	/*PTC8*/
#define UP_INTERRUPTION 0x000001000			/*PTC12, up button*/
#define CLEAR_INTERRUPTION_FLAG 0X1000000	/*1<<24 it clears the interruption flag*/
#define FIVE_SECONDS 5000					/*Waiting time after Antipinch, 5000 ms*/
#define TIME_AUTOMATIC_MODE 50				/*A timer of 10ms is used, so 50x10=500ms */

#endif /* DEFINITIONS_H_ */
