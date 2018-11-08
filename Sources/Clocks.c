#include "Clocks.h"

/*******************************************************************************
Function: SOSC_init_8MHz
Notes   : Set up the 8MHz clk
*******************************************************************************/
void CLOCKS_SOSC_init_8MHz(void)
{
 SCG->SOSCDIV=SOSCDIV1_SOSCDIV2_DIV1;  /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
 SCG->SOSCCFG=SOSC_RANGE_1MHZ_8MHZ; /* Range=2: Medium freq (SOSC between 1MHz-8MHz)*/
 while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
 SCG->SOSCCSR=SOSCCSR_REGISTER_EN;
 while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}

/*******************************************************************************
Function: SPLL_init_160MHz
Notes   : Set up the 160MHz clk
*******************************************************************************/
void CLOCKS_SPLL_init_160MHz(void)
{
 while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
 SCG->SPLLCSR = SPLL_DISABLED; /* SPLLEN=0: SPLL is disabled (default) */
 SCG->SPLLDIV = SPLLDIV1_DIV2_SPLLDIV2_DIV4; /* SPLLDIV1 divide by 2; SPLLDIV2 divide by 4 */
 SCG->SPLLCFG = PREDIV_SOSC_CLK_BY_1; /* PREDIV=0: Divide SOSC_CLK by 0+1=1 */
 while(SCG->SPLLCSR & SCG_SPLLCSR_LK_MASK); /* Ensure SPLLCSR unlocked */
 SCG->SPLLCSR = SPLLCSR_CAN_BE_WRITTEN_NO_LK; /* LK=0: SPLLCSR can be written */
 while(!(SCG->SPLLCSR & SCG_SPLLCSR_SPLLVLD_MASK)); /* Wait for SPLL valid */
}


/*******************************************************************************
Function: clock_setup_80MHz
Notes   : Set up the 80MHz clock
*******************************************************************************/
void CLOCKS_Clock_Setup_80MHz(void) /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
{

 SCG->RCCR=SCG_RCCR_SCS(SPLL_AS_CLKSOURCE) /* PLL as clock source*/
 |SCG_RCCR_DIVCORE(0b01) /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz*/
 |SCG_RCCR_DIVBUS(0b01) /* DIVBUS=1, div. by 2: bus clock = 40 MHz*/
 |SCG_RCCR_DIVSLOW(0b10); /* DIVSLOW=2, div. by 3: SCG slow, flash clock= 26 2/3 MHz*/
 while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}
}


/*******************************************************************************
Function: WDOG_disable
Notes   : Function to disable the watch dog timer
*******************************************************************************/
void CLOCKS_WDOG_disable (void)
  {
    WDOG->CNT=WATCH_DOG_COUNTER_MASK; /*Unlock Watchdog*/
    WDOG->TOVAL=WD_TIMEOUT_MAX; /*Maximum timeout value*/
    WDOG->CS = WD_DISABLE_WATCHDOG;  /*Disable Watchdog*/
  }

/*******************************************************************************
Function: CLOCKS_Init
Notes   : Function to initialize Clocks
*******************************************************************************/
void CLOCKS_Init(void)
{
    CLOCKS_SOSC_init_8MHz();        /*Initialize system oscillator for 8 MHz xtal*/
    CLOCKS_SPLL_init_160MHz();      /*Initialize SPLL to 160 MHz with 8 MHz SOSC*/
    CLOCKS_Clock_Setup_80MHz();     /*Initialize clocks: 80MHz sysclk & core, 40MHz bus, 20MHz flash*/
    CLOCKS_WDOG_disable();          /*Disables the watch dog timer*/        
}