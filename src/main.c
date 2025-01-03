#include "common/defines.h"
#include "drivers/io.h"
#include "drivers/uart.h"
#include "external/printf/printf.h"

int main () {
    io_init();
    USART_Init();

    while (1) {
        _putchar('O');
    }

    return 0;
} 
