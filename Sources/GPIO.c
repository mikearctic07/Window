/*
 * GPIO.c
 *
 *  Created on: 1 nov. 2018
 *      Author: migue
 */


#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "s32_core_cm4.h"
#include "GPIO.h"

/*******************************************************************************
Function: init_GPIO
Notes   : Initializes clks for Ports: A,B,C and D, GPIOS and Interrupt functionalities
        : for each pin selected as Input or Output
        :
*******************************************************************************/
void GPIO_Init(void)
{
    PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT C*/
    PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT D*/
    PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT B*/
    PCC-> PCCn[PCC_PORTA_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT A*/

    PTC->PDDR &= ~(1<<PTC12);     /*Port C12: Data Direction = input (default) */
    PORTC->PCR[PTC12] |= (GPIO_ACTIVE_MASK|GPIO_ISF_RISING_EDGE_MASK
					 |GPIO_LK_REGISTER_MASK|GPIO_PASSIVE_FILTER_EN);  /*Port C12: MUX=GPIO, ISF flag on rising-edge*/

    PTC->PDDR &= ~(1<<PTC13);     /*Port C12: Data Direction = input */
    PORTC->PCR[PTC13] |= (GPIO_ACTIVE_MASK|GPIO_ISF_RISING_EDGE_MASK
    				 |GPIO_LK_REGISTER_MASK|GPIO_PASSIVE_FILTER_EN);  /*Port C13: MUX=GPIO, ISF flag on rising-edge*/

    /*PTB6 and PTB7 are not used because they're reserved for external oscillator*/
    PTB->PDDR |= OUTPUT_LEDS; /*Port D: Mask of bits configured as outputs*/

    PORTB->PCR[PTB0] = GPIO_ACTIVE_MASK; /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB1] = GPIO_ACTIVE_MASK; /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB2] = GPIO_ACTIVE_MASK; /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB3] = GPIO_ACTIVE_MASK; /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB4] = GPIO_ACTIVE_MASK; /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB5] = GPIO_ACTIVE_MASK; /*Port B pins 0 to 5, MUX = GPIO*/

    PORTB->PCR[PTB8] = GPIO_ACTIVE_MASK;  /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB9] = GPIO_ACTIVE_MASK;  /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB10] = GPIO_ACTIVE_MASK;  /*Port B pins 0 to 5, MUX = GPIO*/
    PORTB->PCR[PTB11] = GPIO_ACTIVE_MASK;  /*Port B pins 0 to 5, MUX = GPIO*/


    PTD->PDDR |= 1<<LED_BLUE;        /*Port D0: Data Direction= output*/
    PORTD->PCR[LED_BLUE] = GPIO_ACTIVE_MASK; /*Port D0: MUX = GPIO*/

    PTD->PDDR |= 1<<LED_RED;       /*Port D15: Data Direction= output*/
    PORTD->PCR[LED_RED] = GPIO_ACTIVE_MASK;/*Port D15: MUX = GPIO*/

    PTD->PDDR |= 1<<LED_GREEN;       /*Port D16: Data Direction= output*/
    PORTD->PCR[LED_GREEN] = GPIO_ACTIVE_MASK;/*Port D16: MUX = GPIO*/

    PTC->PDDR &= ~(1<<PTC8);     /*Port C8: Data Direction = input*/
    PORTC->PCR[PTC8] |= (GPIO_ACTIVE_MASK|GPIO_ISF_RISING_EDGE_MASK
    				|GPIO_LK_REGISTER_MASK|GPIO_PASSIVE_FILTER_EN
					|GPIO_INPUT_PULLDOWN_R_EN);  /*Port C8: MUX= GPIO, ISF on rising edge*/

    PTD-> PSOR |= (1<<LED_BLUE|1<<LED_RED|1<<LED_GREEN);  /*Set the LEDS RED, BLUE off */
    PTB-> PSOR |= OUTPUT_LEDS; 		/*Set the Red Led Bar pins off */
}
