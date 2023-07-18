#ifndef HAL_CLOCK_H_
#define HAL_CLOCK_H_

#include "stdint.h"
//#include "MKE16Z4.h"
#include "MKE16Z4.h"

typedef enum 
{
    HAL_SUCCESS = 0,
    HAL_FAIL
}HALCLOCK_Status;

typedef enum
{

 PCC_FLASH                          = 32,
 PCC_MSCAN0                         = 36,
 PCC_LPSPI0                         = 44,
 PCC_CRC                            = 50,
 PCC_PDB0                           = 54,
 PCC_LPIT0                          = 55,
 PCC_FLEXTMR0                       = 56,
 PCC_FLEXTMR1                       = 57,
 PCC_ADC0                           = 59,
 PCC_RTC                            = 61,
 PCC_LPTMR0                         = 64,
 PCC_TSI                            = 69,
 PCC_PORTA                          = 73,
 PCC_PORTB                          = 74,
 PCC_PORTC                          = 75,
 PCC_PORTD                          = 76,
 PCC_PORTE                          = 77,
 PCC_PWT                            = 86,
 PCC_EWM                            = 97,
 PCC_LPI2C0                         = 102,
 PCC_LPUART0                        = 106,
 PCC_LPUART1                        = 107,
 PCC_LPUART2                        = 108,
 PCC_CMP0                           = 115,

}Clock_peripheral_e;


/*******************************************************************************
 * API
 ******************************************************************************/
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
HALCLOCK_Status HALCLOCK_Enableclock_peripheral(Clock_peripheral_e Clock_peripheral, uint32_t Select);
/**
 * @func    Initialization on application
 * @brief   Function Initialization for Queue and Uart
 * @param   None
 * @return  None 
 **/
void HALCLOCK_FastIRC_FIRC(SCG_Type* scg_reg  ,PCC_Type* pcc_reg);

#endif /*HAL_CLOCK_H_*/
/*******************************************************************************
 * EOF
 ******************************************************************************/