#ifndef DRIVER_LED_H
#define DRIVER_LED_H

#include "HAL_CLOCK.h"
#include "HAL_PORT.h"
#include "HAL_GPIO.h"

/* @brief  initialization clock PORT B for led*/
#define PCC_PORTB_CGC           (1 << 30UL)

/* @brief  initialization clock PORT D */
#define PCC_PORTD_CGC_D           (1 << 30UL)

/* @brief  initialization pin PORT B for led*/
#define LED_RED1     (1<<5UL)
#define LED_GREEN1   (1<<4UL)
#define LED_BLUE1   (1<<1UL)
/* @brief  initialization pin PORT B for led*/
#define RED_LED_PIN    (5UL)
#define GREEN_LED_PIN  (4UL)
#define BLUE_LED_PIN   (1UL)
#define LED_RED (5UL)
#define LED_GREEN  (4UL)
#define LED_BLUE   (1UL)

/* @brief  return funtion for driver led*/
typedef enum {
	  DRIVER_LED_SUCCESS =0,
	  DRIVER_LED_FAIL ,
}DRIVER_LED_Erorr;

void Set_Color(uint32_t Color);

/*******************************************************************************
 * API
 ******************************************************************************/

DRIVER_LED_Erorr DRIVER_LED_init(PORT_Type2* PORTx,PORT_Type2* PORTy,PORT_Type2* PORTz);
void RGB_run(uint32_t *set_color_rgb);
void Set_Color(uint32_t Color);
uint32_t ReadPin_Button(FGPIO_Type2* FGPIO2,uint32_t Pin_select);
#endif /*DRIVER_LED_H*/