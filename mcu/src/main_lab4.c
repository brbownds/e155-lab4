// Broderick Bownds
// brbownds@hmc.edu
// 9/29/2025

// lab4_starter.c
// Fur Elise, E155 Lab 4
// Updated Fall 2024

#include "RCC.h"
#include "GPIO.h"
#include "TIM.h"

// Pitch in Hz, duration in ms
const int notes[][2] = {
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	250},
{  0,	125},
{494,	125},
{523,	125},
{587,	125},
{659,	375},
{392,	125},
{699,	125},
{659,	125},
{587,	375},
{349,	125},
{659,	125},
{587,	125},
{523,	375},
{330,	125},
{587,	125},
{523,	125},
{494,	250},
{  0,	125},
{330,	125},
{659,	125},
{  0,	250},
{659,	125},
{1319,	125},
{  0,	250},
{623,	125},
{659,	125},
{  0,	250},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{416,	125},
{494,	125},
{523,	250},
{  0,	125},
{330,	125},
{659,	125},
{623,	125},
{659,	125},
{623,	125},
{659,	125},
{494,	125},
{587,	125},
{523,	125},
{440,	250},
{  0,	125},
{262,	125},
{330,	125},
{440,	125},
{494,	250},
{  0,	125},
{330,	125},
{523,	125},
{494,	125},
{440,	500},
{  0,	0}};

int main(void) {
    // 1configure system clock (PLL to 80 MHz)
    configureClock();

    // enable clocks: GPIOA, TIM15, TIM16
    RCC->AHB2ENR |= (1 << 0);     
    RCC->APB2ENR |= (1 << 16); 
    RCC->APB2ENR |= (1 << 17);     

    // setup GPIO pin
    pinMode(6, GPIO_ALT);
    GPIOA->AFRL &= ~(0xF << (6 * 4));
    GPIOA->AFRL |=  (14 << (6 * 4));   // AF14 for PA6

    // start PWM on TIM16, 50% duty cycle
    const uint32_t TIMER_CLK_HZ = 80000000; // adjust if clock not at 80 MHz
    setupPWM(TIM16, TIMER_CLK_HZ, 440, 50); // start at A4=440Hz

    // play through all notes
    int song_length = sizeof(notes) / sizeof(notes[0]);
    for (int i = 0; i < song_length; i++) {
        int freq = notes[i][0];
        int dur  = notes[i][1];

        if (dur == 0) break;  // end of song

        if (freq == 0) {
            // reset - disable channel output
            TIM16->CCER &= ~(1 << 0); // CC1E=0
            delay_us(dur * 1000);
            TIM16->CCER |=  (1 << 0); // re-enable
        } else {
            // change frequency
            changePWM(TIM16, TIMER_CLK_HZ, freq, 50);
            delay_us(dur * 1000); // convert ms to us
        }
    }

    // stop PWM
    TIM16->CR1 &= ~1;
    while (1);
}
