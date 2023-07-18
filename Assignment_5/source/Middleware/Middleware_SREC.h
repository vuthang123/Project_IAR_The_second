#ifndef Middleware_SREC_H_
#define Middleware_SREC_H_

#include "stdint.h"

#define MAX_DATA_LENGTH                   (255U)

typedef struct
{
    uint32_t u32Address;
    uint32_t u32Data_length;
    uint8_t  u8Data[MAX_DATA_LENGTH];
}Middleware_Srec_Pasre_data_line_struct_t;

typedef enum
{
    MIDDLEWARE_SREC_PASRE_STATE_START          = 0U,
    MIDDLEWARE_SREC_PASRE_STATE_HANDLE         = 1U,
    MIDDLEWARE_SREC_PASRE_STATE_COMPLETE       = 2U,
    MIDDLEWARE_SREC_PASRE_STATE_FAIL           = 3U,
    MIDDLEWARE_SREC_PASRE_STATE_UNKNOWN        = 0xFF,
}Middleware_Srec_Pasre_status;

typedef enum
{
    SREC_FILE    = 1,
    UNKNOWN_FILE = 0xFF
}Middleware_Srec_Pasre_Filetype;
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
uint16_t Check_length_str(uint8_t *str);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
Middleware_Srec_Pasre_status Middleware_SREC_Parse(uint8_t * input_data,Middleware_Srec_Pasre_data_line_struct_t *out_data);
#endif /*Middleware_SREC_H_*/