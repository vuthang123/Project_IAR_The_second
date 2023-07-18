#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <stdint.h>

#define BUTTON_SW2                      (1 << 3)
/*@brief:Address start of peripheral*/
#define PERRIPH_BASE_ADD                (0x40000000UL)
/*@brief:Address start clock of peripheral*/
#define PCC_BASE_ADD                    (PERRIPH_BASE_ADD + 0x00065000UL)
#define PCC_PORTB_OFFSET                (0x00000128UL)
#define PCC_PORTD_OFFSET                (0x00000130UL)
#define PCC_PORTD_EN_CLOCK              (PCC_BASE_ADD + PCC_PORTD_OFFSET)
#define PCC_PORTB_EN_CLOCK              (PCC_BASE_ADD + PCC_PORTB_OFFSET)
/*@brief: Address start port */
#define PORTB_BASE_ADD          		(PERRIPH_BASE_ADD + 0x0004A000UL)
#define PORTB_PCR5_OFFSET       		(0x00000014UL)
#define PORTB_PCR5_REG_ADD      		(PORTB_BASE_ADD + PORTB_PCR5_OFFSET)
#define PORTD_BASE_ADD          		(PERRIPH_BASE_ADD + 0x0004C000UL)
#define PORTD_PCR3_OFFSET       		(0x0000000CUL)
#define PORTD_PCR3_REG_ADD      		(PORTD_BASE_ADD + PORTD_PCR3_OFFSET)
/*@brief: Address start gpio of peripheral*/
#define GPIO_BASE_ADD                   (PERRIPH_BASE_ADD + 0x000FF000UL)
#define GPIOB_PDDR_OFFSET       	    (0x00000054UL)
#define GPIOB_PDOR_OFFSET       	    (0x00000040UL)
#define GPIOB_PSOR_OFFSET       	    (0x00000044UL)
#define GPIOB_PCOR_OFFSET       	    (0x00000048UL)
#define GPIOB_PDDR_REG_ADD      	    (GPIO_BASE_ADD + GPIOB_PDDR_OFFSET)
#define GPIOB_PDOR_REG_ADD      	    (GPIO_BASE_ADD + GPIOB_PDOR_OFFSET)
#define GPIOB_PSOR_REG_ADD      	    (GPIO_BASE_ADD + GPIOB_PSOR_OFFSET)
#define GPIOB_PCOR_REG_ADD      	    (GPIO_BASE_ADD + GPIOB_PCOR_OFFSET)
#define GPIOD_PDOR_OFFSET       	    (0x000000C0UL)
#define GPIOD_PSOR_OFFSET       	    (0x000000C4UL)
#define GPIOD_PCOR_OFFSET       	    (0x000000C8UL)
#define GPIOD_PDIR_OFFSET       	    (0x000000D0UL)
#define GPIOD_PDDR_OFFSET       	    (0x000000D4UL)
#define GPIOD_PDOR_REG_ADD      	    (GPIO_BASE_ADD + GPIOD_PDOR_OFFSET)
#define GPIOD_PSOR_REG_ADD      	    (GPIO_BASE_ADD + GPIOD_PSOR_OFFSET)
#define GPIOD_PCOR_REG_ADD      	    (GPIO_BASE_ADD + GPIOD_PCOR_OFFSET)
#define GPIOD_PDIR_REG_ADD      	    (GPIO_BASE_ADD + GPIOD_PDIR_OFFSET)
#define GPIOD_PDDR_REG_ADD      	    (GPIO_BASE_ADD + GPIOD_PDDR_OFFSET)

/**
 * @brief: Initialization led
 * @param none
 * @return none
 */
void Init_Led(void);
/**
 * @brief: Delay (Core do nothing)
 * @param none
 * @return none
 */
void Delay(int n);
/**
 * @brief: Initialization button
 * @param none
 * @return none
 */
void Button_Init(void);
/**
 * @brief: Led On
 * @param none
 * @return none
 */
void Led_On(void);
/**
 * @brief: led Off
 * @param none
 * @return none
 */
void Led_Off(void);
/**
 * @brief: Read pin button 
  * @param none
 * @return none
 */

uint32_t ReadPin_Button(uint32_t Pin);
/**
 * @brief: Write pin led
 * @param none
 * @return none
 */
void WritePin_Led(uint32_t status);



#endif /*_DRIVER_H_*/ 