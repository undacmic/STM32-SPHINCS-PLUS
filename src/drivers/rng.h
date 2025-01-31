#ifndef RNG_H
#define RNG_H

#include <stdint.h>

/**
 * Create HRNG using time jitter betweenAN internal oscillator (HSI48) and a 
 * PLL clock signal with synthetic-generated frequency.
 * 
 * HSI48 / 16 -> TIM15_CH1
 * PLLPCLK / 16 -> TIM15_ch2
 * 
 * TIM15
 * CH2 - Configure input-capture on both edges
 * CH1 - Configure input capture on rising edge
 * 
 * DMA request on CH1 input capture that transfers the count measurement of CH2, updated on either rising or falling edge
 * 
 */

void RNG_Module_Init (void);
uint8_t* GenerateBytes (uint8_t seed_length);

#endif // RNG_H