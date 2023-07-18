#ifndef _UART_H_
#define _UART_H_

#include "stdint.h"
#include "stdbool.h"
#include "MKE16Z4.h"

typedef struct uart_conf
{
    uint8_t Con_fig_bits;    /* Number of data bits */
    bool parityEnable;       /* Parity enable */
    uint8_t parityType;      /* Parity type */
    bool select_sort_byte;   /* MSB or LSB first */  
    uint32_t Baud_Rate;      /* Baud rate */  
    uint8_t Select_Tx_Rx;    /* Enable transmitter or receiver or both */
	
}uart_conf_stuct_t;

/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALUART_Baurate(LPUART_Type *uart_reg ,uint32_t minOsr ,uint32_t min_sbr);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HAL_UART_Callback(void (*sfun)(uint8_t));
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALLPUART_Transmit(uint8_t u8Data);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALLPUART_Ennable_Tx_Rx(LPUART_Type *uart_reg);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALLPUART_Disable_Tx_Rx(LPUART_Type *uart_reg);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALLPUART_ENABLE_RECEI_interrupt(LPUART_Type *uart_reg);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALLPUART_Data_bit(LPUART_Type *uart_reg,uart_conf_stuct_t* base);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALLPUART_ParityType(LPUART_Type *uart_reg,uart_conf_stuct_t* base);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALUART_Enable_Rx_IT(LPUART_Type *uart_reg);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALUART_Stopbit(LPUART_Type *uart_reg);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALUART_Sortbyte(LPUART_Type *uart_reg,uart_conf_stuct_t* base);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void HALUART_Not_Inversion(LPUART_Type *uart_reg);

#endif /*_UART_H_*/
/*******************************************************************************
 * EOF
 ******************************************************************************/