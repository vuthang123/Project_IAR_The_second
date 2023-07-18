#include "HAL_SYSTICK.h"
#include "MKE16Z4.h"
#include "stdint.h"

#define COUNTFLAG                   (1<<16)
#define SYST_CSR_RESET_VALUE        (0x00000000UL) /*SysTick Reload Value Register */
#define SYST_CVR_RESET_VALUE        (0x00000000UL) /*SysTick Current Value Register*/
#define CLOCKSOURCE_Mask (2UL)
#define CLOCKSOURCE(x) (1 << CLOCKSOURCE_Mask)

extern volatile uint32_t TICK;

void Systick_init(uint32_t ticks)
{
	/*Disable systick*/
	SysTick->CTRL = SYST_CSR_RESET_VALUE;
	SysTick->LOAD  = (uint32_t)(ticks - 1UL); 
	/** select soucre clock 
     */
	/*Clear bit fields*/
	SysTick->CTRL &= ~(CLOCKSOURCE_Mask);
	/*Ser bit fields*/
	SysTick->CTRL |= CLOCKSOURCE(1)| SysTick_CTRL_ENABLE_Msk|SysTick_CTRL_TICKINT_Msk;
	
	SysTick->VAL   = SYST_CVR_RESET_VALUE;
		
}




void delay_ms(uint32_t ms) 
{
	// Calculate the number of ticks to wait for  
    uint32_t ticks = SystemCoreClock / 1000 * ms; 
	// Record the starting time for busy-waiting
    uint32_t start_time = SysTick->VAL; 
	
    while ((SysTick->VAL - start_time) < ticks) 
	{
        // Busy-wait for the required number of ticks
    }
}


