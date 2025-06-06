#include "common/defines.h"

extern int main();
extern void __libc_init_array(void);

extern uint32_t _estack;
extern uint32_t _sidata;
extern uint32_t _data_start;
extern uint32_t _data_end;
extern uint32_t _bss_start;
extern uint32_t _bss_end;
extern uint32_t _heap_start;

/*================== Interrupt Vector Prototypes =========================================*/

void Default_Handler(void)                          __attribute__((weak));
void System_Init();

/*================== Internal Interrupts =================================================*/

void Reset_Handler(void)                                __attribute__((weak));
void NMI_Handler(void)                                  __attribute__((weak));  // Non Maskable Interrupt
void HardFault_Handler(void)                            __attribute__((weak));  // Cortex-M Hard Fault Interrupt 
void SVCall_Handler(void)                               __attribute__((weak));  // Cortex-M SV Call Interrupt 
void PendSV_Handler(void)                               __attribute__((weak));  // Cortex-M Pend SV Interrupt 
void SysTick_Handler(void)                              __attribute__((weak));  // Cortex-M System Tick Interrupt 

/*================== External Interrupts (STM32GxBx specific) ============================*/

void WWDG_IRQHandler()                              __attribute__((weak, alias ("Default_Handler")));
void PVD_VDDIO2_IRQHandler()                        __attribute__((weak, alias ("Default_Handler")));
void RTC_TAMP_IRQHandler()                          __attribute__((weak, alias ("Default_Handler")));
void FLASH_IRQHandler()                             __attribute__((weak, alias ("Default_Handler")));
void RCC_CRS_IRQHandler()                           __attribute__((weak, alias ("Default_Handler")));
void EXTI0_1_IRQHandler()                           __attribute__((weak, alias ("Default_Handler")));
void EXTI2_3_IRQHandler()                           __attribute__((weak, alias ("Default_Handler")));
void EXTI4_15_IRQHandler()                          __attribute__((weak, alias ("Default_Handler")));
void USB_UCPD1_2_IRQHandler()                       __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel1_IRQHandler()                     __attribute__((weak, alias ("Default_Handler")));
void DMA1_Channel2_3_IRQHandler()                   __attribute__((weak, alias ("Default_Handler")));
void DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler() __attribute__((weak, alias ("Default_Handler")));
void ADC1_COMP_IRQHandler()                         __attribute__((weak, alias ("Default_Handler")));
void TIM1_BRK_UP_TRG_COM_IRQHandler()               __attribute__((weak, alias ("Default_Handler")));
void TIM1_CC_IRQHandler()                           __attribute__((weak, alias ("Default_Handler")));
void TIM2_IRQHandler()                              __attribute__((weak, alias ("Default_Handler")));
void TIM3_TIM4_IRQHandler()                         __attribute__((weak, alias ("Default_Handler")));
void TIM6_DAC_LPTIM1_IRQHandler()                   __attribute__((weak, alias ("Default_Handler")));
void TIM7_LPTIM2_IRQHandler()                       __attribute__((weak, alias ("Default_Handler")));
void TIM14_IRQHandler()                             __attribute__((weak, alias ("Default_Handler")));
void TIM15_IRQHandler()                             __attribute__((weak, alias ("Default_Handler")));
void TIM16_FDCAN_IT0_IRQHandler()                   __attribute__((weak, alias ("Default_Handler")));
void TIM17_FDCAN_IT1_IRQHandler()                   __attribute__((weak, alias ("Default_Handler")));
void I2C1_IRQHandler()                              __attribute__((weak, alias ("Default_Handler")));
void I2C2_3_IRQHandler()                            __attribute__((weak, alias ("Default_Handler")));
void SPI1_IRQHandler()                              __attribute__((weak, alias ("Default_Handler")));
void SPI2_3_IRQHandler()                            __attribute__((weak, alias ("Default_Handler")));
void USART1_IRQHandler()                            __attribute__((weak, alias ("Default_Handler")));
void USART2_LPUART2_IRQHandler()                    __attribute__((weak, alias ("Default_Handler")));
void USART3_4_5_6_LPUART1_IRQHandler()              __attribute__((weak, alias ("Default_Handler")));
void CEC_IRQHandler()                               __attribute__((weak, alias ("Default_Handler")));

/*================== Function Definitions ==================================================*/

// Normally provided by Newlib's runtime file crti.o, but we compile without
// (-startfiles) Inserted by __libc_init_array because newlib was compiled with
// _HAVE_INIT_FINI. We don't need it, so add an empty stub.
void _init(void) {} 

void *_sbrk(int incr) {
    static unsigned char *heap = 0;
    unsigned char *prev_heap;

    if (heap == 0) {
        heap = (unsigned char *)&_heap_start;
    }

    prev_heap = heap;
    heap += incr;

    return prev_heap;
}

