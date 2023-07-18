#include "HAL_UART.h"
#include "HAL_CLOCK.h"
#include "HAL_PORT.h"
#include "stdint.h"
void UART_init();
void UART_port(void)
{
	/*Enable the clock for the PORT associated with the LPUART pins you want to use*/
	PCC->CLKCFG[PCC_PORTB_INDEX] |= PCC_CLKCFG_CGC(1);

	PORTB->PCR[1] = PORT_PCR_MUX(2);
	
	PORTB->PCR[0] |= PORT_PCR_MUX(2);
	/*Configure the divider and enable the clock source to be used for the LPUART*/
	SCG->FIRCDIV |=  SCG_FIRCDIV_FIRCDIV2(2);
	/*Select clock source and enable clock for LPUART module*/
	PCC->CLKCFG[PCC_LPUART0_INDEX] |= PCC_CLKCFG_PCS(3)|PCC_CLKCFG_CGC(1);
	
}
void UART_BAUDRATE()
{
	/*Configure the baud rate BAUD[SBR, OSR]*/	
	LPUART0->BAUD &=~LPUART_BAUD_SBR_MASK;
	LPUART0->BAUD |= LPUART_BAUD_SBR(26);
	LPUART0->BAUD &=~LPUART_BAUD_OSR_MASK;
	LPUART0->BAUD |= LPUART_BAUD_OSR(7);
	
}
void UART_CONTROL_REGISTER()
{
	/*Disable TX RX*/
	LPUART0->CTRL &= ~LPUART_CTRL_TE_MASK;
	LPUART0->CTRL &= ~LPUART_CTRL_RE_MASK;
	/*Number of data  8 bits*/
	LPUART0->CTRL &=~ LPUART_CTRL_M_MASK;
	//LPUART0->CTRL &=~ LPUART_CTRL_M7_MASK;
	
	//LPUART0->BAUD &= ~LPUART_BAUD_M10(1);
	/*Parity ENABLE and parity EVEN*/
	LPUART0->CTRL &= ~LPUART_CTRL_PE_MASK;
	//LPUART0->CTRL |= LPUART_CTRL_PE(1);
	
	//LPUART0->CTRL &= ~LPUART_CTRL_PT(1);
	/* LSB */
	LPUART0->STAT &= ~LPUART_STAT_MSBF_MASK;
	/*Data polarity STAT[RXINV] and CTRL[TXINV]*/
	LPUART0->STAT &= ~LPUART_STAT_RXINV_MASK;
	LPUART0->CTRL &= ~LPUART_CTRL_TXINV_MASK;
	/*Configure number of Stop bit BAUD[SBNS]*/
	LPUART0->BAUD &= ~LPUART_BAUD_SBNS_MASK;
}


void UART_init()
{	
	UART_port();
	
	UART_CONTROL_REGISTER();
	UART_BAUDRATE();
	/*Enable the receiver and/or transmitter */
	LPUART0->CTRL |= LPUART_CTRL_RE(1);
	LPUART0->CTRL |= LPUART_CTRL_TE(1);
}
void UART0_Transmit(uint8_t *u8Data)
{
    /* Wait Data Register is Empty */
    while( (LPUART0->STAT & LPUART_STAT_TDRE_MASK) == 0 );
     
    /* Write to Data Register */
    LPUART0->DATA = *u8Data;
    
    /*wait transmission activity complete*/
    while ((LPUART0->STAT & LPUART_STAT_TC_MASK) == 0);

}
//uint8_t UART0_Receive(void)
//{
//     /* Wait Data Register is full */
//    while( ((LPUART0->STAT & LPUART_STAT_RDRF_MASK) == 0) );
//    
//    /* Read and Return Data Register */
//    return LPUART0->DATA;
//    
//}

