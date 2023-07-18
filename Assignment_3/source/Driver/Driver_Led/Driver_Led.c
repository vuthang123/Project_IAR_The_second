#include "Driver_Led.h"
#include "HAL_PORT.h"
#include "HAL_GPIO.h"
#include "HAL_CLOCK.h"
#include "HAL_SYSTICK.h"
#include "stdbool.h"
#include "MKE16Z4.h"

#define COLOR_MASK (0xFFu)
#define RED_SHIFT    (16u)
#define GREEN_SHIFT  (8u)
#define BLUE_SHIFT   (0u)
#define TICKS 255
#define DELAY 2000
#define CHANGE_RGB(CHANGE_RED,CHANGE_GREEN,CHANGE_BLUE) ((CHANGE_RED << RED_SHIFT)|\
                                                         (CHANGE_GREEN << GREEN_SHIFT)|\
														 (CHANGE_BLUE << BLUE_SHIFT))
volatile uint32_t delay_count;

volatile uint8_t s_red_color;
volatile uint8_t s_green_color;
volatile uint8_t s_blue_color;

static void DRIVER_Led_Transistion(uint32_t oldcolor ,uint32_t newColor);


DRIVER_LED_Erorr DRIVER_LED_init(PORT_Type2* PORTx,PORT_Type2* PORTy,PORT_Type2* PORTz)
{
	
	DRIVER_LED_Erorr E_Retval = DRIVER_LED_SUCCESS ;
	
	/*cHECK ENABLE CLOCK PORT  B*/
	if (HAL_CLOCK_Init(PCC_PORTB_INDEX,PCC_PORTB_CGC) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*select mode gpio*/
	if(HAL_PORT_Select_Mode(PORTx,LED_RED,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*config output*/
	if(HAL_GPIO_IO(FGPIOB2,LED_RED1,HAL_GPIO_OUTPUT))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*Setup defaut*/
	if(HAL_GPIO_Setup_Defaut(FGPIOB2,LED_RED1))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/************************Enable clock PORTB************************/

	/*select mode gpio*/
	if(HAL_PORT_Select_Mode(PORTy,LED_GREEN,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*config output*/
	if(HAL_GPIO_IO(FGPIOB2,LED_GREEN1,HAL_GPIO_OUTPUT))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*Setup defaut*/
	if(HAL_GPIO_Setup_Defaut(FGPIOB2,LED_GREEN1))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/***********************Enable clock PORTD********************************/
	
		/*cHECK ENABLE CLOCK PORT  D*/
	if (HAL_CLOCK_Init(PCC_PORTD_INDEX,PCC_PORTD_CGC_D) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*select mode gpio*/
	if(HAL_PORT_Select_Mode(PORTz,LED_BLUE,Mode_Gpio) != 0)
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*config output*/
	if(HAL_GPIO_IO(FGPIOD2,LED_BLUE1,HAL_GPIO_OUTPUT))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	/*Setup defaut*/
	if(HAL_GPIO_Setup_Defaut(FGPIOD2,LED_BLUE1))
	{
		E_Retval = DRIVER_LED_FAIL;	
	}
	
	return E_Retval;
}


void SysTick_Handler(void)
{
	delay_count++;
    static uint32_t count_us=0;
	count_us++;

	if (count_us == 255UL)
	{
		count_us = 0;
		HAL_GPIO_Clear_State(FGPIOB2,LED_RED1);
		HAL_GPIO_Clear_State(FGPIOB2,LED_GREEN1);
	    HAL_GPIO_Clear_State(FGPIOD2,LED_BLUE1);
	}
	
	if(count_us == s_red_color)
	{
		HAL_GPIO_Set_State(FGPIOB2,LED_RED1);
	}
	
	if(count_us == s_green_color)
	{
		HAL_GPIO_Set_State(FGPIOB2,LED_GREEN1);
	}
	
	if(count_us == s_blue_color)
	{
		HAL_GPIO_Set_State(FGPIOD2,LED_BLUE1);
	}	
}

void RGB_run(uint32_t *set_color_rgb)
{
	uint32_t index =0;
	
	for(index=0;index<5;index++)
	{
  
		DRIVER_Led_Transistion(*(set_color_rgb+index),*(set_color_rgb+index+1));
		 		
	}
}

static void DRIVER_Led_Transistion(uint32_t oldcolor ,uint32_t newColor)
{

    uint8_t CHANGE_red;
	uint8_t CHANGE_green;
	uint8_t CHANGE_blue;
	
	uint32_t RGB_new;
	
	uint8_t DIFF_red;
	uint8_t DIFF_green;
	uint8_t DIFF_blue;
	uint8_t  Step = 0;
	
	uint8_t  OLD_red_code;
	uint8_t  OLD_green_code;
	uint8_t  OLD_blue_code;
	
	uint8_t  NEW_red_code;
	uint8_t  NEW_green_code;
	uint8_t  NEW_blue_code;
	
	OLD_red_code  = (oldcolor >> RED_SHIFT)   & COLOR_MASK;
	OLD_green_code= (oldcolor >> GREEN_SHIFT) & COLOR_MASK;
	OLD_blue_code = (oldcolor >> BLUE_SHIFT)  & COLOR_MASK;
	
    NEW_red_code  = (newColor >> RED_SHIFT)   & COLOR_MASK;
	NEW_green_code= (newColor >> GREEN_SHIFT) & COLOR_MASK;
	NEW_blue_code = (newColor >> BLUE_SHIFT)  & COLOR_MASK;
	
	DIFF_red    = NEW_red_code   -  OLD_red_code;
	DIFF_green  = NEW_green_code -  OLD_green_code;
	DIFF_blue   = NEW_blue_code  -  OLD_blue_code;
	
	for (Step = 0; Step < TICKS ;Step++)
	{
		  CHANGE_red  =OLD_red_code  + DIFF_red*Step/(TICKS-1);
		  CHANGE_green=OLD_green_code+ DIFF_green*Step/(TICKS-1);
		  CHANGE_blue =OLD_blue_code + DIFF_blue*Step/(TICKS-1);		  
		  RGB_new =CHANGE_RGB(CHANGE_red,CHANGE_green,CHANGE_blue);	
		  Set_Color(RGB_new);
		  Delay_us(DELAY);
	}

}

void Set_Color(uint32_t Color)
{
	s_red_color   = (Color >> RED_SHIFT)   & COLOR_MASK;
	s_green_color = (Color >> GREEN_SHIFT) & COLOR_MASK;
	s_blue_color  = (Color >> BLUE_SHIFT)  & COLOR_MASK;
}
