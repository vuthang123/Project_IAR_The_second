#include "Middleware_QUEUE.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>


static CircularQueue_struct_t q;

static uint8_t index =0;
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_QueueInit() 
{
    q.front = 0;
    q.rear = 0;
    q.size = 0;
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
bool Middleware_Queue_Empty() 
{
    uint8_t flag = false;
    if(q.front == q.rear && q.size == 0)
    {
        flag = true;
    }
    return flag;
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
bool Middleware_Queue_Full() 
{
    uint8_t flag = false;
    if(q.front == q.rear && q.size == MAX_LINE)
    {
        flag = true;
    }
    return flag;
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_Queue_PushData(uint8_t data)
{
    q.queue[q.rear][index] = data; 
    index++;
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_Queue_Enqueue(void)
{
    if(!Middleware_Queue_Full())
    {
        q.rear =  (q.rear + 1) % MAX_LINE;
        q.size++;
        index = 0;
    }

}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
uint8_t *Middleware_Queue_Popdata()
{
    return q.queue[q.front];
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
void Middleware_Queue_Dequeue()
{
      if(!Middleware_Queue_Empty())
      {
         q.front = (q.front + 1) % MAX_LINE;
         q.size--;
      }

}
