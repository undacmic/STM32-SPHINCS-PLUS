#include <stdint.h>

/*================== Peripheral Devices =========================================*/

// Nested Vectored Interrupt Controller
typedef struct {
    volatile uint32_t ISER;     /* Offset 0x000 Interrupt set-enable register    */
    uint32_t RESERVED0[31U];    
    volatile uint32_t ICER;     /* Offset 0x080 Interrupt clear-enable register  */
    uint32_t RESERVED1[31U];
    volatile uint32_t ISPR;     /* Offset 0x100 Interrupt set-pending register   */
    uint32_t RESERVED2[31U];
    volatile uint32_t ICPR;     /* Offset 0x180 Interrupt clear-pending register */
    uint32_t RESERVED3[31U];
    uint32_t RESERVED4[64u];
    volatile uint32_t IPR[8U];  /* Offset 0x300 Interrupt priority registers     */
} NIVC_Def;

// Reset and Clock Control
typedef struct {
    volatile uint32_t CR;
    volatile uint32_t ICSCR;
    volatile uint32_t CFGR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t RESERVED;
    volatile uint32_t CRRCR;
    volatile uint32_t CIER;
    volatile uint32_t CIFR;
    volatile uint32_t CICR;
    volatile uint32_t IOPRSTR;
    volatile uint32_t AHBRSTR;
    volatile uint32_t APBRSTR1;
    volatile uint32_t APBRSTR2;
    volatile uint32_t IOPENR;
    volatile uint32_t AHBENR;
    volatile uint32_t APBENR1;
    volatile uint32_t APBENR2;
    volatile uint32_t IOPSMENR;
    volatile uint32_t AHBSMENR;
    volatile uint32_t APBSMENR1;
    volatile uint32_t APBSMENR2;
    volatile uint32_t CCIPR;
    volatile uint32_t CCIPR2;
    volatile uint32_t BDCR;
    volatile uint32_t CSR;
} RCC_Def;

// Universal Synchronous/Asynchronous Receiver Transmitter Control
typedef struct {
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t CR3;
    volatile uint32_t BRR;
    volatile uint32_t GTPR;
    volatile uint32_t RTOR;
    volatile uint32_t RQR;
    volatile uint32_t ISR;
    volatile uint32_t ICR;
    volatile uint32_t RDR;
    volatile uint32_t TDR;
    volatile uint32_t PRESC;
} USART_Def; 

// General Purpose Input/Output
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFRL;
    volatile uint32_t AFRH;
    volatile uint32_t BRR;
} GPIO_Def; 

// Embedded Flash Memory
typedef struct {
    volatile uint32_t ACR;
    volatile uint32_t RESERVED0;
    volatile uint32_t KEYR;
    volatile uint32_t OPTKEYR;
    volatile uint32_t SR;
    volatile uint32_t CR;
    volatile uint32_t ECCR;
    volatile uint32_t ECCR2;
    volatile uint32_t OPTR;
    volatile uint32_t PCROP1ASR;
    volatile uint32_t PCROP1AER;
    volatile uint32_t WRP1AR;
    volatile uint32_t WRP1BR;
    volatile uint32_t PCROP1BSR;
    volatile uint32_t PCROP1BER;
    volatile uint32_t RESERVED1;
    volatile uint32_t PCROP2ASR;
    volatile uint32_t PCROP2AER;
    volatile uint32_t WRP2BR;
    volatile uint32_t PCROP2BSR;
    volatile uint32_t RESERVED2;
    volatile uint32_t SECR;
} FLASH_Def;

