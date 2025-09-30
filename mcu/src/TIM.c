// TIM.c
// Timer functions for E155 Lab 4
// Broderick Bownds
// 9/30/2025

#include "TIM.h"

// Delay using TIM15 (basic timer)
void delay_us(uint32_t us) {
    // Reset counter
    TIM15->CNT = 0;

    // Prescaler: tick = 1 µs → PSC = (80 MHz / 1 MHz) - 1 = 79
    TIM15->PSC = 79;

    // Auto-reload = number of microsec
    TIM15->ARR = us;

    // Clear update flag
    TIM15->SR &= ~1;

    // Enable counter
    TIM15->CR1 |= 1;

    // Wait until update event flag (UIF) is set
    while (!(TIM15->SR & 1));

    // Clear flag and stop counter
    TIM15->SR &= ~1;
    TIM15->CR1 &= ~1;
}

// Millisecond wrapper (optional)
void delay_ms(uint32_t ms) {
    while (ms--) {
        delay_us(1000);
    }
}


// Setup PWM on channel 1 of a given timer (e.g., TIM16 for audio output)
void setupPWM(TIM_TypeDef *TIMx, uint32_t timer_clk, int frequency, int dutycycle) {
    if (frequency <= 0) return;

    // Compute period (ARR+1 = timer_clk/frequency)
    uint32_t period = timer_clk / (uint32_t)frequency;
    if (period < 2) period = 2; // avoid divide by zero

    TIMx->PSC = 0;
    TIMx->ARR = period - 1;

    // Compare value = duty %
    uint32_t ccr = (period * (uint32_t)dutycycle) / 100;
    if (ccr >= period) ccr = period - 1;
    TIMx->CCR1 = ccr;

    // PWM mode 1 (OC1M=110), enable preload
    TIMx->CCMR1 &= ~(0x7 << 4);
    TIMx->CCMR1 |=  (0x6 << 4); // PWM mode 1
    TIMx->CCMR1 |=  (1 << 3);   // OC1PE = 1

    // Enable channel 1 output
    TIMx->CCER &= ~(1 << 1);
    TIMx->CCER |=  (1 << 0);

    // Enable ARR preload
    TIMx->CR1 |= (1 << 7);

    // Main output enable (BDTR.MOE) — required on TIM15/16
    TIMx->BDTR |= (1 << 15);

    // Generate update to latch preload
    TIMx->EGR |= 1;

    // Start counter
    TIMx->CR1 |= 1;
}

// Change PWM frequency and duty cycle (for next note)
void changePWM(TIM_TypeDef *TIMx, uint32_t timer_clk, int frequency, int dutycycle) {
    if (frequency <= 0) return;

    uint32_t period = timer_clk / (uint32_t)frequency;
    if (period < 2) period = 2;

    uint32_t ccr = (period * (uint32_t)dutycycle) / 100;
    if (ccr >= period) ccr = period - 1;

    TIMx->ARR  = period - 1;
    TIMx->CCR1 = ccr;

    // Force update so new values take effect immediately
    TIMx->EGR |= 1;
}
