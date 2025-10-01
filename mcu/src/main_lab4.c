// Broderick Bownds
// brbownds@hmc.edu
// 9/29/2025

// This main module is the application entry point for Lab 4.
// Configures the system clock, sets up GPIO and timers, and plays 
// songs by generating square-wave PWM signals on a speaker using 
// TIM16 for frequency and TIM15 for duration control.

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

const int star_wars_theme[][2] = {
    {440, 500}, {440, 500}, {349, 350}, {523, 150}, // A4, A4, F4, C5
    {440, 500}, {349, 350}, {523, 150}, {440, 1000}, // A4, F4, C5, A4

    {659, 500}, {659, 500}, {659, 500},             // E5, E5, E5
    {698, 350}, {523, 150}, {392, 500}, {349, 350}, {523, 150}, {440, 1000}, // F5, C5, G4, F4, C5, A4

    {880, 500}, {440, 350}, {440, 150}, {880, 500}, // A5, A4, A4, A5
    {830, 250}, {784, 250}, {740, 250}, {698, 250}, // G#5, G5, F#5, F5
    {698, 125}, {698, 125},                         // F5, F5
    {659, 250}, {587, 250}, {659, 500},             // E5, D5, E5

    {392, 250}, {440, 500}, {523, 500}, {440, 500}, // G4, A4, C5, A4
    {349, 350}, {523, 150}, {440, 1000},            // F4, C5, A4

    {0, 0} // end marker
};


int main(void) {
    configureFlash();
    configureClock();

    // Enable GPIOA + TIM15 + TIM16
    RCC->AHB2ENR |= (1 << 0);     // GPIOAEN
    RCC->APB2ENR |= (1 << 16);    // TIM15EN
    RCC->APB2ENR |= (1 << 17);    // TIM16EN

    // Configure PA6 = TIM16_CH1 (AF14)
    pinMode(6, GPIO_ALT);
    GPIO->AFRL &= ~(0xF << (6 * 4));
    GPIO->AFRL |=  (14 << (6 * 4));

    // Start PWM on TIM16
    const uint32_t TIMER_CLK_HZ = 80000000/80;
    setupPWM(TIM16, TIMER_CLK_HZ, 440, 50); // A4 default

    // --- Play Fur Elise ---
    int song_length = sizeof(notes) / sizeof(notes[0]);
    for (int i = 0; i < song_length; i++) {
        int freq = notes[i][0];
        int dur  = notes[i][1];

        if (dur == 0) break;
        
        if (freq == 0) {
            TIM16->CCER &= ~(1 << 0); // rest
            delay_ms(dur);
            TIM16->CCER |= (1 << 0);
        } else {
            changePWM(TIM16, TIMER_CLK_HZ, freq, 50);
            delay_ms(dur);
        }
    }

    // --- Pause for 2 seconds ---
    TIM16->CCER &= ~(1 << 0);
    delay_ms(2000);
    TIM16->CCER |= (1 << 0);

    // --- Play Star Wars ---
    int sw_length = sizeof(star_wars_theme) / sizeof(star_wars_theme[0]);
    for (int j = 0; j < sw_length; j++) {
        int freq = star_wars_theme[j][0];
        int dur  = star_wars_theme[j][1];

        if (dur == 0) break;
        
        if (freq == 0) {
            TIM16->CCER &= ~(1 << 0); // rest
            delay_ms(dur);
            TIM16->CCER |= (1 << 0);
        } else {
            changePWM(TIM16, TIMER_CLK_HZ, freq, 50);
            delay_ms(dur);
        }
    }

    TIM16->CR1 &= ~1; // stop PWM
    while (1);
}