// Timer
typedef struct {
    volatile uint16_t CR1;
    volatile uint16_t RESERVED0;
    volatile uint16_t CR2;
    volatile uint16_t RESERVED1;
    volatile uint32_t RESERVED2;
    volatile uint16_t DIER;
    volatile uint16_t RESERVED3;
    volatile uint16_t SR;
    volatile uint16_t RESERVED4;
    volatile uint16_t EGR;
    volatile uint16_t RESERVED5;
    volatile uint32_t CCMR1;
    volatile uint32_t RESERVED6;
    volatile uint16_t CCER;
    volatile uint16_t RESERVED7;
    volatile uint32_t CNT;
    volatile uint16_t PSC;
    volatile uint16_t RESERVED8;
    volatile uint16_t ARR;
    volatile uint16_t RESERVED9;
    volatile uint16_t RCR;
    volatile uint16_t RESERVED10;
    volatile uint16_t CCR1;
    volatile uint16_t RESERVED11;
    volatile uint16_t CCR2;
    volatile uint16_t RESERVED12;
    volatile uint32_t RESERVED13[2];
    volatile uint32_t BDTR;
    volatile uint16_t DCR;
    volatile uint16_t RESERVED14;
    volatile uint16_t DMAR;
    volatile uint16_t RESERVED15;
    volatile uint32_t RESERVED16[4];
    volatile uint32_t AF1;
    volatile uint32_t RESERVED17;
    volatile uint32_t TISEL;
} TIM_Def;

// Direct Memory Access
typedef struct  {
    volatile uint32_t ISR;
    volatile uint32_t IFCR;
    volatile uint32_t CCR1;
    volatile uint32_t CNDTR1;
    volatile uint32_t CPAR1;
    volatile uint32_t CMAR1;
    volatile uint32_t RESERVED0;
    volatile uint32_t CCR2;
    volatile uint32_t CNDTR2;
    volatile uint32_t CPAR2;
    volatile uint32_t CMAR2;
    volatile uint32_t RESERVED1;
    volatile uint32_t CCR3;
    volatile uint32_t CNDTR3;
    volatile uint32_t CPAR3;
    volatile uint32_t CMAR3;
    volatile uint32_t RESERVED2;
    volatile uint32_t CCR4;
    volatile uint32_t CNDTR4;
    volatile uint32_t CPAR4;
    volatile uint32_t CMAR4;
    volatile uint32_t RESERVED3;
    volatile uint32_t CCR5;
    volatile uint32_t CNDTR5;
    volatile uint32_t CPAR5;
    volatile uint32_t CMAR5;
    volatile uint32_t RESERVED4;
    volatile uint32_t CCR6;
    volatile uint32_t CNDTR6;
    volatile uint32_t CPAR6;
    volatile uint32_t CMAR6;
    volatile uint32_t RESERVED5;
    volatile uint32_t CCR7;
    volatile uint32_t CNDTR7;
    volatile uint32_t CPAR7;
    volatile uint32_t CMAR7;
} DMA1_Def;

// Direct Memory Access Multiplexer
typedef struct {
    volatile uint32_t C0CR;
    volatile uint32_t C1CR;
    volatile uint32_t C2CR;
    volatile uint32_t C3CR;
    volatile uint32_t C4CR;
    volatile uint32_t C5CR;
    volatile uint32_t C6CR;
    volatile uint32_t C7CR;
    volatile uint32_t C8CR;
    volatile uint32_t C9CR;
    volatile uint32_t C10CR;
    volatile uint32_t C11CR;
    volatile uint32_t RESERVED0[20];
    volatile uint32_t CSR;
    volatile uint32_t CFR;
    volatile uint32_t RESERVED1[30];
    volatile uint32_t RG0CR;
    volatile uint32_t RG1CR;
    volatile uint32_t RG2CR;
    volatile uint32_t RG3CR;
    volatile uint32_t RESERVED2[12];
    volatile uint32_t RGSR;
    volatile uint32_t RGCFR;
} DMAMUX_Def;


/*================== Clock ===============================================================*/

#define CYCLES_1MHZ                                 (1000000U)
#define CYCLES_64MHZ                                (64U * CYCLES_1MHZ)
#define CYCLES_16MHZ                                (16U * CYCLES_1MHZ)
#define SYSCLK                                      (CYCLES_64MHZ)

