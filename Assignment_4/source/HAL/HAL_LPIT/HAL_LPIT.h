#ifndef HAL_LPIT_H
#define HAL_LPIT_H
#include "MKE16Z4.h"

typedef enum{
	  channel_0 =0,
	  channel_1 =1,
	  channel_2 =2,
	  channel_3 =3,
}chanal_number;

typedef struct {
	  chanal_number number0;
	  chanal_number number1;
}chanal_number_s;

//void (*hal_callback)(void);
//void HAL_LPIT_Callback((*hal_callback)(void));
void HAL_LPIT_Callback(void (*sfun)(void));

void Enble_CLOCK_LPIT_FIRC(SCG_Type *base_clock,PCC_Type* base_clock_peripheral);
void Driver_LPIT_init(LPIT_Type* Base_LPIT);
void Setup_timer(LPIT_Type* Base_LPIT);
void Select_mode(LPIT_Type* Base_LPIT,chanal_number_s *num);
void One_timer(LPIT_Type* Base_LPIT,chanal_number_s *num,uint32_t clock,IRQn_Type IRQ);
void Chaning_timer(LPIT_Type* Base_LPIT,chanal_number_s *num,uint32_t clock,IRQn_Type IRQ);

#endif /*HAL_LPIT*/