#ifndef DRIVER_LED_H
#define DRIVER_LED_H

#include "HAL_CLOCK.h"
#include "HAL_PORT.h"
#include "HAL_GPIO.h"

/* @brief  initialization clock PORT B for led*/
#define PCC_PORTB_CGC           (1 << 30UL)

/* @brief  initialization pin PORT B for led*/
#define LED_RED1   (1<<5UL)

/* @brief  initialization pin PORT B for led*/
#define LED_RED    (5UL)

/* @brief  return funtion for driver led*/
typedef enum {
	  DRIVER_LED_SUCCESS =0,
	  DRIVER_LED_FAIL ,
}DRIVER_LED_Erorr;



/*******************************************************************************
 * API
 ******************************************************************************/

DRIVER_LED_Erorr DRIVER_LED_init(PORT_Type* PORTx);

void DRIVER_LED_Toggle(FGPIO_Type* FGPIOx,FGPIO_Type* FGPIOy,uint32_t Pin_state_Button,uint32_t Pin_state_Led);

#endif /*DRIVER_LED_H*/