/*================== ARM Cortex-M0+ PRIMASK ==============================================*/

static inline void __enable_interrupts(void)        __attribute__((always_inline));
static inline void __disable_interrupts(void)       __attribute__((always_inline));


/*================== Macros ==============================================================*/

#define PPB_BASE                    (0xE0000000)
#define NVIC_BASE                   (PPB_BASE + 0xE100)
#define NVIC                        ((NIVC_Def*) NVIC_BASE)

#define RCC_BASE                    (0x40021000)
#define RCC                         ((RCC_Def*) RCC_BASE)
#define RCC_CR_PLLON_MASK           (0x1UL  << 24)
#define RCC_CR_PLLRDY_MASK          (0x1UL  << 25)
#define RCC_CR_HSI48ON_MASK         (0x1UL  << 22)
#define RCC_CR_HSI48RDY_MASK        (0x1UL  << 23)
#define RCC_CFGR_SW_MASK            (0x3UL  << 0)
#define RCC_CFGR_SW(x)              ((x & 0x3UL) << 0)
#define RCC_CFGR_SWS_PLL_MASK       (0x1UL  << 4)
#define RCC_CFGR_PPRE_MASK          (0x7UL  << 12)
#define RCC_CFGR_PPRE(x)            ((x & 0x7UL) << 12)
#define RCC_CFGR_MCOSEL_MASK        (0xFUL  << 24)
#define RCC_CFGR_MCOSEL(x)          ((x & 0xFUL) << 24)
#define RCC_CFGR_MCO2SEL_MASK       (0xFUL  << 16)
#define RCC_CFGR_MCO2SEL(x)         ((x & 0xFUL) << 16)
#define RCC_CFGR_MCOPRE_MASK        (0xFUL  << 28)
#define RCC_CFGR_MCOPRE(x)          ((x & 0xFUL) << 28)
#define RCC_CFGR_MCO2PRE_MASK       (0xFUL  << 20)
#define RCC_CFGR_MCO2PRE(x)         ((x & 0xFUL) << 20)
#define RCC_PLLCFGR_PLLSRC_MASK     (0x3UL  << 0)
#define RCC_PLLCFGR_PLLSRC(x)       ((x & 0x3UL) << 0)
#define RCC_PLLCFGR_PLLM_MASK       (0x7UL  << 4)
#define RCC_PLLCFGR_PLLM(x)         ((x & 0x7UL) << 4)
#define RCC_PLLCFGR_PLLN_MASK       (0x7FUL << 8)
#define RCC_PLLCFGR_PLLN(x)         ((x & 0x7FUL) << 8)
#define RCC_PLLCFGR_PLLPEN_MASK     (0x1UL  << 16)
#define RCC_PLLCFGR_PLLP_MASK       (0x3FUL << 17)
#define RCC_PLLCFGR_PLLP(x)         ((x & 0x3FUL) << 17)
#define RCC_PLLCFGR_PLLQEN_MASK     (0x1UL  << 24)
#define RCC_PLLCFGR_PLLQ_MASK       (0x7UL  << 25)
#define RCC_PLLCFGR_PLLQ(x)         ((x & 0x7UL) << 25)
#define RCC_PLLCFGR_PLLREN_MASK     (0x1UL  << 28)
#define RCC_PLLCFGR_PLLR_MASK       (0x7UL  << 29)
#define RCC_PLLCFGR_PLLR(x)         ((x & 0x7UL) << 29) 
#define RCC_AHBENR_DMA1EN           (0x1UL  << 0)   
#define RCC_APBENR1_USART2EN        (0x1UL  << 17)
#define RCC_APBENR2_TIM15EN         (0x1UL  << 16)
#define RCC_APBENR2_TIM16EN         (0x1UL  << 17)
#define RCC_IOPENR_GPIOAEN_MASK     (0x1UL  << 0)
#define RCC_CCIPR_USART2SEL_MASK    (0x3UL  << 2)
#define RCC_CCIPR_USART2SEL(x)      ((x & 0x3UL) << 2)
#define RCC_CCIPR_TIM15SEL_MASK     (0x1UL  << 24)

