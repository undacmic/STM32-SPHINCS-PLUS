#include "common/defines.h"
#include "drivers/io.h"
#include "drivers/uart.h"
#include "external/printf/printf.h"

int main () {
    io_init();

    __enable_interrupts();

    USART_Init();

    while (1) {
        printf("OK\n");
    }

    return 0;
} 
