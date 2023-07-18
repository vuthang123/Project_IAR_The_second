#ifndef HAL_CLOCK_H_
#define HAL_CLOCK_H_

#include "stdint.h"
//#include "MKE16Z4.h"

typedef enum 
{
	HAL_SUCCESS = 0,
	HAL_FAIL
}HAL_RETURN_E;

typedef enum
{
   PCC_FLASH_INDEX                          =32,
   PCC_MSCAN0_INDEX                         =36,
   PCC_LPSPI0_INDEX                         =44,
   PCC_CRC_INDEX                            =50,
   PCC_PDB0_INDEX                           =54,
   PCC_LPIT0_INDEX                          =55,
   PCC_FLEXTMR0_INDEX                       =56,
   PCC_FLEXTMR1_INDEX                       =57,
   PCC_ADC0_INDEX                           =59,
   PCC_RTC_INDEX                            =61,
   PCC_LPTMR0_INDEX                         =64,
   PCC_TSI_INDEX                            =69,
   PCC_PORTA_INDEX                          =73,
   PCC_PORTB_INDEX                          =74,
   PCC_PORTC_INDEX                          =75,
   PCC_PORTD_INDEX                          =76,
   PCC_PORTE_INDEX                          =77,
   PCC_PWT_INDEX                            =86,
   PCC_EWM_INDEX                            =97,
   PCC_LPI2C0_INDEX                         =102,
   PCC_LPUART0_INDEX                        =106,
   PCC_LPUART1_INDEX                        =107,
   PCC_LPUART2_INDEX                        =108,
   PCC_CMP0_INDEX                           =115
}CLOCK_SYS_register_name_e;

/*******************************************************************************
 * API
 ******************************************************************************/

HAL_RETURN_E HAL_CLOCK_Init(CLOCK_SYS_register_name_e register_selected, uint32_t Select);

void Delay(int n);
#endif /*HAL_CLOCK_H_*/
