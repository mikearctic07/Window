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

  volatile int exit_code = 0;

/* User includes (#include below this line is not maintained by Processor Expert) */
#define PTD0 0
#define PTD15 15
#define PTD16 16
#define PTC12 12
#define PTC13 13
#define OUTPUT_LEDS 0xF3F
#define FIRST_5_BITS 0x3F
#define FIRST_10_BITS 0x3FF
#define GPIO_ACTIVE 0x00000100

__IO uint32_t InterruptRegister;
__IO uint32_t CurrentRegister;
__IO uint32_t IteratorPinsB;

/*!
  \brief The main function for the project.
  \details The startup initialization sequence is the following:
 * - startup asm routine
 * - main()
*/

void RegisterUp(__IO uint32_t CurrentRegisterUp);
void RegisterDown(__IO uint32_t CurrentRegisterDown);
void UpMovement(void);
void DownMovement(void);

void RegisterUp(__IO uint32_t CurrentRegisterUp)
{
    __IO uint32_t RealBits;
    /*In order to not use PB6 and PB7*/
    if(CurrentRegisterUp>FIRST_5_BITS)
    {
    	RealBits=(CurrentRegisterUp<<2)+3;
    	RealBits=RealBits&OUTPUT_LEDS;
    }
    else
    {
    	RealBits=CurrentRegisterUp;
    }

    PTB-> PCOR |= RealBits;
}

void RegisterDown(__IO uint32_t CurrentRegisterDown)
{
    __IO uint32_t RealBits;
    if(CurrentRegisterDown>FIRST_5_BITS)
    {
    	RealBits=(CurrentRegisterDown<<2)+3;
    	RealBits=RealBits&OUTPUT_LEDS;
    }
    else
    {
    	RealBits=CurrentRegisterDown;
    }

    PTB-> PSOR = ~RealBits;
}

void UpMovement(void)
{
	CurrentRegister=(CurrentRegister<<1)+1;
	CurrentRegister=CurrentRegister&FIRST_10_BITS;
	RegisterUp(CurrentRegister);
}

void DownMovement(void)
{
	CurrentRegister=CurrentRegister>>1;
	RegisterDown(CurrentRegister);
}

  void LPIT0_Ch0_IRQHandler (__IO uint32_t MILIS)
      {
      	PCC->PCCn[PCC_LPIT_INDEX] = PCC_PCCn_PCS(6); /*Clock Src = 6 (SPLL2_DIV_CLK)*/
      	PCC->PCCn[PCC_LPIT_INDEX] |=PCC_PCCn_CGC_MASK;
      	LPIT0->MCR=0x00000001;
      	LPIT0->MIER =0x0000001;
      	LPIT0->TMR[0].TVAL = MILIS*40000; /*Chan 0 Timeout period: 40 M clocks*/
      	LPIT0->TMR[0].TCTRL = 0x00000001; /*T_EN=1  : Timer channel is enabled*/
      	while(0 == (LPIT0->MSR & LPIT_MSR_TIF0_MASK));
      	LPIT0->MSR |= LPIT_MSR_TIF0_MASK;
      	LPIT0->TMR[0].TCTRL = 0x00000000;
      }

  void SOSC_init_8MHz(void)
  {
  	 SCG->SOSCDIV=0x00000101; /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
  	 SCG->SOSCCFG=0x00000024; /* Range=2: Medium freq (SOSC between 1MHz-8MHz)*/
  	 while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
  	 SCG->SOSCCSR=0x00000001;
  	 while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
  }



  void SPLL_init_160MHz(void)
  {
  	 while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  	 SCG->SPLLCSR = 0x00000000; /* SPLLEN=0: SPLL is disabled (default) */
  	 SCG->SPLLDIV = 0x00000302; /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
  	 SCG->SPLLCFG = 0x00180000; /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
  	 while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
  	 SCG->SPLLCSR = 0x00000001; /* LK=0: SPLLCSR can be written */
  	 while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */

  }

  void clock_setup_80MHz(void) /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
  {

  	 SCG->RCCR=SCG_RCCR_SCS(6) /* PLL as clock source*/
  	 |SCG_RCCR_DIVCORE(0b01) /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz*/
  	 |SCG_RCCR_DIVBUS(0b01) /* DIVBUS=1, div. by 2: bus clock = 40 MHz*/
  	 |SCG_RCCR_DIVSLOW(0b10); /* DIVSLOW=2, div. by 3: SCG slow, flash clock= 26 2/3 MHz*/
  	 while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}
  }

  void WDOG_disable (void)
      {
      	WDOG->CNT=0xD928C520;
      	WDOG->TOVAL=0x0000FFFF;
      	WDOG->CS = 0x00002100;
      }

  void PORTC_IRQHandler(void)
  {
    __IO uint32_t counter=0;
    
	  InterruptRegister=PORTC->ISFR;
	   if(InterruptRegister==0x00001000)
	   {
		   PORTC->PCR[12] |= (1 << 24);
       while((PTC->PDIR & (1<<PTC12)))

		      		   {
		      		   	   PTD->PTOR |=(1<<16);
		      		   	   LPIT0_Ch0_IRQHandler(10);
		      			   PTD->PTOR |=(1<<16);
		      			   counter++;
		      			 if ((counter>=10) && (counter%40 ==0))
		      			 {
//		      				 PTD->PCOR |=(1<<15);
		      				 UpMovement();
		      			 }

		      		   }
					   if((counter<50) && (counter>1))
					   {
						   while(CurrentRegister<0x3FF)
						   {
							   PTD->PTOR |=(1<<16);
							   LPIT0_Ch0_IRQHandler(10);
							   PTD->PTOR |=(1<<16);
							   counter++;
							   if ((counter>=10) && (counter%40 ==0))
							   		      			 {
							   		      				 UpMovement();
							   		      			 }
						   }
					   }



	   }
	   else
	   {
        PORTC->PCR[13] |= (1 << 24);
        while((PTC->PDIR & (1<<PTC13)))
			   {
        			PTD->PTOR |=(1<<0);
				   LPIT0_Ch0_IRQHandler(10);
				   PTD->PTOR |=(1<<0);
				   counter++;
			   if ((counter>=10) && (counter%40 ==0))
			   		      			 {
				   	   	   	   	   	   DownMovement();
			   		      			 }
			   }
        if((counter<50) && (counter>1))
        					   {
        						   while((CurrentRegister>0))
        						   {
        							   PTD->PTOR |=(1<<0);
        							   LPIT0_Ch0_IRQHandler(10);
        							   PTD->PTOR |=(1<<0);
        							   counter++;
        							   if ((counter>=10) && (counter%40 ==0))
        							   		      			 {
        								   	   	   	   	   	   DownMovement();
        							   		      			 }
        						   }
        					   }

	   }


  }