void Reset_Handler(void){
    __asm (
        "LDR R0, =_estack\n\t"
        "MOV SP, R0\n\t"
    );

    const uint32_t *dataSrc = &_sidata;
    uint32_t *dataDest = &_data_start;
    while (dataDest != &_data_end) {
        *dataDest++ = *dataSrc++;
    }

    __asm (
        "LDR R0, =_bss_start\n\t"
        "LDR R1, =_bss_end\n\t"
        "MOV R2, #0\n\t"
        "loop_zero:\n\t"
        "   CMP 	R0, R1\n\t"
        "   BGE 	end_loop\n\t"
        "   STR	    R2, [R0]\n\t"
        "   ADD     R0, R0, #4\n\t"
        "   B 	    loop_zero\n\t"
        "end_loop:\n\t"
    );

    __libc_init_array();

    System_Init();
    
    main();
}

void Default_Handler(void) {

    while (1) {

    }
}

void System_Init(void) {
    // FLASH->ACR &= ~FLASH_ACR_LATENCY_MASK;
    FLASH->ACR |= FLASH_ACR_LATENCY(2);
    FLASH->ACR |= FLASH_ACR_PRFTEN_MASK;
    while ((FLASH->ACR & FLASH_ACR_LATENCY_MASK) != 2) {
    }

    RCC->CR |= RCC_CR_HSI48ON_MASK;
    while (RCC->CR & RCC_CR_HSI48RDY_MASK) {
    }

    RCC->CR &= ~RCC_CR_PLLON_MASK;
    while (RCC->CR & RCC_CR_PLLRDY_MASK) {
    }

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLSRC_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLSRC(2);

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLM_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLM(4);

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLN_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLN(83);

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLQ_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLQ(2);

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLP_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLP(30);

    RCC->PLLCFGR &= ~RCC_PLLCFGR_PLLR_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLR(4);

    RCC->CR |= RCC_CR_PLLON_MASK;

    RCC->PLLCFGR |= RCC_PLLCFGR_PLLREN_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLQEN_MASK;
    RCC->PLLCFGR |= RCC_PLLCFGR_PLLPEN_MASK;

    while (! (RCC->CR & RCC_CR_PLLRDY_MASK)) {
    }

    RCC->CFGR |= RCC_CFGR_SW(2);

    RCC->CFGR &= ~RCC_CFGR_MCOPRE_MASK;
    RCC->CFGR &= ~RCC_CFGR_MCOSEL_MASK;
    RCC->CFGR |= RCC_CFGR_MCOPRE(4);
    RCC->CFGR |= RCC_CFGR_MCOSEL(2);

    RCC->CFGR &= ~RCC_CFGR_MCO2PRE_MASK;
    RCC->CFGR &= ~RCC_CFGR_MCO2SEL_MASK;
    RCC->CFGR |= RCC_CFGR_MCO2PRE(4);
    RCC->CFGR |= RCC_CFGR_MCO2SEL(8);

    
}

void NMI_Handler(void) {

    while (1) {

    }
}

void HardFault_Handler(void) {

    while (1) {

    }
}

void SVCall_Handler(void) {

    while (1) {

    }
}

void PendSV_Handler(void) {

    while(1) {

    }
}

void SysTick_Handler(void) {

    while (1) {

    }
}

/*================== Interrupt Vector Table ==============================================*/
void (* g_pfnVectors[])(void) __attribute__((section (".isr_vector"))) = {
    ((void (*)(void)) (&_estack)),

    /*================== Cortex-M0+ Processor Exceptions =================================*/
    Reset_Handler,
    NMI_Handler,                // -14
    HardFault_Handler,          // -13
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    0,                          // Reserved
    SVCall_Handler,             //  -5
    0,                          // Reserved
    0,                          // Reserved
    PendSV_Handler,             //  -2
    SysTick_Handler,            //  -1

    /*================== STM32G0xxxx Interrupts ===========================================*/
    WWDG_IRQHandler,
    PVD_VDDIO2_IRQHandler,
    RTC_TAMP_IRQHandler,
    FLASH_IRQHandler,
    RCC_CRS_IRQHandler,
    EXTI0_1_IRQHandler,
    EXTI2_3_IRQHandler,
    EXTI4_15_IRQHandler,
    USB_UCPD1_2_IRQHandler,
    DMA1_Channel1_IRQHandler,
    DMA1_Channel2_3_IRQHandler,
    DMA1_Ch4_7_DMA2_Ch1_5_DMAMUX1_OVR_IRQHandler,
    ADC1_COMP_IRQHandler,
    TIM1_BRK_UP_TRG_COM_IRQHandler,
    TIM1_CC_IRQHandler,
    TIM2_IRQHandler,
    TIM3_TIM4_IRQHandler,
    TIM6_DAC_LPTIM1_IRQHandler,
    TIM7_LPTIM2_IRQHandler,
    TIM14_IRQHandler,
    TIM15_IRQHandler,
    TIM16_FDCAN_IT0_IRQHandler,
    TIM7_LPTIM2_IRQHandler,
    I2C1_IRQHandler,
    I2C2_3_IRQHandler,
    SPI1_IRQHandler,
    SPI2_3_IRQHandler,
    USART1_IRQHandler,
    USART2_LPUART2_IRQHandler,
    USART3_4_5_6_LPUART1_IRQHandler,
    CEC_IRQHandler
};

