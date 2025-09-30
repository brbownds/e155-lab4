// Broderick Bownds
// brbownds@hmc.edu
// 9/29/2025


// TIM.h
// Header for TIM16 and TIM15

#ifndef TIM_H
#define TIM_H

#include <stdint.h> 
#include "GPIO.h"

// Define

#define __IO volatile


// Base addresses
#define TIM15_BASEADD (0x40014000) // base address of TIM15
#define TIM16_BASEADD (0x40014400) // base address of TIM16

typedef struct
{
  __IO uint32_t CR1;          /*!< TIMxx Control Register 1,                    Address offset: 0x00 */
  __IO uint32_t CR2;          /*!< TIMxx Control Register 2,                    Address offset: 0x04 */
       uint32_t RESERVED00;    /*!< Reserved,                                   Address offset: 0x08 */
  __IO uint32_t DIER;         /*!< TIMxx DMA/interrupt enable register,         Address offset: 0x0C */
  __IO uint32_t SR;           /*!< TIMxx status register,                       Address offset: 0x10 */
  __IO uint32_t EGR;          /*!< TIMxx event generation register,             Address offset: 0x14 */
  __IO uint32_t CCMR1;        /*!< TIMxx capture/compare mode register 1,       Address offset: 0x18 */
       uint32_t RESERVED01;  /*!< TIMxx capture/compare mode register 1,       Address offset: 0x1C */
  __IO uint32_t CCER;         /*!< TIMxx capture/compare enable register,       Address offset: 0x20 */
  __IO uint32_t CNT;          /*!< TIMxx counter,                               Address offset: 0x24 */
  __IO uint32_t PSC;          /*!< TIMxx prescaler,                             Address offset: 0x28 */
  __IO uint32_t ARR;          /*!< TIMxx auto-reload register,                  Address offset: 0x2C */
  __IO uint32_t RCR;          /*!< TIMxx repetition counter regsiter,           Address offset: 0x30 */
  __IO uint32_t CCR1;         /*!< TIMxx capture/compare register 1,            Address offset: 0x34 */
       uint32_t RESERVED02;    /*!< Reserved,                                   Address offset: 0x38 */
       uint32_t RESERVED03;    /*!< Reserved,                                   Address offset: 0x3C */
       uint32_t RESERVED04;    /*!< Reserved,                                   Address offset: 0x40 */
  __IO uint32_t BDTR;         /*!< TIMxx breakand dead-time register,           Address offset: 0x44 */
  __IO uint32_t DCR;          /*!< TIMxx DMA control register,                  Address offset: 0x48 */
  __IO uint32_t DMAR;         /*!< TIMxx DMA address for full transfer,         Address offset: 0x4C */
  __IO uint32_t OR1_1;        /*!< TIMxx option register 1,                     Address offset: 0x50 */
       uint32_t RESERVED05;    /*!< Reserved,                                   Address offset: 0x54 */
       uint32_t RESERVED06;    /*!< Reserved,                                   Address offset: 0x58 */
       uint32_t RESERVED07;    /*!< Reserved,                                   Address offset: 0x5C */
  __IO uint32_t OR2_1;        /*!< TIMxx option register 2,                     Address offset: 0x60 */
} TIM_TypeDef;

#define TIM15 ((TIM_TypeDef *) TIM15_BASEADD)
#define TIM16 ((TIM_TypeDef *) TIM16_BASEADD)

// Function prototypes 
void delay_us(uint32_t us); 

void delay_ms(uint32_t ms);

void setupPWM(TIM_TypeDef *TIMx, uint32_t timer_clk, int frequency, int dutycycle); 

void changePWM(TIM_TypeDef *TIMx, uint32_t timer_clk, int frequency, int dutycycle); 
#endif 
