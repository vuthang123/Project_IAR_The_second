#include "Driver_Button.h"
#include "Driver_Led.h"
#include <stdint.h>

int main(void)
{
	/* @brief  initialization PORT D for button*/
	DRIVER_BUTTON_init(PORTD);
	/* @brief  nitialization PORT B for led*/
	DRIVER_LED_init(PORTB);
	
	while (1)
	{	
		  /* @brief  Toggle led*/
		  DRIVER_LED_Toggle(FGPIOD,FGPIOB,BUTTON,LED_RED1);
	}
}

  