#define USART2_BASE                 (0x40004400)
#define USART2                      ((USART_Def*) USART2_BASE)
#define USART2_CR1_UE_MASK          (0x1UL  << 0)
#define USART2_CR1_RE_MASK          (0x1UL  << 2)
#define USART2_CR1_TE_MASK          (0x1UL  << 3)
#define USART2_CR1_PCE_MASK         (0x1UL  << 10)
#define USART2_CR1_M0_MASK          (0x1UL  << 12)
#define USART2_CR1_OVER8_MASK       (0x1UL  << 15)
#define USART2_CR1_M1_MASK          (0x1UL  << 28)
#define USART2_CR1_TCIE_MASK        (0x1UL  << 6)
#define USART2_CR2_STOP_MASK        (0x3UL  << 12)
#define USART2_CR2_STOP(x)          ((x & 0x3UL) << 12)
#define USART2_PRESC_PRESCALER_MASK (0xFUL  << 0)
#define USART2_PRESC_PRESCALER(x)   ((x & 0xFUL)  << 0)
#define USART2_BRR_BRR_MASK         (0x7FFFUL << 0)
#define USART2_BRR_BRR(x)           ((x & 0x7FFFUL) << 0)
#define USART2_ISR_TC_MASK          (0x1UL  << 6)
#define USART2_ICR_TCCF_MASK        (0x1UL  << 6)

#define GPIOA_BASE                  (0x50000000)
#define GPIOA                       ((GPIO_Def*) GPIOA_BASE)
#define GPIOB_BASE                  (0x50000400)
#define GPIOB                       ((GPIO_Def*) GPIOB_BASE)
#define GPIOC_BASE                  (0x50000800)
#define GPIOC                       ((GPIO_Def*) GPIOC_BASE)
#define GPIOD_BASE                  (0x50000C00)
#define GPIOD                       ((GPIO_Def*) GPIOD_BASE)
#define GPIOE_BASE                  (0x50001000)
#define GPIOE                       ((GPIO_Def*) GPIOE_BASE)
#define GPIOF_BASE                  (0x50001400)
#define GPIOF                       ((GPIO_Def*) GPIOF_BASE)
#define GPIO_MODER_MODE_MASK(y)     (0x3UL  << 2*y)
#define GPIO_MODER_MODE(x, y)       ((x & 0x3UL)  << 2*y)
#define GPIO_AFRx_AFSEL_MASK(y)     (0xFUL  << 4*y)
#define GPIO_AFRx_AFSEL(x, y)       ((x & 0xFUL)  << 4*y)
#define GPIO_OTYPER_OT_MASK(y)      (0x1UL  << y)
#define GPIO_OSPEEDR_OSPEED_MASK(y) (0x3UL  << 2*y)
#define GPIO_OSPEEDR_OSPEED(x, y)   ((x & 0x3UL)  << 2*y)
#define GPIO_PUPDR_PUPD_MASK(y)     (0x3UL  << 2*y)
#define GPIO_PUPDR_PUPD(x, y)       ((x & 0x3UL)  << 2*y)

#define FLASH_BASE                  (0x40022000)
#define FLASH                       ((FLASH_Def*) FLASH_BASE)
#define FLASH_ACR_LATENCY_MASK      (0x7UL  << 0)
#define FLASH_ACR_LATENCY(x)        ((x & 0x7UL)  << 0)
#define FLASH_ACR_PRFTEN_MASK       (0x1UL  << 8)

