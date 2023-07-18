#include "Driver_LPIT.h"
#include "HAL_LPIT.h"
#include "MKE16Z4.h"

/* Define a global function pointer*/
void  (*s_funct)(void);

/*******************************************************************************
 * Code
 ******************************************************************************/
/**
  * @brief  Chaining timer 
  * @param Base_LPIT: base Lpit
 
  * @retval none
  */
void Driver_LPIT_init(LPIT_Type* Base_LPIT)
{
	Enble_CLOCK_LPIT_FIRC(SCG,PCC);
	
	Setup_timer(Base_LPIT);
		
}
/**
  * @brief  Chaining timer 
  * @param Base_LPIT: base Lpit
           Clock  : Default Clock
           IRQ   :  Number rountine   
  * @retval none
  */
void Driver_LPIT_timer0(LPIT_Type* Base_LPIT,uint32_t clock,IRQn_Type IRQ)
{
	chanal_number my_number_1 =channel_0;
	
	chanal_number_s my_number = {my_number_1};
	
	Select_mode(Base_LPIT,&my_number);
	
	One_timer(Base_LPIT,&my_number,clock,IRQ);
	
	/* Callback function*/
    HAL_LPIT_Callback(s_funct);	
}
/**
  * @brief  Chaining timer 
  * @param Base_LPIT: base Lpit
           Clock  : Default Clock
           IRQ   :  Number rountine   
  * @retval none
  */
void Driver_LPIT_chain(LPIT_Type* Base_LPIT,uint32_t clock,IRQn_Type IRQ)
{
	chanal_number my_number_1 =channel_0;
	chanal_number my_number_2 =channel_1;
	
	chanal_number_s my_number = {my_number_1,my_number_2};
	
	Select_mode(Base_LPIT,&my_number);
	
	Chaning_timer(Base_LPIT,&my_number,clock,IRQ);
	
	/* Callback function*/
    HAL_LPIT_Callback(s_funct);	
}
/**
  * @brief  function call handler callback
  * @param PORT_Type (PORTA ,PORTB,PORTC,PORTD,PORTE)         
  * @retval 0 : SUCCESS
			1 : ERROR
  */

void DRIVER_LPIT_Callback(void (*fun)(void))
{
   s_funct = fun;
}
/*******************************************************************************
 * EOF
 ******************************************************************************/