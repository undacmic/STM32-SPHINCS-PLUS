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

/*================== Clock ===============================================================*/

#define CYCLES_1MHZ                                 (1000000U)
#define CYCLES_64MHZ                                (64U * CYCLES_1MHZ)
#define SYSCLK                                      (CYCLES_64MHZ)

/*================== ARM Cortex-M0+ PRIMASK ==============================================*/

static inline void __enable_interrupts(void)        __attribute__((always_inline));
static inline void __disable_interrupts(void)       __attribute__((always_inline));

/*================== Interrupt Vector Prototypes =========================================*/

void Default_Handler(void)                          __attribute__((weak));
void System_Init();

/*================== Internal Interrupts =================================================*/

void Reset_Handler()                                __attribute__((weak));
void NMI_Handler()                                  __attribute__((weak));  // Non Maskable Interrupt
void HardFault_Handler()                            __attribute__((weak));  // Cortex-M Hard Fault Interrupt 
void SVCall_Handler()                               __attribute__((weak));  // Cortex-M SV Call Interrupt 
void PendSV_Handler()                               __attribute__((weak));  // Cortex-M Pend SV Interrupt 
void SysTick_Handler()                              __attribute__((weak));  // Cortex-M System Tick Interrupt 

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

/*================== Macros ==============================================================*/

#define PPB_BASE                    (0xE0000000)
#define NVIC_NASE                   (PPB_BASE + 0xE100)

#define RCC_BASE                    (0x40021000)
#define RCC                         ((RCC_Def*) RCC_BASE)
#define RCC_CR_PLLON_MASK           (0x1UL  << 24)
#define RCC_CR_PLLRDY_MASK          (0x1UL  << 25)
#define RCC_CFGR_SW_MASK            (0x3UL  << 0)
#define RCC_CFGR_SW(x)              ((x & 0x3UL) << 0)
#define RCC_CFGR_SWS_PLL_MASK       (0x1UL  << 4)
#define RCC_CFGR_PPRE_MASK          (0x7UL  << 12)
#define RCC_CFGR_PPRE(x)            ((x & 0x7UL) << 12)
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
#define RCC_APBENR1_USART2EN        (0X1UL  << 17)
#define RCC_IOPENR_GPIOAEN_MASK     (0x1UL  << 0)

#define USART2_BASE                 (0x40004400)
#define USART2                      ((USART_Def*) USART2_BASE)
#define USART2_CR1_UE_MASK          (0x1UL  << 0)
#define USART2_CR1_RE_MASK          (0x1UL  << 2)
#define USART2_CR1_TE_MASK          (0x1UL  << 3)
#define USART2_CR1_PCE_MASK         (0x1UL  << 10)
#define USART2_CR1_M0_MASK          (0x1UL  << 12)
#define USART2_CR1_OVER8_MASK       (0x1UL  << 15)
#define USART2_CR1_M1_MASK          (0x1UL  << 28)
#define USART2_CR2_STOP_MASK        (0x3UL  << 12)
#define USART2_CR2_STOP(x)          ((x & 0x3UL) << 12)
#define USART2_PRESC_PRESCALER_MASK (0xFUL  << 0)
#define USART2_PRESC_PRESCALER(x)   ((x & 0xFUL)  << 0)
#define USART2_BRR_BRR_MASK         (0x7FFFUL << 0)
#define USART2_BRR_BRR(x)           ((x & 0x7FFFUL) << 0)
#define USART2_ISR_TC_MASK          (0x1UL  << 6)

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

/*================== Utils =================================================================*/
#define ARRAY_SIZE(array)           (sizeof(array) / sizeof(array[0]))

/*================== Function Definitions ==================================================*/

void Default_Handler(void) {

    while (1) {

    }
}

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


