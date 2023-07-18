#include "HAL_LPIT.h"
#include "MKE16Z4.h"

#define CLOCK 24000000

/* Static global variable for function pointer type*/

void (*hal_callback_floor)(void);
/*******************************************************************************
 * Code
 ******************************************************************************/
void Setup_timer(LPIT_Type* Base_LPIT)
{
	/*reset timer*/
	Base_LPIT->MCR |= LPIT_MCR_SW_RST(1);
	Base_LPIT->MCR &= ~LPIT_MCR_SW_RST_MASK;
	/*debug--doze modes -- enable the module*/
	LPIT0->MCR &= (~LPIT_MCR_DBG_EN_MASK);
	LPIT0->MCR &= (~LPIT_MCR_DOZE_EN_MASK);
	LPIT0->MCR &= (~LPIT_MCR_M_CEN_MASK);
	
	LPIT0->MCR |= LPIT_MCR_DBG_EN(1)|LPIT_MCR_DOZE_EN(1)|LPIT_MCR_M_CEN(1);
}
void Select_mode(LPIT_Type* Base_LPIT,chanal_number_s *num)
{
	Base_LPIT->CHANNEL[num->number0].TCTRL &=~LPIT_TCTRL_MODE_MASK;
	Base_LPIT->CHANNEL[num->number0].TCTRL |= LPIT_TCTRL_MODE(0);
	Base_LPIT->CHANNEL[num->number1].TCTRL &=~LPIT_TCTRL_MODE_MASK;
	Base_LPIT->CHANNEL[num->number1].TCTRL |= LPIT_TCTRL_MODE(0);

}
void Select_channal_mul(LPIT_Type* Base_LPIT,chanal_number_s *num)
{
	Base_LPIT->CHANNEL[num->number0].TCTRL &=~LPIT_TCTRL_MODE_MASK;
	Base_LPIT->CHANNEL[num->number0].TCTRL |= LPIT_TCTRL_MODE(0);
	Base_LPIT->CHANNEL[num->number1].TCTRL &=~LPIT_TCTRL_MODE_MASK;
	Base_LPIT->CHANNEL[num->number1].TCTRL |= LPIT_TCTRL_MODE(0);

}
void One_timer(LPIT_Type* Base_LPIT,chanal_number_s *num,uint32_t clock,IRQn_Type IRQ)
{
	  	/*timer0*/
	Base_LPIT->CHANNEL[num->number0].TVAL = (clock-1);
	// Enable channel0 interrupt
    Base_LPIT->MIER |= LPIT_MIER_TIE0_MASK; 
	/*Enable channel0 interrupt;*/
	NVIC_EnableIRQ(IRQ);
	// Starts the timer counting after all configuration
	Base_LPIT->SETTEN |=  LPIT_SETTEN_SET_T_EN_0_MASK;

}
void Chaning_timer(LPIT_Type* Base_LPIT,chanal_number_s *num,uint32_t clock,IRQn_Type IRQ)
{
	/*Timer 0*/
	Base_LPIT->CHANNEL[num->number0].TVAL = (clock-1);
	Base_LPIT->CHANNEL[num->number0].TCTRL |= (LPIT_TCTRL_T_EN_MASK);
	
	/*CHAING TIMER*/
	Base_LPIT->CHANNEL[num->number1].TCTRL |= LPIT_TCTRL_CHAIN(1);
	
	/*Timer 0*/
	Base_LPIT->CHANNEL[num->number1].TVAL = 9;
	Base_LPIT->CHANNEL[num->number1].TCTRL |= (LPIT_TCTRL_T_EN_MASK);
	
	NVIC_EnableIRQ(IRQ);
	// Enable channel1 interrupt
    Base_LPIT->MIER |= LPIT_MIER_TIE1_MASK;
	
	Base_LPIT->SETTEN |=  LPIT_SETTEN_SET_T_EN_0_MASK;
	Base_LPIT->SETTEN |=  LPIT_SETTEN_SET_T_EN_1_MASK;
}


void Enble_CLOCK_LPIT_FIRC(SCG_Type *base_clock,PCC_Type* base_clock_peripheral)
{
	base_clock->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(2);
	
	base_clock_peripheral->CLKCFG[PCC_LPIT0_INDEX] &=~PCC_CLKCFG_CGC_MASK;
	base_clock_peripheral->CLKCFG[PCC_LPIT0_INDEX] &=~PCC_CLKCFG_CGC_MASK;
	base_clock_peripheral->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_PCS(3);
	base_clock_peripheral->CLKCFG[PCC_LPIT0_INDEX] |= PCC_CLKCFG_CGC(1);
}

void LPIT0_IRQHandler()
{
	// Clear interrupt flag
    LPIT0->MSR |= LPIT_MSR_TIF1_MASK;

	//call func
	hal_callback_floor();
	
}

void HAL_LPIT_Callback(void (*sfun)(void))
{
	/* Assign pointer of function to global function pointer*/
    hal_callback_floor = sfun;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/