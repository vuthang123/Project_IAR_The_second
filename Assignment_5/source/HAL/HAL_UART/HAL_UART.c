#include "HAL_UART.h"
#include "HAL_CLOCK.h"
#include "HAL_PORT.h"
#include "stdbool.h"
#include "stdint.h"
#include "stdio.h"
#include "MKE16Z4.h"
/*static global */
static void (*HAL_UART_sfun_pointer)(uint8_t);

/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALLPUART_Disable_Tx_Rx(LPUART_Type *uart_reg)
{
	  /*Disable TX RX*/
    uart_reg->CTRL &= ~LPUART_CTRL_TE_MASK;
    uart_reg->CTRL &= ~LPUART_CTRL_RE_MASK;
	  
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
/*Enable the receiver and/or transmitter */
void HALLPUART_Ennable_Tx_Rx(LPUART_Type *uart_reg)
{
    uart_reg->CTRL |= LPUART_CTRL_TE_MASK;
    uart_reg->CTRL |= LPUART_CTRL_RE_MASK;

}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALLPUART_Data_bit(LPUART_Type *uart_reg,uart_conf_stuct_t* base)
{
	/*  Number of data bits */
    switch (base->Con_fig_bits)
    {
	  case 1:
	  case 2:
	  case 3:
	  case 4:
	  case 5:
	  case 6:
	  case 7:
		  uart_reg->CTRL |= LPUART_CTRL_M_MASK;
		  uart_reg->BAUD &= ~LPUART_BAUD_M10_MASK;
	  case 8:
		  uart_reg->CTRL &= ~LPUART_CTRL_M_MASK;
		  uart_reg->CTRL &= ~LPUART_CTRL_M7_MASK;
		  uart_reg->BAUD &= ~LPUART_BAUD_M10(1);
		  break;

	  case 9:
		  uart_reg->CTRL |= LPUART_CTRL_M_MASK;
		  uart_reg->CTRL &= ~LPUART_CTRL_M7_MASK;
		  uart_reg->BAUD &= ~LPUART_BAUD_M10_MASK;
		  break;

	  case 10:
		  uart_reg->CTRL &= ~LPUART_CTRL_M7_MASK;
		  uart_reg->BAUD |=  LPUART_BAUD_M10_MASK;
		  break;
    }
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
/*Parity ENABLE and parity EVEN*/
void HALLPUART_ParityType(LPUART_Type *uart_reg,uart_conf_stuct_t* base)
{
	uart_reg->CTRL |= base->parityEnable ? LPUART_CTRL_PE(1) : LPUART_CTRL_PE(0);
    uart_reg->CTRL |= base->parityType   ? LPUART_CTRL_PT(1) : LPUART_CTRL_PT(0);

}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALUART_Stopbit(LPUART_Type *uart_reg)
{
	  /*Configure number of Stop bit BAUD[SBNS]*/
	  uart_reg->BAUD &=~LPUART_BAUD_SBNS_MASK;
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALUART_Enable_Rx_IT(LPUART_Type *uart_reg)
{    
    uart_reg->CTRL |= LPUART_CTRL_RIE_MASK;
    NVIC_ClearPendingIRQ(LPUART0_IRQn);
    NVIC_EnableIRQ(LPUART0_IRQn);
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALUART_Sortbyte(LPUART_Type *uart_reg,uart_conf_stuct_t* base)
{
	/* MSB or LSB first */
    uart_reg->STAT &= ~LPUART_STAT_MSBF_MASK;
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALUART_Not_Inversion(LPUART_Type *uart_reg)
{
	/*Data polarity STAT[RXINV] and CTRL[TXINV]*/
    uart_reg->STAT &= ~LPUART_STAT_RXINV_MASK;
    uart_reg->CTRL &= ~LPUART_CTRL_TXINV_MASK;
 
}

/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void LPUART0_IRQHandler()
{
    uint8_t receiData = 0;
    
    if(LPUART0->STAT & LPUART_STAT_RDRF_MASK)
    {
        receiData =  LPUART0->DATA;
        if(HAL_UART_sfun_pointer!= NULL)
        {
            HAL_UART_sfun_pointer(receiData);
        }
    }
}

void HAL_UART_Callback(void (*sfun)(uint8_t))
{
    HAL_UART_sfun_pointer = sfun;
}

void HALUART_Baurate(LPUART_Type *uart_reg ,uint32_t minOsr ,uint32_t min_sbr)
{
      /*Configure the baud rate BAUD[SBR, OSR]*/    
    LPUART0->BAUD = (LPUART0->BAUD & (~LPUART_BAUD_SBR_MASK))|LPUART_BAUD_SBR(minOsr);  
    LPUART0->BAUD = (LPUART0->BAUD & (~LPUART_BAUD_OSR_MASK)) | LPUART_BAUD_OSR(min_sbr);	  
}
