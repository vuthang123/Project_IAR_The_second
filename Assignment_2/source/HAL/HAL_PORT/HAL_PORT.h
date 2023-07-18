#ifndef HAL_PORT_H
#define HAL_PORT_H

#include "HAL_CORE_M0+.h"
#include "stdint.h"

/** Interrupt Number Definitions */
#define NUMBER_OF_INT_VECTORS 48                 /**< Number of interrupts in the Vector table */

typedef enum IRQn {
  /* Auxiliary constants */
  NotAvail_IRQn                = -128,             /**< Not available device specific interrupt */

  /* Core interrupts */
  NonMaskableInt_IRQn          = -14,              /**< Non Maskable Interrupt */
  HardFault_IRQn               = -13,              /**< Cortex-M0 SV Hard Fault Interrupt */
  SVCall_IRQn                  = -5,               /**< Cortex-M0 SV Call Interrupt */
  PendSV_IRQn                  = -2,               /**< Cortex-M0 Pend SV Interrupt */
  SysTick_IRQn                 = -1,               /**< Cortex-M0 System Tick Interrupt */

  /* Device specific interrupts */
  Reserved16_IRQn              = 0,                /**< Reserved interrupt */
  Reserved17_IRQn              = 1,                /**< Reserved interrupt */
  Reserved18_IRQn              = 2,                /**< Reserved interrupt */
  Reserved19_IRQn              = 3,                /**< Reserved interrupt */
  Reserved20_IRQn              = 4,                /**< Reserved interrupt */
  FTFA_IRQn                    = 5,                /**< Flash memory single interrupt vector for all sources */
  LVD_LVW_IRQn                 = 6,                /**< Low-voltage detect, low-voltage warning */
  PORTAE_IRQn                  = 7,                /**< Pin detect (Port A, E) */
  LPI2C0_IRQn                  = 8,                /**< Inter-integrated circuit 0 interrupt */
  Reserved25_IRQn              = 9,                /**< Reserved interrupt */
  LPSPI0_IRQn                  = 10,               /**< Serial peripheral Interface 0 interrupt */
  Reserved27_IRQn              = 11,               /**< Reserved interrupt */
  LPUART0_IRQn                 = 12,               /**< Single interrupt vector for all sources */
  LPUART1_IRQn                 = 13,               /**< Single interrupt vector for all sources */
  LPUART2_IRQn                 = 14,               /**< Single interrupt vector for all sources */
  ADC0_IRQn                    = 15,               /**< ADC0 conversion complete interrupt */
  CMP0_IRQn                    = 16,               /**< CMP0 interrupt */
  FTM0_IRQn                    = 17,               /**< FTM0 single interrupt vector for all sources */
  FTM1_IRQn                    = 18,               /**< FTM1 single interrupt vector for all sources */
  Reserved35_IRQn              = 19,               /**< Reserved interrupt */
  RTC_IRQn                     = 20,               /**< Single interrupt vector for all sources */
  Reserved37_IRQn              = 21,               /**< Reserved interrupt */
  LPIT0_IRQn                   = 22,               /**< LPIT channel 0-1 */
  Reserved39_IRQn              = 23,               /**< Reserved interrupt */
  TSI_IRQn                     = 24,               /**< TSI interrupt */
  PDB0_IRQn                    = 25,               /**< Programmable delay block interrupt */
  PORTBCD_IRQn                 = 26,               /**< Pin detect (Port B, C, D) */
  SCG_RCM_IRQn                 = 27,               /**< Single interrupt vector for SCG and RCM */
  WDOG_EWM_IRQn                = 28,               /**< Single interrupt vector for WDOG and EWM */
  PWT_LPTMR0_IRQn              = 29,               /**< Single interrupt vector for PWT and LPTMR0 */
  MSCAN_Rx_IRQn                = 30,               /**< MSCAN Rx Interrupt */
  MSCAN_ORed_IRQn              = 31                /**< MSCAN Tx, Err and Wake-up interrupt */
} IRQn_Type;

