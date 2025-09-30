// Broderick Bownds
// brbownds@hmc.edu
// 9/29/2025

// RCC.c
// Source code for RCC functions

#include "RCC.h"

#define FLASH_BASE   0x40022000UL
#define FLASH_ACR   (*(volatile uint32_t *)(FLASH_BASE + 0x00))

void configurePLL(void) {
    // disable PLL if it’s on
    RCC->CR &= ~(1 << 24);          // PLLON = 0
    while (RCC->CR & (1 << 25));    // wait until PLLRDY = 0

    // select PLL source = MSI 
    RCC->PLLCFGR &= ~(0b11 << 0);
    RCC->PLLCFGR |=  (0b01 << 0);

    // set PLLM = 1 (
    RCC->PLLCFGR &= ~(0b111 << 4);

    // set PLLN = 40 
    RCC->PLLCFGR &= ~(0x7F << 8);
    RCC->PLLCFGR |=  (40 << 8);

    // set PLLR = 2 
    RCC->PLLCFGR &= ~(0b11 << 25);

    // enable PLLR output
    RCC->PLLCFGR |= (1 << 24);      // PLLREN = 1

    // enable PLL
    RCC->CR |= (1 << 24);           // PLLON = 1
    while (!(RCC->CR & (1 << 25))); // wait until PLLRDY = 1
}

void configureClock(void) {
    // 80 MHz requires 4 wait states
    FLASH_ACR &= ~0x7;      
    FLASH_ACR |= 0x4;       

    //  configure and start PLL
    configurePLL();

    // switch SYSCLK source to PLL
    RCC->CFGR &= ~(0b11 << 0);   
    RCC->CFGR |=  (0b11 << 0);  

    // Wait
    while (((RCC->CFGR >> 2) & 0b11) != 0b11);
}
