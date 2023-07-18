#include "HAL_GPIO.h"

/*******************************************************************************
 * Prototypes
 ******************************************************************************/



/*******************************************************************************
 * Code
 ******************************************************************************/

/**
  * @brief  Config input or out put.
  * @param  FGPIOx: where x can be (A..E depending on device used) to select the FGPIO peripheral
  * @param  Pin_select: specifies the port bit to read.
  * @param  Select_Mode_IO: Select mode        
  * @retval 0 : SUCCESS
			1 : ERROR
  */
HAL_GPIO_Erorr_E HAL_GPIO_IO(FGPIO_Type2* FGPIOx,uint32_t Pin_select,HAL_GPIO_Select_Mode_IO Select_Mode_IO)
{	
	HAL_GPIO_Erorr_E E_retval = HAL_GPIO_SUCCESS;
	
		if((FGPIOx == FGPIOA2) || (FGPIOx == FGPIOB2) || (FGPIOx == FGPIOC2)\
		  || (FGPIOx == FGPIOD2) || (FGPIOx == FGPIOE2))
	{
		 
		 
		 switch (Select_Mode_IO)
		 {
			 case HAL_GPIO_INPUT:
			 {
				/*input*/
				FGPIOx->PDDR &= ~Pin_select;
				break;
			 }
			 case HAL_GPIO_OUTPUT:
			 { 		
				/*outpot*/
				FGPIOx->PDDR |= Pin_select;
				break;
			 }
		 }
		 	  
	}
	else
	{
		E_retval = 	HAL_GPIO_FAIL;
	}
	
	return E_retval;
	
}
 

/**
  * @brief  Reads the specified input port pin.
  * @param  FGPPIOx: where x can be (A..E depending on device used) to select the FGPIO peripheral
  * @param  Pin_select: specifies the port bit to read.
  * @retval The input port pin value.
  */
uint32_t HAL_GPIO_Read_Pin(FGPIO_Type2* FGPPIOx,uint32_t Pin_select)
{
	uint32_t status = 0;
	
	if ((FGPPIOx->PDIR & Pin_select) != 0)
	{
	  status = 1;
	}
	else
	{
	  status = 0;
	}

	return status;
	
}
/*Data Output*/
/**
  * @brief  Write the specified input port pin.
  * @param  FGPPIOx: where x can be (A..E depending on device used) to select the FGPIO peripheral
  * @param  Pin_select: specifies the port bit to write.
  * @param  u8status: Status .
  * @retval none
  */
void HAL_GPIO_Write_Pin(FGPIO_Type2* GPIOx,FGPIO_Type2* FGPIOy,uint32_t Pin_Select,uint8_t u8status)
{
	
	if (u8status != 0)
	{
	  HAL_GPIO_Clear_State(FGPIOy,Pin_Select);
		  
	}
	else
	{
	  HAL_GPIO_Set_State(FGPIOy,Pin_Select);
	}
}
/*Setup defaut*/
/**
  * @brief  Setup defaut specified output pin.
  * @param  GPIOx: where x can be (A..E depending on device used) to select the FGPIO peripheral
  * @param  Pin_select: specifies the port bit to read.
  * @retval 0 : SUCCESS
			1 : ERROR
  */
HAL_GPIO_Erorr_E HAL_GPIO_Setup_Defaut(FGPIO_Type2* FGPIOx,uint32_t Pin_select)
{

	HAL_GPIO_Erorr_E E_retval = HAL_GPIO_SUCCESS;
	if((FGPIOx == FGPIOA2) || (FGPIOx == FGPIOB2) || (FGPIOx == FGPIOC2)\
		  || (FGPIOx == FGPIOD2) || (FGPIOx == FGPIOE2))
	{
		
		FGPIOx->PDOR |= Pin_select;
	}
	else
	{
		E_retval = 	HAL_GPIO_FAIL;
	}
		
	return E_retval;

}
/**
  * @brief  Set state specified output gpio pin.
  * @param  GPIOx: where x can be (A..E depending on device used) to select the FGPIO peripheral
  * @param  Pin_select: specifies the port bit to read.        
  * @retval 0 : SUCCESS
			1 : ERROR
  */

 HAL_GPIO_Erorr_E HAL_GPIO_Set_State(FGPIO_Type2* FGPIOy,uint32_t Pin_select)
{
	HAL_GPIO_Erorr_E E_retval = HAL_GPIO_SUCCESS;
	
	if((FGPIOy == FGPIOA2) || (FGPIOy == FGPIOB2) || (FGPIOy == FGPIOC2)\
		  || (FGPIOy == FGPIOD2) || (FGPIOy == FGPIOE2))
	{
		
		FGPIOy->PSOR |= Pin_select;
	}
	else
	{
		E_retval = 	HAL_GPIO_FAIL;
	}
	
	
	return E_retval;
	
}
/**
  * @brief  Clear state specified output gpio pin.
  * @param  GPIOx: where x can be (A..E depending on device used) to select the FGPIO peripheral
  * @param  Pin_select: specifies the port bit to read.        
  * @retval 0 : SUCCESS
			1 : ERROR
  */
 HAL_GPIO_Erorr_E HAL_GPIO_Clear_State(FGPIO_Type2* FGPIOy,uint32_t Pin_select)
{
	HAL_GPIO_Erorr_E E_retval = HAL_GPIO_SUCCESS;
	
	if((FGPIOy == FGPIOA2) || (FGPIOy == FGPIOB2) || (FGPIOy == FGPIOC2)\
		  || (FGPIOy == FGPIOD2) || (FGPIOy == FGPIOE2))
	{
		FGPIOy->PCOR |= Pin_select;
	}
	else
	{
		E_retval = 	HAL_GPIO_FAIL;
	}
	
	
	return E_retval;
	
}

