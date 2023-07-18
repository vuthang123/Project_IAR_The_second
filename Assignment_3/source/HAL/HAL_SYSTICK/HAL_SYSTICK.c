#include "HAL_SYSTICK.h"
#include "MKE16Z4.h"
#include "stdint.h"

extern uint32_t delay_count;

#define US  100000

void Systick_Configuration(void)
{
    
    SysTick->LOAD = 5*SystemCoreClock / US - 1U; 

    // C?u hình SysTick Control and Status Register
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | 
                    SysTick_CTRL_TICKINT_Msk |   
                    SysTick_CTRL_ENABLE_Msk;
	
	
}

void Delay_us(uint32_t microsecond)
{
    delay_count = 0; 

    while(delay_count < microsecond);
}

