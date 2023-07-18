#include "Driver_Led.h"
#include "Driver_LPIT.h"
#include "MKE16Z4.h"


static void HanInterupt(void);

int main()
{	
	DRIVER_LED_init(PORTB,PORTB,PORTD);
	
	Driver_LPIT_init(LPIT0);
	
	DRIVER_LPIT_Callback(HanInterupt);
	
	//Driver_LPIT_timer0();
	Driver_LPIT_chain(LPIT0,24000000,LPIT0_IRQn);

	while (1){}
}

/* Function to handler interupt*/
static void HanInterupt(void)
{ 
    // Toggle LED
    GPIOB->PTOR |= (1 << 5);	  
}

