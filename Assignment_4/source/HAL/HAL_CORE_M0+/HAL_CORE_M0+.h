#ifndef HAL_CORE_M0_PLUS_H_
#define HAL_CORE_M0_PLUS_H_

#include "stdint.h"
#include "HAL_PORT.h"

#define     __I     volatile             /*!< Defines 'read only' permissions */
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */


/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  volatile uint32_t ISER[1U];               /*!< Offset: 0x000 (R/W)  Interrupt Set Enable Register */
        uint32_t RESERVED0[31U];
  volatile uint32_t ICER[1U];               /*!< Offset: 0x080 (R/W)  Interrupt Clear Enable Register */
        uint32_t RESERVED1[31U];
  volatile uint32_t ISPR[1U];               /*!< Offset: 0x100 (R/W)  Interrupt Set Pending Register */
        uint32_t RESERVED2[31U];
  volatile uint32_t ICPR[1U];               /*!< Offset: 0x180 (R/W)  Interrupt Clear Pending Register */
        uint32_t RESERVED3[31U];
        uint32_t RESERVED4[64U];
  volatile uint32_t IP[8U];                 /*!< Offset: 0x300 (R/W)  Interrupt Priority Register */
}  NVIC_Type;

#define SCS_BASE            (0xE000E000UL)     

#define NVIC_BASE           (SCS_BASE +  0x0100UL) 
#define NVIC                ((NVIC_Type      *)     NVIC_BASE     ) 



#endif /*HAL_CORE_M0_PLUS_H_*/
