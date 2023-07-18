#include "Driver.h"
//#include <stdint.h>

//int main(void)
//{
//	Init_Led();
//	Button_Init();
//	while (1)
//	{		  
//		  if(ReadPin_Button(BUTTON_SW2) == 0)
//		  {		  
//			 Delay(700);	
//			 while(ReadPin_Button(BUTTON_SW2) == 0)
//			 {
//				/*If held down then Do nothing */
//			 }
//			 u8status = ~u8status;
//			 WritePin_Led(u8status);
//
//		  }	  		 
//	}
//}
#include "MKE16Z4.h"

#define RED_LED_PIN             (1 << 5)
#define RED_LED_PIN             (1 << 5)
#define RED_LED_PIN             (1 << 5)

#define BUTTON_SW2 				(1 << 3)
#define COUNTFLAG                (1<<16)
uint8_t u8status = 0;
uint8_t u8status1 = 0xFF;
void delay(uint32_t Delay);
void initLed();
//void initbuuton();

int main(void)
{
    initLed();
    //initbuuton();
	while(1)
	{
	 	delay(1000);
	 	GPIOB->PTOR |= RED_LED_PIN;
	}
}
void initLed()
{
    /* Enable Clock for PORTB */
    PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);
    
    /* Setup PINB4, PINB5 as GPIO */
   
    PORTB->PCR[5] |= PORT_PCR_MUX(1);
    
    /* Setup PINB4 as Output Mode */
    FGPIOB->PDDR |=  RED_LED_PIN;
    
    /* Set default value for PINB4 = HIGH, PINB5 = LOW */
    FGPIOB->PDOR |= RED_LED_PIN;
    
}
void delay(uint32_t Delay) 
{
	
	while(Delay)
	{
	  
	  SysTick->LOAD = 48*1000 - 1U;
	  
	  SysTick->CTRL |= (uint32_t)(1<<0); 
	  SysTick->CTRL |= (uint32_t)(1<<2);
	  
	  SysTick->VAL  = 0U;
	  
	  while((SysTick->CTRL & COUNTFLAG) == 0) {}
	  --Delay;
	}
}
//void initbuuton()
//{
//    /* Enable Clock for PORTB */
//    PCC->CLKCFG[PCC_PORTD_INDEX] |= PCC_CLKCFG_CGC(1);
//    
//    /* Setup PINB4, PINB5 as GPIO */
//	PORTD->PCR[3] &=~PORT_PCR_MUX_MASK;
//    PORTD->PCR[3] |= PORT_PCR_MUX(1);
//	
//	PORTD->PCR[3] &=~ PORT_PCR_PE_MASK;
//	PORTD->PCR[3] |= PORT_PCR_PE(1);
//	/*intput*/
//	GPIOD->PDDR &=~BUTTON_SW2;
//	/*SETUP PULL UP*/
//	PORTD->PCR[3] &=~ PORT_PCR_PS_MASK;
//	PORTD->PCR[3] |= PORT_PCR_PS(1);
//	/*INTERRUP CONFIG*/
//	PORTD->PCR[3] &=~ PORT_PCR_IRQC_MASK;
//	
//	PORTD->PCR[3] &= ~(1<<16);
//	PORTD->PCR[3] |= (1<<17);
//	PORTD->PCR[3] &= ~(1<<18);
//	PORTD->PCR[3] |= (1<<19);
//	
//	NVIC_ClearPendingIRQ(PORTBCD_IRQn);
//	/*eNABLE NVIC*/
//	NVIC_EnableIRQ(PORTBCD_IRQn);
//   
//}

//void PORTBCD_IRQHandler(void)
//{
//	/*clearn flag intteruppt*/
//	PORTD->PCR[3] |= PORT_PCR_ISF_MASK;
//		
//	if(ReadPin_Button(BUTTON_SW2) == 0)
//	{		  
////			 Delay(700);	
////			 while(ReadPin_Button(BUTTON_SW2) == 0)
////			 {
////				/*If held down then Do nothing */
////			 }
//		u8status = ~u8status;
//		WritePin_Led(u8status);
//	 }	  	
//		  
//}


