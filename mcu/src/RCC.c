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
    
    RCC->CR &= ~(1 << 24);          // PLLON = turn off PLL
    while (RCC->CR >> (25 & 1)!= 0);    // wait until PLLRDY = 0

    // select PLL source = MSI 
    RCC->PLLCFGR &= ~(1 << 1);
    RCC->PLLCFGR |=  (1 << 0);

    // set PLLN = 80 
    RCC->PLLCFGR &= ~(0b11111111 << 8); // clearing the bits
    RCC->PLLCFGR |=  (0b1010000 << 8);

     // set PLLM = 1 cleaaring the bits
    RCC->PLLCFGR &= ~(0b111 << 4);

    // set PLLR = 2 
    RCC->PLLCFGR &= ~(0b11 << 26);
    RCC->PLLCFGR |= (1 << 25);

    // enable PLLR output
    RCC->PLLCFGR |= (1 << 24);      // PLLREN = 1

    // enable PLL
    RCC->CR |= (1 << 24);           // PLLON = 1
    while (!(RCC->CR >> 25 & 1)!=1); // wait until PLLRDY = 1
}

void configureClock() {
    // 80 MHz requires 4 wait 
    //  configure and start PLL
    configurePLL();
    // switch SYSCLK source to PLL
    RCC->CFGR |=  (0b11 << 0);  
    // Wait
    while (((RCC->CFGR >> 2) & 0b11) != 0b11);
}
