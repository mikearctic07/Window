/*
 * Movement.c
 *
 *  Created on: 1 nov. 2018
 *      Author: alex
 */

/* ******************************************************************************
 * Includes
****************************************************************************** */
#include "Movement.h"

volatile uint32_t currentLedState;
static uint32_t updatedLedState;

/*******************************************************************************
Function:
Notes   : Checks if the current register has to be updated
        :
        :
*******************************************************************************/
uint32_t MOVEMENT_Breaking_Bits(uint32_t currentLedStateBreaking)
{
    uint32_t outputLeds;
    if(currentLedStateBreaking>FIRST_5_BITS) /*Checks if bit 6 or higher has to be clear, shifts-left 2 bits and add 3 in order to use only*/
        {                                      /*bits [0-5] and [8-11] */
            outputLeds=(currentLedStateBreaking<<2)+3;
            outputLeds=outputLeds&OUTPUT_LEDS;
        }
    else
        {
            outputLeds=currentLedStateBreaking;      /*if bit 6 must not be cleared yet, the current register remains the same*/
        }
    return outputLeds;
}


/*******************************************************************************
Function: UpMovement
Notes   : Generates the current register of LED bar if one bit has to be incremented
        :
        :
*******************************************************************************/
void MOVEMENT_Up_Movement(void)
{
	currentLedState=(currentLedState<<1)+1;        /*adds the next bit to be turned on*/
	currentLedState=currentLedState&FIRST_10_BITS; /*Current Led State is prepared with the MASK*/
	updatedLedState=MOVEMENT_Breaking_Bits(currentLedState);
    PTB-> PCOR |= updatedLedState; /*Turn On Leds*/
}


/*******************************************************************************
Function: DownMovement
Notes   : Generates the current register of LED bar if one bit has to be decremented
        :
        :
*******************************************************************************/
void MOVEMENT_Down_Movement(void)
{
	currentLedState=currentLedState>>1;            /*takes the next bit to be turned off*/
	updatedLedState=MOVEMENT_Breaking_Bits(currentLedState);
    PTB-> PSOR = ~updatedLedState; /*Turn Off Leds*/
}

/*******************************************************************************
Function: UpTransition
Notes   : Generates  a valid "Up" transition (more than 10 mS and increments every 400 mS)
        :
        :
*******************************************************************************/
void MOVEMENT_Up_Transition(uint32_t counter)
{
	PTD->PTOR |=(1<<LED_BLUE);      /*Toggles Green LED while the LED bar increments*/
    LPIT0_Ch0_IRQHandler(10);  /*LPIT0 timer is initialized with timeout = 10ms*/
    PTD->PTOR |=(1<<LED_BLUE);      /*Toggles Green LED while the LED bar increments*/

    if ((counter>=1) && (counter%40 ==0)) /* if 40 X 10ms = 400ms, checks for valid time and increments one led every 400ms*/
    {
 	   MOVEMENT_Up_Movement();
    }
}

/*******************************************************************************
Function: DownTransition
Notes   : Generates  a valid "Down" transition (more than 10 mS and increments every 400 mS)
        :
        :
*******************************************************************************/
void MOVEMENT_Down_Transition(uint32_t counter)
{
	PTD->PTOR |=(1<<LED_GREEN);        /*Toggles Blue LED while the LED bar increments*/
    LPIT0_Ch0_IRQHandler(10);  /*LPIT0 timer is initialized with timeout = 10ms*/
    PTD->PTOR |=(1<<LED_GREEN);        /*Toggles Blue LED while the LED bar increments*/

    if ((counter>=1) && (counter%40 ==0)) /* if 40 X 10ms = 400ms, checks for valid time and decrements one led every 400ms*/
    {
 	   MOVEMENT_Down_Movement();
    }
}

