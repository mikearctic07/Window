/*
 * GPIO.c
 *
 *  Created on: 1 nov. 2018
 *      Author: migue
 */

/* ******************************************************************************
 * Includes
****************************************************************************** */
#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "s32_core_cm4.h"
#include "GPIO.h"

#define PTD0 0
#define PTD15 15
#define PTD16 16
#define PTC12 12
#define PTC13 13
#define PTC8 8
#define OUTPUT_LEDS 0xF3F
#define FIRST_5_BITS 0x3F
#define FIRST_10_BITS 0x3FF
#define GPIO_ACTIVE 0x00000100
__IO uint32_t IteratorPinsB;

/*******************************************************************************
Function: init_GPIO
Notes   : Initializes clks for Ports: A,B,C and D, GPIOS and Interrupt functionalities
        : for each pin selected as Input or Output
        :
*******************************************************************************/
void init_GPIO(void)
{
	PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT C*/
	PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT D*/
	PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT B*/
	PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT A*/

	PTC->PDDR &= ~(1<<PTC12);     /*Port C12: Data Direction = input (default) */
	PORTC->PCR[12] = 0x00098110;  /*Port C12: MUX=GPIO, ISF flag on rising-edge*/

	PTC->PDDR &= ~(1<<PTC13);     /*Port C12: Data Direction = input */
	PORTC->PCR[13] = 0x00098110;  /*Port C13: MUX=GPIO, ISF flag on rising-edge*/

	/*PTB6 and PTB7 are not used because they're reserved for external oscillator*/
	PTB->PDDR |= OUTPUT_LEDS; /*Port D: Mask of bits configured as outputs*/
	for(IteratorPinsB=0;IteratorPinsB<=5;IteratorPinsB++)
	{
		PORTB->PCR[IteratorPinsB] = GPIO_ACTIVE; /*Port B pins 0 to 5, MUX = GPIO*/
	}

	for(IteratorPinsB=8;IteratorPinsB<=11;IteratorPinsB++)
	{
		PORTB->PCR[IteratorPinsB] = GPIO_ACTIVE;  /*Port B pins 0 to 5, MUX = GPIO*/
	}

	PTD->PDDR |= 1<<PTD0;        /*Port D0: Data Direction= output*/
	PORTD->PCR[0] = GPIO_ACTIVE; /*Port D0: MUX = GPIO*/

	PTD->PDDR |= 1<<PTD15;       /*Port D15: Data Direction= output*/
	PORTD->PCR[15] = GPIO_ACTIVE;/*Port D15: MUX = GPIO*/

	PTD->PDDR |= 1<<PTD16;       /*Port D16: Data Direction= output*/
	PORTD->PCR[16] = GPIO_ACTIVE;/*Port D16: MUX = GPIO*/

	PTC->PDDR &= ~(1<<PTC8);     /*Port C8: Data Direction = input*/
	PORTC->PCR[8] = 0x00090112;  /*Port C8: MUX= GPIO, ISF on rising edge*/
}
