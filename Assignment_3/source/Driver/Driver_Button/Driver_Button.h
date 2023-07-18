#ifndef DRIVER_BUTTON_H
#define DRIVER_BUTTON_H

#include "HAL_CLOCK.h"
#include "HAL_PORT.h"
#include "HAL_GPIO.h"
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
typedef enum
{
	FIRST  =0,
	SECOND =1,
	THIRD  =2
}Button_type;

/*******************************************************************************
 * API
 ******************************************************************************/
DRIVER_BUTTON_Erorr DRIVER_BUTTON_init(PORT_Type2* PORTx);

uint32_t Driver_Button_count(FGPIO_Type2* FGPIO2X,uint32_t Pin);
#endif /*DRIVER_BUTTON_H*/
