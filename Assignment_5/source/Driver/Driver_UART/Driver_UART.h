#ifndef DRIVER_UART_H
#define DRIVER_UART_H

#include "MKE16Z4.h"

/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Middleware_UART_Init();
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_Uart_Hander_Data(void(*Function_call)(uint8_t));
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_Uart_Rx();
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_LPUART0_Transmission_Milt_byte(uint8_t *u8Data ,uint8_t lenght);
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_LPUART0_Transmission_One_byte(uint8_t u8Data);
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_UART_Init();      
      
#endif /*DRIVER_UART_H*/
/*******************************************************************************
 * EOF
 ******************************************************************************/