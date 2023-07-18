#ifndef DRIVER_BUTTON_H
#define DRIVER_BUTTON_H

#include "HAL_CLOCK.h"
#include "HAL_PORT.h"

/* @brief  initialization clock PORT D */
#define PCC_PORTD_CGC           (1 << 30UL)
/* @brief  initialization pin PORT D for button*/
#define BUTTON_SW2              (3UL)
/* @brief  initialization pin PORT D for button*/
#define BUTTON                  (1 << 3UL)

/* @brief  return funtion for driver button*/
typedef enum 
{
	  DRIVER_BUTTON_SUCCESS =0,
	  DRIVER_BUTTON_FAIL 
	  
}DRIVER_BUTTON_Erorr;

/*******************************************************************************
 * API
 ******************************************************************************/
/**
  * @brief  Initialization for Button
  * @param PORT_Type (PORTA ,PORTB,PORTC,PORTD,PORTE)         
  * @retval 0 : SUCCESS
			1 : ERROR
  */
DRIVER_BUTTON_Erorr DRIVER_BUTTON_init(PORT_Type* PORTx);


#endif /*DRIVER_BUTTON_H*/
/*******************************************************************************
 * EOF
 ******************************************************************************/