/** PORT - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCR[32];                           /**< Pin Control Register n, array offset: 0x0, array step: 0x4 */
  __O  uint32_t GPCLR;                             /**< Global Pin Control Low Register, offset: 0x80 */
  __O  uint32_t GPCHR;                             /**< Global Pin Control High Register, offset: 0x84 */
       uint8_t RESERVED_0[24];
  __IO uint32_t ISFR;                              /**< Interrupt Status Flag Register, offset: 0xA0 */
       uint8_t RESERVED_1[28];
  __IO uint32_t DFER;                              /**< Digital Filter Enable Register, offset: 0xC0 */
  __IO uint32_t DFCR;                              /**< Digital Filter Clock Register, offset: 0xC4 */
  __IO uint32_t DFWR;                              /**< Digital Filter Width Register, offset: 0xC8 */
} PORT_Type;

/* ----------------------------------------------------------------------------
   -- PORT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PORT_Register_Masks PORT Register Masks
 * @{
 */

/*! @name PCR - Pin Control Register n */
/*! @{ */
#define PORT_PCR_PS_MASK                         (0x1U)
#define PORT_PCR_PS_SHIFT                        (0U)
/*! PS - Pull Select
 *  0b0..Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set.
 *  0b1..Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set.
 */
#define PORT_PCR_PS(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PS_SHIFT)) & PORT_PCR_PS_MASK)
#define PORT_PCR_PE_MASK                         (0x2U)
#define PORT_PCR_PE_SHIFT                        (1U)
/*! PE - Pull Enable
 *  0b0..Internal pullup or pulldown resistor is not enabled on the corresponding pin.
 *  0b1..Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
#define PORT_PCR_PE(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PE_SHIFT)) & PORT_PCR_PE_MASK)
#define PORT_PCR_PFE_MASK                        (0x10U)
#define PORT_PCR_PFE_SHIFT                       (4U)
/*! PFE - Passive Filter Enable
 *  0b0..Passive input filter is disabled on the corresponding pin.
 *  0b1..Passive input filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 *       Refer to the device data sheet for filter characteristics.
 */
#define PORT_PCR_PFE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_PFE_SHIFT)) & PORT_PCR_PFE_MASK)
#define PORT_PCR_DSE_MASK                        (0x40U)
#define PORT_PCR_DSE_SHIFT                       (6U)
/*! DSE - Drive Strength Enable
 *  0b0..Low drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 *  0b1..High drive strength is configured on the corresponding pin, if pin is configured as a digital output.
 */
#define PORT_PCR_DSE(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_DSE_SHIFT)) & PORT_PCR_DSE_MASK)
#define PORT_PCR_MUX_MASK                        (0x700U)
#define PORT_PCR_MUX_SHIFT                       (8U)
/*! MUX - Pin Mux Control
 *  0b000..Pin disabled (Alternative 0) (analog).
 *  0b001..Alternative 1 (GPIO).
 *  0b010..Alternative 2 (chip-specific).
 *  0b011..Alternative 3 (chip-specific).
 *  0b100..Alternative 4 (chip-specific).
 *  0b101..Alternative 5 (chip-specific).
 *  0b110..Alternative 6 (chip-specific).
 *  0b111..Alternative 7 (chip-specific).
 */
#define PORT_PCR_MUX(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_MUX_SHIFT)) & PORT_PCR_MUX_MASK)
#define PORT_PCR_LK_MASK                         (0x8000U)
#define PORT_PCR_LK_SHIFT                        (15U)
/*! LK - Lock Register
 *  0b0..Pin Control Register fields [15:0] are not locked.
 *  0b1..Pin Control Register fields [15:0] are locked and cannot be updated until the next system reset.
 */
#define PORT_PCR_LK(x)                           (((uint32_t)(((uint32_t)(x)) << PORT_PCR_LK_SHIFT)) & PORT_PCR_LK_MASK)
#define PORT_PCR_IRQC_MASK                       (0xF0000U)
#define PORT_PCR_IRQC_SHIFT                      (16U)
/*! IRQC - Interrupt Configuration
 *  0b0000..Interrupt Status Flag (ISF) is disabled.
 *  0b0100..Reserved.
 *  0b0101..Reserved.
 *  0b0110..Reserved.
 *  0b0111..Reserved.
 *  0b1000..ISF flag and Interrupt when logic 0.
 *  0b1001..ISF flag and Interrupt on rising-edge.
 *  0b1010..ISF flag and Interrupt on falling-edge.
 *  0b1011..ISF flag and Interrupt on either edge.
 *  0b1100..ISF flag and Interrupt when logic 1.
 *  0b1101..Reserved.
 *  0b1110..Reserved.
 *  0b1111..Reserved.
 */
