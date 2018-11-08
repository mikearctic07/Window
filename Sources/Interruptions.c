/*
 * Interruptions.c
 *
 *  Created on: 7 nov. 2018
 *      Author: alex
 */

/* ******************************************************************************
 * Includes
****************************************************************************** */
#include "Interruptions.h"

volatile uint32_t *vectorInterruption;
volatile uint32_t currentLedState;

/*******************************************************************************
Function: LPIT0_Ch0_IRQHandler
Notes   : Handler function for LPIT0 timer channel Interrupt
        : Timer with milliseconds option as a parameter
        :
*******************************************************************************/
void LPIT0_Ch0_IRQHandler (uint32_t MILIS)
  {
	PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6); /*Clock Src = 6 (SPLL2_DIV_CLK)*/
	PCC->PCCn[PCC_LPIT_INDEX] |=PCC_PCCn_CGC_MASK; /*Enable clk to LPIT0 regs*/
	LPIT0->MCR=0x00000001; /* Enables the module*/
	LPIT0->MIER =0x0000001; /* Enables the Interrupt for LPIT0*/
	LPIT0->TMR[0].TVAL = MILIS*40000; /*Channel 0 Timeout period: 40 M clocks*/
	LPIT0->TMR[0].TCTRL = 0x00000001; /*T_EN=1  : Timer channel is enabled*/
	while(0 == (LPIT0->MSR & LPIT_MSR_TIF0_MASK)); /*Waits until the flag of LPIT is asserted*/
	LPIT0->MSR |= LPIT_MSR_TIF0_MASK; /* Clears the LPIT0 interrupt Flag*/
	LPIT0->TMR[0].TCTRL = 0x00000000;/*T_EN=0  : Timer channel is disabled*/
  }


/*******************************************************************************
Function: PORTC_IRQHandler
Notes   : Handler function for Port C interrupts
        : Controls if the LED bar has to go one bit UP or DOWN
        : Checks for the current Interrupt to be executed
*******************************************************************************/
void PORTC_IRQHandler(void)
{
	uint32_t counter=0; /* counter variable is initialized 0*/
	vectorInterruption=(uint32_t *)&PORTC->ISFR;  /*ISF register is stored in global variable*/

	if(*vectorInterruption == ANTIPINCH_INTERRUPTION) /* Checks for interrupt generated by the AntiPinch Button*/
	{
		while((currentLedState>0)) /*while the LED bar has leds "ON", DownTransition will turn them off*/
		{
			MOVEMENT_Down_Transition(counter);
			counter++;
		}
		LPIT0_Ch0_IRQHandler (FIVE_SECONDS);  /*LPIT0 is initialized with timeout value = 5000 milliseconds (5 seconds)*/
		PORTC->PCR[PTC8] |= CLEAR_INTERRUPTION_FLAG;     /*LPIT0 ISF Flag is cleared*/
	}
	else if(*vectorInterruption==UP_INTERRUPTION)  /*Checks if the interrupt is generated by SW2 (PTC12)*/
	{
		PORTC->PCR[PTC12] |= CLEAR_INTERRUPTION_FLAG;       /*Clears flag on bit [24] of PCR register of pin 12 (SW2)*/
		while((PTC->PDIR & (1<<PTC12)) && (*vectorInterruption ==0 )) /*Checks if the SW2 is being pressed and the ISFR register is 0 (empty)*/
		{
			MOVEMENT_Up_Transition(counter);		  /*LEDS will be turned on every 400 milliseconds while the SW2 is pressed*/
			counter++;

		}
		if((counter<TIME_AUTOMATIC_MODE) && (counter>1))    /*if pressed time is more than 10mS and less than 500mS LEDs will turn on Automatically*/
		{								  /*leds will turn on Automatically*/
			while((currentLedState<FIRST_10_BITS) && (*vectorInterruption ==0 ))  /*Checks if Antipinch flag has not been raised*/
			{
				MOVEMENT_Up_Transition(counter); /*Until all LED's are ON, UpTransition will turn them on one by one*/
				counter++;
			}
		}

	}
	else								       /*Checks for pin 13 on Port C has generated the interrupt*/
	{
		PORTC->PCR[PTC13] |= CLEAR_INTERRUPTION_FLAG;        /*Clears PTC13 ISFR flag*/
		while((PTC->PDIR & (1<<PTC13)))     /*checks if pin13 Port C (SW3) is being pressed*/
		{
			MOVEMENT_Down_Transition(counter);       /*LEDS's are being turned off one by one*/
			counter++;
		}
		if((counter<TIME_AUTOMATIC_MODE) && (counter>1))
		{
			while((currentLedState>0) && (*vectorInterruption ==0 )) /*if pressed time exceed 500mS and less than 10mS*/
			{												 /*LEDS are turned on Automatically*/
				MOVEMENT_Down_Transition(counter);
				counter++;
			}
		}
	}
}

void INTERRUPTIONS_Init_PORTC(void)
{
    INT_SYS_EnableIRQ(PORTC_IRQn);  /*Enable desired interrupts on PORT C*/
}
