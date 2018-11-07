/*
 * functions.c
 *
 *  Created on: 1 nov. 2018
 *      Author: migue
 */

/* ******************************************************************************
 * Includes
****************************************************************************** */
#include "Movement.h"

__IO uint32_t InterruptRegister;
__IO uint32_t CurrentRegister;
__IO uint32_t AntiPinch;

/*******************************************************************************
Function: RegisterUp
Notes   : Checks if the current register has to be updated (if one bit has to be set for Up Movement)
        :
        :
*******************************************************************************/
void RegisterUp(__IO uint32_t CurrentRegisterUp)
{
    __IO uint32_t RealBits;               /*this variable will store new value for the LED bar*/
                                          /*In order to not use PB6 and PB7*/
    if(CurrentRegisterUp>FIRST_5_BITS)    /*Checks if bit 6 or higher has to be set, shifts 2 bits and add 3 in order to use only*/
    {								      /*bits [0-5] and [8-11] */
    	RealBits=(CurrentRegisterUp<<2)+3;
    	RealBits=RealBits&OUTPUT_LEDS;
    }
    else
    {
    	RealBits=CurrentRegisterUp;       /*if bit 6 must not be set yet, the current register remains the same*/
    }

    PTB-> PCOR |= RealBits;               /*Clear LED's on Current register (LEDS on)*/
}

/*******************************************************************************
Function:
Notes   : Checks if the current register has to be updated (if one bit has to be cleared for Down Movement)
        :
        :
*******************************************************************************/
void RegisterDown(__IO uint32_t CurrentRegisterDown)
{
	__IO uint32_t RealBits;
	if(CurrentRegisterDown>FIRST_5_BITS)       /*Checks if bit 6 or higher has to be clear, shifts-left 2 bits and add 3 in order to use only*/
		{								       /*bits [0-5] and [8-11] */
			RealBits=(CurrentRegisterDown<<2)+3;
			RealBits=RealBits&OUTPUT_LEDS;
		}
	else
		{
			RealBits=CurrentRegisterDown;      /*if bit 6 must not be cleared yet, the current register remains the same*/
		}

	PTB-> PSOR = ~RealBits;                    /*Set LEDs on Current register (LEDS OFF)*/
}

/*******************************************************************************
Function: UpMovement
Notes   : Generates the current register of LED bar if one bit has to be incremented
        :
        :
*******************************************************************************/
void UpMovement(void)
{
	CurrentRegister=(CurrentRegister<<1)+1;        /*adds the next bit to be turned on*/
	CurrentRegister=CurrentRegister&FIRST_10_BITS; /*Current register is prepared with the MASK*/
	RegisterUp(CurrentRegister);                   /*New current register is created while avoiding bits [0-5] and [8-11] */
}


/*******************************************************************************
Function: DownMovement
Notes   : Generates the current register of LED bar if one bit has to be decremented
        :
        :
*******************************************************************************/
void DownMovement(void)
{
	CurrentRegister=CurrentRegister>>1;            /*takes the next bit to be turned off*/
	RegisterDown(CurrentRegister);                 /*New current register is created while avoiding bits [0-5] and [8-11] */
}

/*******************************************************************************
Function: UpTransition
Notes   : Generates  a valid "Up" transition (more than 10 mS and increments every 400 mS)
        :
        :
*******************************************************************************/
void UpTransition(__IO uint32_t counter)
{
	PTD->PTOR |=(1<<16);      /*Toggles Green LED while the LED bar increments*/
    LPIT0_Ch0_IRQHandler(10);  /*LPIT0 timer is initialized with timeout = 10ms*/
    PTD->PTOR |=(1<<16);      /*Toggles Green LED while the LED bar increments*/

    if ((counter>=1) && (counter%40 ==0)) /* if 40 X 10ms = 400ms, checks for valid time and increments one led every 400ms*/
    {
 	   UpMovement();
    }
}



/*******************************************************************************
Function: DownTransition
Notes   : Generates  a valid "Down" transition (more than 10 mS and increments every 400 mS)
        :
        :
*******************************************************************************/
void 
DownTransition(__IO uint32_t counter)
{
	PTD->PTOR |=(1<<0);        /*Toggles Blue LED while the LED bar increments*/
    LPIT0_Ch0_IRQHandler(10);  /*LPIT0 timer is initialized with timeout = 10ms*/
    PTD->PTOR |=(1<<0);        /*Toggles Blue LED while the LED bar increments*/

    if ((counter>=1) && (counter%40 ==0)) /* if 40 X 10ms = 400ms, checks for valid time and decrements one led every 400ms*/
    {
 	   DownMovement();
    }
}

