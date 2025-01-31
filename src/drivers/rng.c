#include "common/defines.h"
#include "drivers/rng.h"

#include <stdint.h>
#include <stdlib.h>

#define K_D             (465)
#define K_M             (83)
#define DMA1_IRQn       (9)

volatile uint16_t raw_entropy_buffer[K_D] = { 0 };
volatile uint8_t conditioned_entropy_buffer[32] = { 0 };
volatile uint8_t buffer_index = 0, ready = 0;
uint8_t buffer_length = 0;

INTERRUPT_VECTOR DMA1_Channel1_IRQHandler (void) {
    static uint8_t transfer_count = 0;

    if (DMA1->ISR & DMA1_ISR_TF_FLAG(1)) {
        DMA1->IFCR |= DMA1_IFCR_CTCIF(1);

        uint8_t amplitude = 1, random_bit = 1;

        int i;
        for(i = 1; i < K_D; i++) {
            if (raw_entropy_buffer[i] > raw_entropy_buffer[i-1]) {
                amplitude = (amplitude == 1) ? 0 : 1;
            }

            random_bit ^= amplitude;
        }

        conditioned_entropy_buffer[buffer_index] <<= 1;
        conditioned_entropy_buffer[buffer_index] += random_bit;

        transfer_count++;
        if (transfer_count >= 8) {

            transfer_count -= 8;
            buffer_index++;
        }

        if (buffer_index == buffer_length) {
            DMA1->CCR1 &= ~DMA1_CCR_EN_MASK;
            TIM15->DIER &= ~TIM_DIER_CC1DE_MASK;

            buffer_index = 0;
            ready = 1;
        }
        
        TIM15->CNT = 0;

        DMA1->CCR1 &= ~DMA1_CCR_EN_MASK;

        DMA1->CNDTR1 = K_D;

        DMA1->CCR1 |= DMA1_CCR_EN_MASK;
        
    }

}

static void DMA1_Configure (void) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1->CPAR1 = (uint32_t) &TIM15->CCR2;
    DMA1->CMAR1 = (uint32_t) &raw_entropy_buffer[0];
    DMA1->CNDTR1 = K_D;

    DMA1->CCR1 |= DMA1_CCR_PL(3);
    DMA1->CCR1 |= DMA1_CCR_MSIZE(1);
    DMA1->CCR1 |= DMA1_CCR_PSIZE(1);
    DMA1->CCR1 |= DMA1_CCR_MINC_MASK;
    DMA1->CCR1 &= ~DMA1_CCR_CIRC_MASK;
    DMA1->CCR1 &= ~DMA1_CCR_DIR_MASK;

    DMAMUX->C0CR |=  DMAMUX_CxCR_DMAREQ_ID(40);
    
    DMA1->CCR1 |= DMA1_CCR_TCIE_MASK;
    DMA1->CCR1 |= DMA1_CCR_EN_MASK;

    NVIC_EnableIRQ(DMA1_IRQn);
}

static void TIM15_Configure (void) {
    RCC->APBENR2 |= RCC_APBENR2_TIM15EN;
    RCC->CCIPR |= RCC_CCIPR_TIM15SEL_MASK;

    TIM15->PSC = 0;
    TIM15->ARR = 0xFFFF;

    TIM15->TISEL &= ~TIM_TISEL_TI1SEL_MASK;
    TIM15->TISEL &= ~TIM_TISEL_TI2SEL_MASK;

    TIM15->CCMR1 &= ~TIM_CCMR1_CC1S_MASK;
    TIM15->CCMR1 |= TIM_CCMR1_CC1S(1);

    TIM15->CCMR1 &= ~TIM_CCMR1_CC2S_MASK;
    TIM15->CCMR1 |= TIM_CCMR1_CC2S(1);

    TIM15->CCER &= ~TIM_CCER_CC1NP_MASK;
    TIM15->CCER &= ~TIM_CCER_CC1P_MASK;

    TIM15->CCER |= TIM_CCER_CC2NP_MASK;
    TIM15->CCER |= TIM_CCER_CC2P_MASK; 
    
    TIM15->CR1 |= TIM_CR1_CEN_MASK;

    TIM15->CCER |= TIM_CCER_CC1E_MASK;
    TIM15->CCER |= TIM_CCER_CC2E_MASK;
}

void RNG_Module_Init (void) {
    DMA1_Configure();
    TIM15_Configure();
}

uint8_t* GenerateBytes (uint8_t seed_length) {
    buffer_length = seed_length;

    ready = 0;
    DMA1->CCR1 |= DMA1_CCR_EN_MASK;
    TIM15->DIER |= TIM_DIER_CC1DE_MASK;

    while (!ready);

    uint8_t* seed =  malloc(seed_length * sizeof(uint8_t));

    int i;
    for (i = 0; i < seed_length; i++) {
        seed[i] = conditioned_entropy_buffer[i];
        conditioned_entropy_buffer[i] = 0;
    }

    return seed;

}