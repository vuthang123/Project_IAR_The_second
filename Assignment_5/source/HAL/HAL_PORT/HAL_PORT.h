#ifndef HAL_PORT_H
#define HAL_PORT_H

#include "stdint.h"
#include "MKE16Z4.h"

typedef enum {
      HAL_PORT_SUCCESS = 0,
      HAL_PORT_FAIL
}HAL_PORT_Erorr_E;

typedef enum 
{
      Mode_Analog = 0u, /*000 Pin disabled (Alternative 0) (analog)*/
      Mode_Gpio   = 1u, /*001 Alternative 1 (GPIO).*/
      Mode_Alternative_2 = 2u,/*010 Alternative 2 (chip-specific).*/
      Mode_Alternative_3 = 3u,/*011 Alternative 3 (chip-specific).*/
      Mode_Alternative_4 = 4u,/*100 Alternative 4 (chip-specific).*/
      Mode_Alternative_5 = 5u,/*101 Alternative 5 (chip-specific).*/
      Mode_Alternative_6 = 6u,/*110 Alternative 6 (chip-specific).*/
      Mode_Alternative_7 = 7u,/*111 Alternative 7 (chip-specific).*/
      
}Mux_type;

typedef enum 
{
    PULL_DISABLE = 0U,
    PULL_ENABLE  
}Pull_ENABLE_Type_E;

typedef enum 
{
    PULL_DOWN = 0U,
    PULL_UP   
}Pull_SELECT_Type_E;

/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
HAL_PORT_Erorr_E HAL_PORT_Select_Mode(PORT_Type* PORTx,uint32_t Select_Pin,Mux_type Select_Mode_IO);
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
HAL_PORT_Erorr_E HAL_PORT_Select_Pull_Enable(PORT_Type* PORTx,uint32_t Select_Pin,Pull_ENABLE_Type_E Select_Mode_IO);
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
HAL_PORT_Erorr_E HAL_PORT_Select_Pull_Mode(PORT_Type* PORTx,uint32_t Select_Pin,Pull_SELECT_Type_E Select_Mode_IO);

#endif /*HAL_PORT_H*/