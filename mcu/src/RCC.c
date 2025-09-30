// Broderick Bownds
// brbownds@hmc.edu
// 9/29/2025


// STM32L432KC_RCC.c
// Source code for RCC functions

#include "RCC.h"

void configurePLL() {
    // Set clock to 80 MHz
    // Output freq = (src_clk) * (N/M) / R
    // (4 MHz) * (N/M) / R = 80 MHz
    // M: XX, N: XX, R: XX
    // Use MSI as PLLSRC

    //: Turn off PLL
    
    // : Wait till PLL is unlocked (e.g., off)
    

    // Load configuration
    // : Set PLL SRC to MSI


    // : Set PLLN


    // : Set PLLM
    

    // : Set PLLR

    
    // : Enable PLLR output
    

    // : Enable PLL
    
    
    // : Wait until PLL is locked
    
}

void configureClock(){
    // Configure and turn on PLL
    configurePLL();

    // Select PLL as clock source
    RCC->CFGR |= (0b11 << 0);
    while(!((RCC->CFGR >> 2) & 0b11));
}