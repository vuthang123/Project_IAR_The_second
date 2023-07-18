#include "HAL_CLOCK.h"

/**
  * @brief  Initialization Clock port  
  * @param  register_selected:  to select reg Initialition 
  * @param  Select: specifies pin select
  * @retval 0 : SUCCESS
			1 : ERROR
  */
HAL_RETURN_E HAL_CLOCK_Init(CLOCK_SYS_register_name_e register_selected, uint32_t Select)
{
      PCC_Type2 *Types = PCC2;
	  HAL_RETURN_E ret = HAL_SUCCESS;
	  
	  switch(register_selected)
	  {
	  		case PCC_FLASH_INDEX :
		    {	
				 Types->CLKCFG[PCC_FLASH_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_FLASH_INDEX] |=  (Select);
				 break;
			}
	  		case PCC_MSCAN0_INDEX :
		    		    {	
				 Types->CLKCFG[PCC_MSCAN0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_MSCAN0_INDEX] |=  (Select);
				 break;
			}
			case PCC_LPSPI0_INDEX :
					    {	
				 Types->CLKCFG[PCC_LPSPI0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPSPI0_INDEX] |=  (Select);
				 break;
			}
		    case PCC_CRC_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_CRC_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_CRC_INDEX] |=  (Select);
				 break;
			}
			case PCC_PDB0_INDEX :
			{	
				 Types->CLKCFG[PCC_PDB0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PDB0_INDEX] |=  (Select);
				 break;
			}
			case PCC_LPIT0_INDEX :
					    {	
				 Types->CLKCFG[PCC_LPIT0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPIT0_INDEX] |=  (Select);
				 break;
			}
			case PCC_FLEXTMR0_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_FLEXTMR0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_FLEXTMR0_INDEX] |=  (Select);
				 break;
			}
			case PCC_FLEXTMR1_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_FLEXTMR1_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_FLEXTMR1_INDEX] |=  (Select);
				 break;
			}
				  
			case PCC_ADC0_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_ADC0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_ADC0_INDEX] |=  (Select);
				 break;
			}
			case PCC_RTC_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_RTC_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_RTC_INDEX] |=  (Select);
				 break;
			}
			case PCC_LPTMR0_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_LPTMR0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPTMR0_INDEX] |=  (Select);
				 break;
			}
			case PCC_TSI_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_TSI_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_TSI_INDEX] |=  (Select);
				 break;
			}
			case PCC_PORTA_INDEX :
						    {	
				 Types->CLKCFG[PCC_PORTA_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PORTA_INDEX] |=  (Select);
				 break;
			}  
			case PCC_PORTB_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_PORTB_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PORTB_INDEX] |=  (Select);
				 break;
			}
		    case PCC_PORTC_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_PORTC_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PORTC_INDEX] |=  (Select);
				 break;
			}
		    case PCC_PORTD_INDEX :
				 		    {	
				 Types->CLKCFG[PCC_PORTD_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PORTD_INDEX] |=  (Select);
				 break;
			} 
		    case PCC_PORTE_INDEX :
				 		    {	
				 Types->CLKCFG[PCC_PORTE_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PORTE_INDEX] |=  (Select);
				 break;
			} 
		    case PCC_PWT_INDEX :
				 		    {	
				 Types->CLKCFG[PCC_PWT_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_PWT_INDEX] |=  (Select);
				 break;
			} 
		    case PCC_EWM_INDEX :
				 		    {	
				 Types->CLKCFG[PCC_EWM_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_EWM_INDEX] |=  (Select);
				 break;
			} 
			case PCC_LPI2C0_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_LPI2C0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPI2C0_INDEX] |=  (Select);
				 break;
			}
			case PCC_LPUART0_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_LPUART0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPUART0_INDEX] |=  (Select);
				 break;
			}
			case PCC_LPUART1_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_LPUART1_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPUART1_INDEX] |=  (Select);
				 break;
			}
		    case PCC_LPUART2_INDEX :
				  		    {	
				 Types->CLKCFG[PCC_LPUART2_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_LPUART2_INDEX] |=  (Select);
				 break;
			}
			case PCC_CMP0_INDEX :	  
	   			    {	
				 Types->CLKCFG[PCC_CMP0_INDEX] &= ~(Select);
				 Types->CLKCFG[PCC_CMP0_INDEX] |=  (Select);
				 break;
			}
	  
	  }

	return ret;
}
/**
  * @brief  Delay according to machine cycles
  * @param  time want run
  */
void Delay(int n)
{
    uint32_t i;
    for (i = 0; i < n; i++)
    {
        __asm("nop");
    }
}