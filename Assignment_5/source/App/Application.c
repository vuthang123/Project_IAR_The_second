#include "Driver_Led.h"
#include "Driver_UART.h"
#include "Middleware_QUEUE.h"
#include "Middleware_SREC.h"
#include "MKE16Z4.h"
#include "stdint.h"
#include "stdbool.h"
#include "stdio.h"

#define NEW_LINE_CHAREACTER               (10UL)
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Application_Init(void);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
static void Application_handle_receiver_data_intterupt(uint8_t data);

/*******************************************************************************
 * Code
 ******************************************************************************/
uint8_t UART_command(void);
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void Application_Init(void)
{    /*Initialization for Queue */
    Middleware_QueueInit();
    /*Initialization for Uart */
    Driver_UART_Init();
}


int main()
{
    /*Initialization input for queue */
    uint8_t *u8Input_Data_Queue = NULL;
    /*Initialization Buffer when receiver success */
	uint8_t *u8u8Sucess = ">>\r\n";
    /*Initialization Buffer when receiver error */
	uint8_t u8Error[] = {"Error\r\n"};
    /*Initialization for Srec parse data line */
    Middleware_Srec_Pasre_data_line_struct_t s_Output = {0,0,{0}};
    /*Initialization state for Srec parse data line */
    Middleware_Srec_Pasre_status s_Status =  MIDDLEWARE_SREC_PASRE_STATE_UNKNOWN;
    /*Initialization state for queue and uart */
    Application_Init();
    /*Handler Data while there interrupt */
    Driver_Uart_Hander_Data(Application_handle_receiver_data_intterupt);
    /*hander interrupt from Hal uart*/
    Driver_Uart_Rx();
    while(1)
    {     
		 
          if (Middleware_Queue_Empty() == false)
          {
                  u8Input_Data_Queue = Middleware_Queue_Popdata();
				  
                  s_Status = Middleware_SREC_Parse(u8Input_Data_Queue,&s_Output);
                  Middleware_Queue_Dequeue();
				  Driver_LPUART0_Transmission_One_byte(0X3E);
                  switch(s_Status)
                  {
                      case MIDDLEWARE_SREC_PASRE_STATE_START:          
                      {
                           Driver_LPUART0_Transmission_Milt_byte(u8u8Sucess,Check_length_str(u8u8Sucess));
						   Driver_LPUART0_Transmission_One_byte(NEW_LINE_CHAREACTER);
                           break;
                            
                      }
                      case MIDDLEWARE_SREC_PASRE_STATE_HANDLE:          
                      {
                           Driver_LPUART0_Transmission_Milt_byte(u8u8Sucess,Check_length_str(u8u8Sucess));
                           Driver_LPUART0_Transmission_One_byte(NEW_LINE_CHAREACTER);
                           break;
                            
                      }
                      case MIDDLEWARE_SREC_PASRE_STATE_COMPLETE:
                      {
                          Driver_LPUART0_Transmission_Milt_byte(u8u8Sucess,Check_length_str(u8u8Sucess));
                           Driver_LPUART0_Transmission_One_byte(NEW_LINE_CHAREACTER);
                          break;
                      }
                      case MIDDLEWARE_SREC_PASRE_STATE_FAIL:
                      {
                           Driver_LPUART0_Transmission_Milt_byte(u8Error,Check_length_str(u8Error));
                           Driver_LPUART0_Transmission_One_byte(NEW_LINE_CHAREACTER);
                           break;
                      }
                  }   
          }
}
}
uint8_t UART_command(void)
{
    uint8_t command;
     /* Disable interrupt UART, using poling */
    NVIC_DisableIRQ(LPUART0_IRQn);
    while(0 == ((LPUART0->STAT) & (LPUART_STAT_RDRF_MASK)));
    command = LPUART0->DATA;
    /* enable interrupt UART */
    NVIC_EnableIRQ(LPUART0_IRQn);
    return command;
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Application_handle_receiver_data_intterupt(uint8_t u8Data)
{
    Middleware_Queue_PushData(u8Data);
	
    if (u8Data == '\n')
    {
         Middleware_Queue_Enqueue();  
    }
  
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
