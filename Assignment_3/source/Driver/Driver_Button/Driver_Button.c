#include "Driver_Button.h"
#include "MKE16Z4.h"
#include "HAL_GPIO.h"
uint8_t Button_count =0;


/*******************************************************************************
 * Code
 ******************************************************************************/
/**
  * @brief  Initialization for Button
  * @param PORT_Type (PORTA ,PORTB,PORTC,PORTD,PORTE)         
  * @retval 0 : SUCCESS
			1 : ERROR
  */


DRIVER_BUTTON_Erorr DRIVER_BUTTON_init(PORT_Type2* PORTx)
{
	
	DRIVER_BUTTON_Erorr E_Retval = DRIVER_BUTTON_SUCCESS ;
	/*cHECK ENABLE CLOCK PORT  D*/
	if (HAL_CLOCK_Init(PCC_PORTD_INDEX,PCC_PORTD_CGC) != 0)
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	/*select mode gpio */
	if(HAL_PORT_Select_Mode(PORTx,BUTTON_SW2,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	
	/*pull enable*/
	if(HAL_PORT_Select_Pull_Enable(PORTx,BUTTON_SW2,PULL_ENABLE))
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	
	/*pull up */
	if(HAL_PORT_Select_Pull_Mode(PORTx,BUTTON_SW2,PULL_UP))
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	/*config input*/
	if(HAL_GPIO_IO(FGPIOD2,BUTTON,HAL_GPIO_INPUT))
	{
		E_Retval = DRIVER_BUTTON_FAIL;	
	}
	PORTD->PCR[BUTTON_SW2] |=PORT_PCR_IRQC(0b1010);
	NVIC_ClearPendingIRQ(PORTBCD_IRQn);
	/*Enable nvic*/
	NVIC_EnableIRQ(PORTBCD_IRQn);
	
	return E_Retval;
}


void PORTBCD_IRQHandler()
{

	PORTD->PCR[3] |= PORT_PCR_ISF_MASK;
	Button_count ++;
	if(Button_count==4){Button_count=0;}
}
