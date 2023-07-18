#ifndef DRIVER_LPIT_H
#define DRIVER_LPIT_H
#include "MKE16Z4.h"
#include "HAL_LPIT.h"

//typedef void (*dirver_callback)(void);
//void DRIVER_LPIT_Callback((*drv_callback)(void));
void DRIVER_LPIT_Callback(void (*fun)(void));
//void LPIT_Config(LPIT_Type* Base_LPIT,uint32_t clock,IRQn_Type IRQ);
void Driver_LPIT_init(LPIT_Type* Base_LPIT);
void Driver_LPIT_timer0(LPIT_Type* Base_LPIT,uint32_t clock,IRQn_Type IRQ);
void Driver_LPIT_chain(LPIT_Type* Base_LPIT,uint32_t clock,IRQn_Type IRQ);

#endif /*DRIVER_LPIT_H*/