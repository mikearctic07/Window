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

/*PORT B MACROS*/
#define PTB0 									0
#define PTB1 									1
#define PTB2 									2
#define PTB3 									3
#define PTB4 									4
#define PTB5 									5
#define PTB8 									8
#define PTB9 									9
#define PTB10 									10
#define PTB11 									11

/*PORT C MACROS*/
#define PTC8 									8
#define PTC12 									12  /*  Port PTC12, bit 12: input [SW2], button UP*/
#define PTC13 									13  /*  Port PTC13, bit 12: input [SW3], button Down*/

/*PORT D MACROS*/
#define LED_BLUE 								0    /*  Port PTD0, bit 0: output to blue LED*/
#define LED_RED 								15  /*  Port PTD15, bit 15: output to red LED*/
#define LED_GREEN 								16  /*  Port PTD16, bit 16: output to green LED*/

/*LED RED BAR MACROS*/
#define OUTPUT_LEDS 							0xF3F    	/* Port B, Mask for designed output pins on for Red LED Bar*/
#define FIRST_5_BITS 							0x3F    	/* Port B, First five bits for Red LED bar */
#define FIRST_10_BITS							0x3FF  	/* Port B, First ten bits for Red LED bar*/
#define GPIO_ACTIVE_MASK 						0x00000100 /*Port B, Mask for the desired outputs on port B*/
#define GPIO_ISF_RISING_EDGE_MASK 				0x00090000
#define GPIO_LK_REGISTER_MASK     				0x00008000
#define GPIO_PASSIVE_FILTER_EN    				0x00000010
#define GPIO_INPUT_PULLDOWN_R_EN  				0x00000002



#define ANTIPINCH_INTERRUPTION 					0x00000100	/*PTC8*/
#define UP_INTERRUPTION 						0x000001000			/*PTC12, up button*/
#define CLEAR_INTERRUPTION_FLAG 				0x1000000	/*1<<24 it clears the interruption flag*/
#define FIVE_SECONDS 							5000					/*Waiting time after Antipinch, 5000 ms*/
#define TIME_AUTOMATIC_MODE 					50				/*A timer of 10ms is used, so 50x10=500ms */

#endif /* DEFINITIONS_H_ */
