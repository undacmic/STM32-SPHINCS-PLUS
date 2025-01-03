#include "common/defines.h"
#include "drivers/uart.h"
#include "drivers/io.h"

#define UART_BAUD_RATE  (115200U)
#define UART_PRESCALER  (8U)
#define UART_PRESCLK    (SYSCLK / UART_PRESCALER)    
#define UARTDIV         (UART_PRESCLK / UART_BAUD_RATE)


static void USART_Transmit(uint8_t data)
{
    USART2->TDR = data;
    while(! (USART2->ISR & USART2_ISR_TC_MASK)) {}
}

static void USART_Configure(void) {
    USART2->PRESC &= ~USART2_PRESC_PRESCALER_MASK;
    USART2->PRESC |= USART2_PRESC_PRESCALER(4); 

    USART2->CR1 &= ~USART2_CR1_M0_MASK;
    USART2->CR1 &= ~USART2_CR1_M1_MASK;
    USART2->CR1 &= ~USART2_CR1_OVER8_MASK;

    USART2->BRR &= ~USART2_BRR_BRR_MASK;
    USART2->BRR |= USART2_BRR_BRR(UARTDIV);

    USART2->CR2 &= ~USART2_CR2_STOP_MASK;

    USART2->CR1 |= USART2_CR1_UE_MASK;

    USART2->CR1 |= USART2_CR1_TE_MASK;
}

void USART_Init(void) {
    RCC->APBENR1 |= RCC_APBENR1_USART2EN;

    USART_Configure();
}

// mpaland/printf needs this to be named _putchar
void _putchar (char c) {
    if(c == '\n') {
        _putchar('\r');
    }
    
    USART_Transmit(c);
}