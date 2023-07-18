#include "HAL_CLOCK.h"
#include "HAL_PORT.h"
#include "HAL_UART.h" 
#include "MKE16Z4.h"

#define PCC_PORTB_CGC 			(1<<30)
#define PORTB_TRANSMITER        (1U)
#define PORTB_RECEIVER        (0U)
/*******************************************************************************
 * Static global
 ******************************************************************************/
static uart_conf_stuct_t uart = {8,0,0,0,115200,0};

/**
 * @func    Initialization driver call back
 * @brief   Function Initialization for Uart
 * @param   None
 * @return  None 
 **/
static void (*Driver_Uart_Call_back)(uint8_t);
/**
 * @func    Enable port uart enable clock 
 * @brief   Driver uart enable clock 
 * @param   None
 * @return  None 
 **/
static void Driver_Uart_Port_Enbale_Clock();
/**
 * @func    Calculate baudrate
 * @brief   Function Baudrate for Uart
 * @param   None
 * @return  None 
 **/
static void Driver_Uart_Baudrate();
/**
 * @func    Initialization on UART
 * @brief   Function Initialization for Uart
 * @param   None
 * @return  None 
 **/
void Driver_UART_Init()
{
	
    Driver_Uart_Port_Enbale_Clock();
	
	HALLPUART_Disable_Tx_Rx(LPUART0);
	
	HALLPUART_Data_bit(LPUART0,&uart);
	
	HALLPUART_ParityType(LPUART0,&uart);
	
	HALUART_Sortbyte(LPUART0,&uart);
	
	HALUART_Not_Inversion(LPUART0);
	
	HALUART_Stopbit(LPUART0);
	
	//Driver_Uart_Baudrate()
	      /*Configure the baud rate BAUD[SBR, OSR]*/
	//LPUART0->BAUD &= ~LPUART_BAUD_M10(1);
    LPUART0->BAUD = (LPUART0->BAUD & (~LPUART_BAUD_SBR_MASK))|LPUART_BAUD_SBR(26);  
    LPUART0->BAUD = (LPUART0->BAUD & (~LPUART_BAUD_OSR_MASK)) | LPUART_BAUD_OSR(7);

    HALLPUART_Ennable_Tx_Rx(LPUART0);
    
    HALUART_Enable_Rx_IT(LPUART0);
     
}
/**
 * @func    Hander data for driver
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_Uart_Rx()
{       
    HAL_UART_Callback(Driver_Uart_Call_back);
}
/**
 * @func    Transmission on App
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_LPUART0_Transmission_One_byte(uint8_t u8Data)
{
    /* Wait Data Register is Empty */
	  while((LPUART0->STAT & LPUART_STAT_TDRE_MASK) == 0)
	  {
			
	  }
    /* Write to Data Register */
    LPUART0->DATA = u8Data;
	
}
/**
 * @func    Transmission multi byte on app
 * @brief   Function Initialization for Queue and Uart
 * @param   u8Data
 * @param   lenght
 * @return  None 
 **/
void Driver_LPUART0_Transmission_Milt_byte(uint8_t *u8Data ,uint8_t lenght)
{
    uint8_t i =0;
    
    for(i=0;i<lenght;i++)
    {
        Driver_LPUART0_Transmission_One_byte(*(u8Data+i));
    }
}
/**
 * @func    driver Ennable uart
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
static void Driver_Uart_Port_Enbale_Clock()
{
	 /*Enable the clock for the PORT associated with the LPUART pins you want to use*/
	 HALCLOCK_Enableclock_peripheral(PCC_PORTB,PCC_PORTB_CGC);
	 /*Enble Transmitter felid mux in PORT */
	 HAL_PORT_Select_Mode(PORTB,PORTB_TRANSMITER,Mode_Alternative_2);
	 /*Enble Rceiver felid mux in PORT */
	 HAL_PORT_Select_Mode(PORTB,PORTB_RECEIVER,Mode_Alternative_2);
	 
	 HALCLOCK_FastIRC_FIRC(SCG,PCC);
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
static uint32_t uart_baudrate_gen(uint32_t clock, uint16_t sbr, uint8_t osr)
{
    uint32_t baudrate = 0;
	
    baudrate = ((clock)/((sbr)*((osr) + 1)));
	
    return baudrate;
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
static uint32_t uart_get_sbr(uint32_t clock,uart_conf_stuct_t *Baud , uint8_t osr)
{
    uint16_t sbr = 0;
	
    sbr = ((clock) / ((Baud->Baud_Rate)* ((osr) + 1)));
	
    return sbr;
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
static uint32_t baudrate_absolute_value(uint32_t temp_baud, uart_conf_stuct_t *Baud)
{
    uint32_t delta = 0;
	
    int32_t abs = 0;
	
    abs = Baud->Baud_Rate - temp_baud;
	if(abs >= 0)
    {
        delta = abs;
    }
    else
    {
        delta = -abs;
    }
	
    return delta;
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
static void Driver_Uart_Baudrate()
{
	uint8_t  osr = 0;
    uint16_t sbr = 0;
    uint32_t baud = 0;
    uint32_t Compare = 0;

    uint32_t Min_compare = 0xFFFFFFFF;
    uint32_t minOsr = 0;
    uint16_t minSbr = 0;
	uint32_t minOsr_done = 0;
	
    for (osr = 4; osr<= 32; ++osr)
    {
        /*get value srb current*/
		sbr = uart_get_sbr(24000000, &uart, osr);
        /*get value baudrate current*/
		baud = uart_baudrate_gen(24000000, sbr, osr);
        /*Compare*/
		Compare = baudrate_absolute_value(baud, &uart);
		/*get value min for Osr and sbr */
        if (Compare < Min_compare)
        {
            Min_compare = Compare;
            minOsr = osr;
            minSbr = sbr;
        }
		
    }    
	minOsr_done = minSbr & 0xFF;
	
	HALUART_Baurate(LPUART0,minOsr_done,minOsr);
}
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Driver_Uart_Hander_Data(void(*Function_call)(uint8_t))
{
     Driver_Uart_Call_back = Function_call;
}