#define PORT_PCR_IRQC(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_PCR_IRQC_SHIFT)) & PORT_PCR_IRQC_MASK)
#define PORT_PCR_ISF_MASK                        (0x1000000U)
#define PORT_PCR_ISF_SHIFT                       (24U)
/*! ISF - Interrupt Status Flag
 *  0b0..Configured interrupt is not detected.
 *  0b1..Configured interrupt is detected. The flag remains set until a logic 1 is written to the flag. If the pin
 *       is configured for a level sensitive interrupt and the pin remains asserted, then the flag is set again
 *       immediately after it is cleared.
 */
#define PORT_PCR_ISF(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_PCR_ISF_SHIFT)) & PORT_PCR_ISF_MASK)
/*! @} */

/* The count of PORT_PCR */
#define PORT_PCR_COUNT                           (32U)

/*! @name GPCLR - Global Pin Control Low Register */
/*! @{ */
#define PORT_GPCLR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCLR_GPWD_SHIFT                    (0U)
/*! GPWD - Global Pin Write Data
 */
#define PORT_GPCLR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWD_SHIFT)) & PORT_GPCLR_GPWD_MASK)
#define PORT_GPCLR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCLR_GPWE_SHIFT                    (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCLR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCLR_GPWE_SHIFT)) & PORT_GPCLR_GPWE_MASK)
/*! @} */

/*! @name GPCHR - Global Pin Control High Register */
/*! @{ */
#define PORT_GPCHR_GPWD_MASK                     (0xFFFFU)
#define PORT_GPCHR_GPWD_SHIFT                    (0U)
/*! GPWD - Global Pin Write Data
 */
#define PORT_GPCHR_GPWD(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWD_SHIFT)) & PORT_GPCHR_GPWD_MASK)
#define PORT_GPCHR_GPWE_MASK                     (0xFFFF0000U)
#define PORT_GPCHR_GPWE_SHIFT                    (16U)
/*! GPWE - Global Pin Write Enable
 *  0b0000000000000000..Corresponding Pin Control Register is not updated with the value in GPWD.
 *  0b0000000000000001..Corresponding Pin Control Register is updated with the value in GPWD.
 */
#define PORT_GPCHR_GPWE(x)                       (((uint32_t)(((uint32_t)(x)) << PORT_GPCHR_GPWE_SHIFT)) & PORT_GPCHR_GPWE_MASK)
/*! @} */

/*! @name ISFR - Interrupt Status Flag Register */
/*! @{ */
#define PORT_ISFR_ISF_MASK                       (0xFFFFFFFFU)
#define PORT_ISFR_ISF_SHIFT                      (0U)
/*! ISF - Interrupt Status Flag
 *  0b00000000000000000000000000000000..Configured interrupt is not detected.
 *  0b00000000000000000000000000000001..Configured interrupt is detected. The flag remains set until a logic 1 is
 *                                      written to the flag. If the pin is configured for a level sensitive
 *                                      interrupt and the pin remains asserted, then the flag is set again immediately
 *                                      after it is cleared.
 */
#define PORT_ISFR_ISF(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_ISFR_ISF_SHIFT)) & PORT_ISFR_ISF_MASK)
/*! @} */

/*! @name DFER - Digital Filter Enable Register */
/*! @{ */
#define PORT_DFER_DFE_MASK                       (0xFFFFFFFFU)
#define PORT_DFER_DFE_SHIFT                      (0U)
/*! DFE - Digital Filter Enable
 *  0b00000000000000000000000000000000..Digital filter is disabled on the corresponding pin and output of the digital filter is reset to zero.
 *  0b00000000000000000000000000000001..Digital filter is enabled on the corresponding pin, if the pin is configured as a digital input.
 */
