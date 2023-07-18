#ifndef Middleware_QUEUE_H_
#define Middleware_QUEUE_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_LINE         4UL
#define MAX_CAPACITY     255UL

typedef struct CircularQueue 
{
    uint8_t queue[MAX_LINE][MAX_CAPACITY];
    uint8_t front;
    uint8_t rear;
    uint8_t size;
    
}CircularQueue_struct_t;
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_QueueInit();
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
bool Middleware_Queue_Empty();
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
bool isFull();
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
uint8_t *Middleware_Queue_Popdata();
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_Queue_Dequeue();
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_Queue_PushData(uint8_t Data);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_Queue_Enqueue(void);

#endif /*Middleware_QUEUE_H_*/