#define TIM15_BASE                  (0x40014000)
#define TIM16_BASE                  (0x40014400)
#define TIM15                       ((TIM_Def*) TIM15_BASE)
#define TIM16                       ((TIM_Def*) TIM16_BASE)
#define TIM_CR1_CEN_MASK            (0x1  << 0)
#define TIM_CCMR1_CC1S_MASK         (0x3UL  << 0)
#define TIM_CCMR1_CC1S(x)           ((x & 0x3UL)  << 0)
#define TIM_CCMR1_CC2S_MASK         (0x3UL  << 8)
#define TIM_CCMR1_CC2S(x)           ((x & 0x3UL)  << 8)
#define TIM_CCER_CC1NP_MASK         (0x1  << 3)
#define TIM_CCER_CC1P_MASK          (0x1  << 1)
#define TIM_CCER_CC2NP_MASK         (0x1  << 7)
#define TIM_CCER_CC2P_MASK          (0x1  << 5)
#define TIM_CCER_CC1E_MASK          (0x1  << 0)
#define TIM_CCER_CC2E_MASK          (0x1  << 4)
#define TIM_DIER_CC1IE_MASK         (0x1  << 1)
#define TIM_DIER_CC2IE_MASK         (0x1  << 2)
#define TIM_DIER_CC1DE_MASK         (0x1  << 9)
#define TIM_SR_CC1IF_MASK           (0x1  << 1)
#define TIM_SR_CC2IF_MASK           (0x1  << 2)
#define TIM_TISEL_TI1SEL_MASK       (0XFUL << 0)
#define TIM_TISEL_TI1SEL(x)         ((x & 0XFUL) << 0)
#define TIM_TISEL_TI2SEL_MASK       (0XFUL << 8)
#define TIM_TISEL_TI2SEL(x)         ((x & 0XFUL) << 8)

#define DMAMUX_BASE                 (0x40020800)
#define DMAMUX                      ((DMAMUX_Def*) DMAMUX_BASE)
#define DMAMUX_CxCR_DMAREQ_ID(x)    ((x & 0x7FUL) << 0)

#define DMA1_BASE                   (0x40020000)
#define DMA1                        ((DMA1_Def*) DMA1_BASE)
#define DMA1_ISR_TF_FLAG(x)         (0x1UL  << (2 * x - 1))
#define DMA1_IFCR_CTCIF(x)          (0x1UL  << (2 * x - 1))
#define DMA1_CCR_PL_MASK            (0x3UL  << 12)
#define DMA1_CCR_PL(x)              ((x & 0x3UL) << 12)
#define DMA1_CCR_MSIZE_MASK         (0x3UL  << 10)
#define DMA1_CCR_MSIZE(x)           ((x & 0x3UL) << 10)
#define DMA1_CCR_PSIZE_MASK         (0x3UL  << 8)
#define DMA1_CCR_PSIZE(x)           ((x & 0x3UL) << 8)
#define DMA1_CCR_MINC_MASK          (0x1UL  << 7)
#define DMA1_CCR_CIRC_MASK          (0x1UL  << 5)
#define DMA1_CCR_DIR_MASK           (0x1UL  << 4)
#define DMA1_CCR_TCIE_MASK          (0x1UL  << 1)
#define DMA1_CCR_EN_MASK            (0x1UL  << 0)

/*================== Utils =================================================================*/
#define ARRAY_SIZE(array)           (sizeof(array) / sizeof(array[0]))
#define INTERRUPT_VECTOR            void __attribute__((interrupt("IRQ")))

static inline void NVIC_EnableIRQ(uint8_t IRQn) {
    NVIC->ISER |= (1 << IRQn);
}

/*================== Function Definitions ==================================================*/

/*
* Enables IRQ interrupts by clearing special-purpose register PRIMASK
*/
static inline void __enable_interrupts(void) {
    __asm ("cpsie i" : : : "memory");
}

/*
* Disables IRQ interrupts by setting special-purpose register PRIMASK
*/
static inline void __disable_interrupts(void) {
    __asm ("cpsid i" : : : "memory");
}


