#include <stdint.h>
#include "Middleware_SREC.h"



static uint32_t u8Counter_Error_String = 0;

/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
static uint8_t Characters_to_Hex(const uint8_t character);
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
static uint8_t Characters_to_Hex(const uint8_t character)
{
    uint8_t u8Flag = 0xFF;

    if(('0' <= character)&&(character <= '9'))
    {
        u8Flag = character - '0';
    }
    else if('A'<=character && character <='F')
    {
        u8Flag = character - 'A' +10;
    }
    else
    {
        u8Counter_Error_String ++;
    }

    return u8Flag;
}

/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
Middleware_Srec_Pasre_status Middleware_SREC_Parse(uint8_t * u8Input_data,Middleware_Srec_Pasre_data_line_struct_t *s_Out_data)
{
    Middleware_Srec_Pasre_status parse_status = MIDDLEWARE_SREC_PASRE_STATE_UNKNOWN;
    
    uint8_t  u8Srec_type = 0;
    uint8_t  u8Byte_u8Count = 0;
    uint8_t  u8Check_sum = 0;
    uint32_t u32Address = 0;
    uint8_t  u8Byte_Address = 0;
    uint16_t u8Offset = 4;        
    uint8_t  u8Buffer =0;
    uint8_t  u8Index = 0;
    uint16_t u8Count = 0;
    //s_Out_data->data_length=0;

    if('S' == u8Input_data[0])
    {
        u8Srec_type = Characters_to_Hex(u8Input_data[1]);
        /***********Calculate byteu8Count value******************/
        u8Byte_u8Count = (Characters_to_Hex(u8Input_data[2]) << 4) | (Characters_to_Hex(u8Input_data[3]));
        u8Check_sum = u8Byte_u8Count;
        switch(u8Srec_type)
        {
            case 0:
            {
                parse_status = MIDDLEWARE_SREC_PASRE_STATE_START;
                u8Byte_Address = 2U;
                break;
            }
            case 1:
            case 2:
            case 3:
            {
                  u8Byte_Address = u8Srec_type +1;
                  parse_status = MIDDLEWARE_SREC_PASRE_STATE_HANDLE;
                
                break;
            }
            case 4:
            case 5:
            case 6:
            {
				  parse_status = MIDDLEWARE_SREC_PASRE_STATE_FAIL;
				  break;
            }
            case 7:
            case 8:
            case 9:
            {
                u8Byte_Address = 11- u8Srec_type;
                parse_status = MIDDLEWARE_SREC_PASRE_STATE_COMPLETE;
                break;
            }
            default:
            {
                parse_status = MIDDLEWARE_SREC_PASRE_STATE_FAIL;
                break;
            }
        }
        if(parse_status != MIDDLEWARE_SREC_PASRE_STATE_FAIL)
        {
            for(u8Index =0; u8Index < u8Byte_Address; u8Index++)
            {
                u8Buffer = (Characters_to_Hex(u8Input_data[u8Offset]) << 4) | (Characters_to_Hex(u8Input_data[u8Offset+1]));
                u32Address = u32Address << 8 | u8Buffer;
                u8Check_sum += u8Buffer;
                u8Offset += 2;
            }
            s_Out_data->u32Address = u32Address;
            
            //u8Count = 0;
            
            while(u8Input_data[u8Count] != '\r')
            {
                u8Count++;
            }
            u8Count = u8Count - 4;
            
            if((u8Byte_u8Count << 1) != u8Count )
            {
                parse_status = MIDDLEWARE_SREC_PASRE_STATE_FAIL;
            }
            
            s_Out_data->u32Data_length = u8Byte_u8Count - 1- u8Byte_Address;
            
            for(u8Index =0; u8Index < (s_Out_data->u32Data_length); u8Index++)
            {
                u8Buffer = (Characters_to_Hex(u8Input_data[u8Offset]) << 4) | (Characters_to_Hex(u8Input_data[u8Offset+1]));
                s_Out_data->u8Data[u8Index] = u8Buffer;
                u8Check_sum += u8Buffer;
                u8Offset += 2;
            }
            
            u8Check_sum += (Characters_to_Hex(u8Input_data[u8Offset]) << 4) | (Characters_to_Hex(u8Input_data[u8Offset+1]));

            if((0xFF != u8Check_sum) || (0 != u8Counter_Error_String))
            {
                parse_status = MIDDLEWARE_SREC_PASRE_STATE_FAIL;
            }
        }
    }
    else
    {
        parse_status = MIDDLEWARE_SREC_PASRE_STATE_FAIL;
    }

    return parse_status;
}
/**
 * @func    Application_handle_rx_data_intterupt
 * @brief   Function to handler interupt receiver
 * @param   u8Data : Reciver Interupt Data
 * @return  None 
 **/
uint16_t Check_length_str(uint8_t *str)
{
    uint16_t length = 1;
    while(13 != str[length])
    {
        length++;
    }

    	return length;
}
