#include "Driver_Led.h"
#include "Driver_Button.h"
#include "HAL_SYSTICK.h"


extern volatile  uint8_t Button_count;


uint32_t rgb_set1[5] = {0x940025, 0xFF7240, 0x5265FF, 0xFF2080, 0xD897FF};
uint32_t rgb_set2[5] = {0x5065FF, 0xFF5396, 0xFF27F0, 0x30FF30, 0xFFF00A};
uint32_t rgb_set3[5] = {0x9600FF, 0x82FF00, 0xFF7240, 0x30F2D9, 0x0FF01F};


int main()
{	
	/********************PLEASE PRESS RESET ------> PRESS SW2****************/
	  
	DRIVER_LED_init(PORTB2,PORTB2,PORTD2);
	DRIVER_BUTTON_init(PORTD2);
	Systick_Configuration();
	
	while(1)
	{
		switch (Button_count)
		{
			  case 1:
			  {
					
					RGB_run(rgb_set1);
					break;
			  }
			  case 2:
			  {
					RGB_run(rgb_set2);
					break;
			  }
			  case 3:
			  {
					RGB_run(rgb_set3);
					break;
			  }
		}
		   
	}
}


