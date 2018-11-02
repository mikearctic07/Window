/* ###################################################################
**     Filename    : main.c
**     Processor   : S32K14x
**     Abstract    :
**         Main module.
**         This module contains user's application code.
**     Settings    :
**     Contents    :
**         No public methods
**
** ###################################################################*/
/*!
** @file main.c
** @version 01.00
** @brief
**         Main module.
**         This module contains user's application code.
*/
/*!
**  @addtogroup main_module main module documentation
**  @{
*/
/* MODULE main */


/* Including necessary module. Cpu.h contains other modules needed for compiling.*/
#include "Cpu.h"
#include "S32k144.h"
#include "header.h"

  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */
#define PTD0 0    /*  Port PTD0, bit 0: output to blue LED*/
#define PTD15 15  /*  Port PTD15, bit 15: output to red LED*/
#define PTD16 16  /*  Port PTD16, bit 16: output to green LED*/
#define PTC12 12  /*  Port PTC12, bit 12: input [SW2]*/
#define PTC13 13  /*  Port PTC13, bit 12: input [SW3]*/
#define PTC8 8    /*  Port PTC12, bit 12: external push button input [SW3]*/
#define OUTPUT_LEDS 0xF3F    	/* Port B, Mask for designed output pins on for Red LED Bar*/
#define FIRST_5_BITS 0x3F    	/* Port B, First five bits for Red LED bar */
#define FIRST_10_BITS 0x3FF  	/* Port B, First ten bits for Red LED bar*/
#define GPIO_ACTIVE 0x00000100 	/*Port B, Mask for the desired outputs on port B*/

int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/
  /* Write your code here */

    SOSC_init_8MHz(); 		/*Initialize system oscillator for 8 MHz xtal*/
    SPLL_init_160MHz();  	/*Initialize SPLL to 160 MHz with 8 MHz SOSC*/
    clock_setup_80MHz(); 	/*Initialize clocks: 80MHz sysclk & core, 40MHz bus, 20MHz flash*/
    WDOG_disable();  		/*Disables the watch dog timer*/
    init_GPIO();  			/*Initialize the GPIO pins---Inputs---Outputs----Interrupt Buttons---*/
    PINS_DRV_SetPins(PTD,(1<<0|1<<15|1<<16)); /*Set LEDs: BLUE, RED and GREEN (LEDS OFF)*/
    PTB-> PSOR |= OUTPUT_LEDS; 		/*Set the Red Led Bar pins off */
    INT_SYS_EnableIRQ(PORTC_IRQn);  /*Enable desired interrupts on PORT C*/
    INT_SYS_EnableIRQ(PORTA_IRQn);  /*Enable desired interrupts on PORT A*/

  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;) {
    if(exit_code != 0) {
      break;
    }
  }
  return exit_code;
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.1 [05.21]
**     for the Freescale S32K series of microcontrollers.
**
** ###################################################################
*/
