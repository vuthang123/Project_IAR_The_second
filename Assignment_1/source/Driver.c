#include "Driver.h"

/*BUTTON*/
static uint32_t *p32GPIOD_PDIR_REG  = (uint32_t*)GPIOD_PDIR_REG_ADD;
/*led*/
static uint32_t *p32GPIOB_PCOR_REG  = (uint32_t*)GPIOB_PCOR_REG_ADD;
static uint32_t *p32GPIOB_PSOR_REG  = (uint32_t*)GPIOB_PSOR_REG_ADD;

void Led_On(void)
{
	/*Clear register*/
	*p32GPIOB_PCOR_REG |= (1 << 5);
	
}
void Led_Off(void)
{   /*Set register*/
	*p32GPIOB_PSOR_REG |= (1 << 5);
}

uint32_t ReadPin_Button(uint32_t Pin)
{
	uint8_t status = 0;
	
	if ((*p32GPIOD_PDIR_REG & BUTTON_SW2) != 0)
	{
	  status = 1;
	}
	else
	{
	  status = 0;
	}
	return status;
}

void WritePin_Led(uint32_t status)
{
	if (status != 0)
	{
	  Led_On();
		  
	}
	else
	{
	  Led_Off();
	}
  
}
void Init_Led(void)
{
	uint32_t *p32PCC_PORTB_REG   = (uint32_t*)PCC_PORTB_EN_CLOCK;
	uint32_t *p32POTRB_PCR5_REG  = (uint32_t*)PORTB_PCR5_REG_ADD;
	uint32_t *p32GPIOB_PDDR_REG  = (uint32_t*)GPIOB_PDDR_REG_ADD;	
	uint32_t *p32GPIOB_PDOR_REG  = (uint32_t*)GPIOB_PDOR_REG_ADD;
	
	/*Enable Clock Port B */	
	*p32PCC_PORTB_REG |= 1 << 30U;
   
	/*Select GPIO */
	*p32POTRB_PCR5_REG |= (1 << 8U);

    /*Select Mode OUTPUT */
	*p32GPIOB_PDDR_REG |= (1 << 5U);
	
	/*Setup defaut*/
	*p32GPIOB_PDOR_REG |=  (1 << 5U);
}

void Button_Init(void)
{
	 uint32_t *p32PCC_PORTD_REG   = (uint32_t*)PCC_PORTD_EN_CLOCK;
	 uint32_t *p32POTRD_PCR3_REG  = (uint32_t*)PORTD_PCR3_REG_ADD;
	 uint32_t *p32GPIOD_PDDR_REG  = (uint32_t*)GPIOD_PDDR_REG_ADD;	
	 
	 /*Enable clock port D - SW2*/
	 *p32PCC_PORTD_REG  |=  (1 << 30U);
	
	 /*setup Goio CLEAR BIT FIELD*/
	 
	 *p32POTRD_PCR3_REG &= ~(0X700UL);
	 *p32POTRD_PCR3_REG |= (1 << 8U);

	 /*setup Pullup PS = 1 ,PE = 1 */
	 *p32POTRD_PCR3_REG &= ~(0X2UL);
	 *p32POTRD_PCR3_REG &= ~(0X1UL);
	 *p32POTRD_PCR3_REG |= (1 << 0) | (1 << 1);
	
    /*setup Input*/
	 *p32GPIOD_PDDR_REG &= ~BUTTON_SW2;
}

void Delay(int n)
{
    uint32_t i;
    for (i = 0; i < n; i++)
    {
        __asm("nop");
    }
}