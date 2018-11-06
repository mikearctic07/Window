#include "S32K144.h" /* include peripheral declarations S32K144 */
#include "s32_core_cm4.h"
#include "Clocks.h"

/*******************************************************************************
Function: SOSC_init_8MHz
Notes   : Set up the 8MHz clk
        :
        :
*******************************************************************************/
void SOSC_init_8MHz(void)
{
 SCG->SOSCDIV=0x00000101; /* SOSCDIV1 & SOSCDIV2 =1: divide by 1 */
 SCG->SOSCCFG=0x00000024; /* Range=2: Medium freq (SOSC between 1MHz-8MHz)*/
 while(SCG->SOSCCSR & SCG_SOSCCSR_LK_MASK); /* Ensure SOSCCSR unlocked */
 SCG->SOSCCSR=0x00000001;
 while(!(SCG->SOSCCSR & SCG_SOSCCSR_SOSCVLD_MASK)); /* Wait for sys OSC clk valid */
}
/*******************************************************************************
Function: SPLL_init_160MHz
Notes   : Set up the 160MHz clk
        :
        :
*******************************************************************************/


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


/*******************************************************************************
Function: clock_setup_80MHz
Notes   : Set up the 80MHz clock
        :
        :
*******************************************************************************/
void clock_setup_80MHz(void) /* Change to normal RUN mode with 8MHz SOSC, 80 MHz PLL*/
{

 SCG->RCCR=SCG_RCCR_SCS(6) /* PLL as clock source*/
 |SCG_RCCR_DIVCORE(0b01) /* DIVCORE=1, div. by 2: Core clock = 160/2 MHz = 80 MHz*/
 |SCG_RCCR_DIVBUS(0b01) /* DIVBUS=1, div. by 2: bus clock = 40 MHz*/
 |SCG_RCCR_DIVSLOW(0b10); /* DIVSLOW=2, div. by 3: SCG slow, flash clock= 26 2/3 MHz*/
 while (((SCG->CSR & SCG_CSR_SCS_MASK) >> SCG_CSR_SCS_SHIFT ) != 6) {}
}


/*******************************************************************************
Function: WDOG_disable
Notes   : Function to disable the watch dog timer
        :
        :
*******************************************************************************/
void WDOG_disable (void)
  {
	WDOG->CNT=0xD928C520; /*Unlock Watchdog*/
	WDOG->TOVAL=0x0000FFFF; /*Maximum timeout value*/
	WDOG->CS = 0x00002100;  /*Disable Watchdog*/
  }