int main(void)
{
  /* Write your local variable definition here */

  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  #ifdef PEX_RTOS_INIT
    PEX_RTOS_INIT();                   /* Initialization of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of Processor Expert internal initialization.                    ***/
  /* Write your code here */
    PCC-> PCCn[PCC_PORTC_INDEX] = PCC_PCCn_CGC_MASK; /*Enable clock to PORT C*/
    PCC-> PCCn[PCC_PORTD_INDEX] = PCC_PCCn_CGC_MASK;/*Enable clock to PORT D*/
    PCC-> PCCn[PCC_PORTB_INDEX] = PCC_PCCn_CGC_MASK;/*Enable clock to PORT B*/

    PTC->PDDR &= ~(1<<PTC12);
    PORTC->PCR[12] = 0x00098110;

    PTC->PDDR &= ~(1<<PTC13);
    PORTC->PCR[13] = 0x00098110;

    /*PTB6 and PTB7 are not used because they're reserved for external oscillator*/
    PTB->PDDR |= OUTPUT_LEDS;
    for(IteratorPinsB=0;IteratorPinsB<=5;IteratorPinsB++)
    {
    	PORTB->PCR[IteratorPinsB] = GPIO_ACTIVE;
    }

    for(IteratorPinsB=8;IteratorPinsB<=11;IteratorPinsB++)
    {
    	PORTB->PCR[IteratorPinsB] = GPIO_ACTIVE;
    }

    PTD->PDDR |= 1<<PTD0;
    PORTD->PCR[0] = GPIO_ACTIVE;

    PTD->PDDR |= 1<<PTD15;
    PORTD->PCR[15] = GPIO_ACTIVE;

    PTD->PDDR |= 1<<PTD16;
    PORTD->PCR[16] = GPIO_ACTIVE;

    SOSC_init_8MHz();
    SPLL_init_160MHz();
    clock_setup_80MHz();
    WDOG_disable();
    PINS_DRV_SetPins(PTD,(1<<0|1<<15|1<<16));
    PTB-> PSOR |= OUTPUT_LEDS;
    INT_SYS_EnableIRQ(PORTC_IRQn);

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
