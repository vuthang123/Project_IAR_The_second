#include "HAL_PORT.h"

/**
  * @brief  Select mode for PORT
  * @param  PORTx: Select port
  * @param  Select_Pin: specifies the port bit to read.
  * @param  Select_Mode_IO:Select mode
  * @retval 0 : SUCCESS
			1 : ERROR
  */
HAL_PORT_Erorr_E HAL_PORT_Select_Mode(PORT_Type2* PORTx,uint32_t Select_Pin,Mux_type Select_Mode_IO)
{
	HAL_PORT_Erorr_E retval = HAL_PORT_SUCCESS;
	
	if((PORTx == PORTA2) || (PORTx == PORTB2) || (PORTx == PORTC2)\
		  || (PORTx == PORTD2) || (PORTx == PORTE2))
	{
		  /* Clean bitfield */
		  PORTx->PCR[Select_Pin] &= ~(PORT_PCR_MUX_MASK);
		  /* Set bitfield */
		  PORTx->PCR[Select_Pin] |=  (PORT_PCR_MUX(Select_Mode_IO));
	
	}
	else
	{
		  retval = HAL_PORT_FAIL;
	}
	
	return retval;
}
/**
  * @brief  PULL enable for PORT
  * @param  PORTx: Select port
  * @param  Select_Pin: specifies the port bit to read.
  * @param  Select_Mode_IO:Select mode
  * @retval 0 : SUCCESS
			1 : ERROR
  */
HAL_PORT_Erorr_E HAL_PORT_Select_Pull_Enable(PORT_Type2* PORTx,uint32_t Select_Pin,Pull_ENABLE_Type_E Select_Mode_IO)
{

	HAL_PORT_Erorr_E retval = HAL_PORT_SUCCESS;
	
	if((PORTx == PORTA2) || (PORTx == PORTB2) || (PORTx == PORTC2)\
		  || (PORTx == PORTD2) || (PORTx == PORTE2))
	{
		  /* Clean bitfield */
		  PORTx->PCR[Select_Pin] &= ~(PORT_PCR_PE_MASK);
		  /* Set bitfield */
		  PORTx->PCR[Select_Pin] |=  (PORT_PCR_PE(Select_Mode_IO));
	}
	
	else
	{
		  retval = HAL_PORT_FAIL;
	}

	
	return retval;
}
/**
  * @brief  Select PULL mode for PORT
  * @param  PORTx: Select port
  * @param  Select_Pin: specifies the port bit to read.
  * @param  Select_Mode_IO:Select mode
  * @retval 0 : SUCCESS
			1 : ERROR
  */
HAL_PORT_Erorr_E HAL_PORT_Select_Pull_Mode(PORT_Type2* PORTx,uint32_t Select_Pin,Pull_SELECT_Type_E Select_Mode_IO)
{

	HAL_PORT_Erorr_E retval = HAL_PORT_SUCCESS;
	
	if((PORTx == PORTA2) || (PORTx == PORTB2) || (PORTx == PORTC2)\
		  || (PORTx == PORTD2) || (PORTx == PORTE2))
	{
		/* Clean bitfield */
		PORTx->PCR[Select_Pin] &= ~(PORT_PCR_PS_MASK);
		/* Set bitfield */
		PORTx->PCR[Select_Pin] |=  (PORT_PCR_PS(Select_Mode_IO));
	
	}
	else
	{
		  retval = HAL_PORT_FAIL;
	}
	return retval;
}