#define PORT_DFER_DFE(x)                         (((uint32_t)(((uint32_t)(x)) << PORT_DFER_DFE_SHIFT)) & PORT_DFER_DFE_MASK)
/*! @} */

/*! @name DFCR - Digital Filter Clock Register */
/*! @{ */
#define PORT_DFCR_CS_MASK                        (0x1U)
#define PORT_DFCR_CS_SHIFT                       (0U)
/*! CS - Clock Source
 *  0b0..Digital filters are clocked by the bus clock.
 *  0b1..Digital filters are clocked by the LPO clock.
 */
#define PORT_DFCR_CS(x)                          (((uint32_t)(((uint32_t)(x)) << PORT_DFCR_CS_SHIFT)) & PORT_DFCR_CS_MASK)
/*! @} */

/*! @name DFWR - Digital Filter Width Register */
/*! @{ */
#define PORT_DFWR_FILT_MASK                      (0x1FU)
#define PORT_DFWR_FILT_SHIFT                     (0U)
/*! FILT - Filter Length
 */
#define PORT_DFWR_FILT(x)                        (((uint32_t)(((uint32_t)(x)) << PORT_DFWR_FILT_SHIFT)) & PORT_DFWR_FILT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PORT_Register_Masks */


/* PORT - Peripheral instance base addresses */
/** Peripheral PORTA base address */
#define PORTA_BASE                               (0x40049000u)
/** Peripheral PORTA base pointer */
#define PORTA                                    ((PORT_Type *)PORTA_BASE)
/** Peripheral PORTB base address */
#define PORTB_BASE                               (0x4004A000u)
/** Peripheral PORTB base pointer */
#define PORTB                                    ((PORT_Type *)PORTB_BASE)
/** Peripheral PORTC base address */
#define PORTC_BASE                               (0x4004B000u)
/** Peripheral PORTC base pointer */
#define PORTC                                    ((PORT_Type *)PORTC_BASE)
/** Peripheral PORTD base address */
#define PORTD_BASE                               (0x4004C000u)
/** Peripheral PORTD base pointer */
#define PORTD                                    ((PORT_Type *)PORTD_BASE)
/** Peripheral PORTE base address */
#define PORTE_BASE                               (0x4004D000u)
/** Peripheral PORTE base pointer */
#define PORTE                                    ((PORT_Type *)PORTE_BASE)

typedef enum {
	  HAL_PORT_SUCCESS = 0,
	  HAL_PORT_FAIL
}HAL_PORT_Erorr_E;

typedef enum 
{
	  Mode_Analog = 0u, /*000 Pin disabled (Alternative 0) (analog)*/
	  Mode_Gpio   = 1u, /*001 Alternative 1 (GPIO).*/
	  Mode_Alternative_2 = 2u,/*010 Alternative 2 (chip-specific).*/
	  Mode_Alternative_3 = 3u,/*011 Alternative 3 (chip-specific).*/
	  Mode_Alternative_4 = 4u,/*100 Alternative 4 (chip-specific).*/
	  Mode_Alternative_5 = 5u,/*101 Alternative 5 (chip-specific).*/
	  Mode_Alternative_6 = 6u,/*110 Alternative 6 (chip-specific).*/
	  Mode_Alternative_7 = 7u,/*111 Alternative 7 (chip-specific).*/
	  
}Mux_type;

typedef enum 
{
	PULL_DISABLE = 0U,
	PULL_ENABLE  
}Pull_ENABLE_Type_E;

typedef enum 
{
	PULL_DOWN = 0U,
	PULL_UP   
}Pull_SELECT_Type_E;

/*******************************************************************************
 * API
 ******************************************************************************/
HAL_PORT_Erorr_E HAL_PORT_Select_Mode(PORT_Type* PORTx,uint32_t Select_Pin,Mux_type Select_Mode_IO);

HAL_PORT_Erorr_E HAL_PORT_Select_Pull_Enable(PORT_Type* PORTx,uint32_t Select_Pin,Pull_ENABLE_Type_E Select_Mode_IO);

HAL_PORT_Erorr_E HAL_PORT_Select_Pull_Mode(PORT_Type* PORTx,uint32_t Select_Pin,Pull_SELECT_Type_E Select_Mode_IO);

#endif /*HAL_PORT_H*/