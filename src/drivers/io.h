#ifndef IO_H
#define IO_H

#include <stdint.h>

/**
 * I/O wrapper over the crude registers provided inside the STM32G0x1 Reference Manual
 * handling pinmapping and configuration.
 */

typedef enum {
    IO_A0, IO_A1, IO_A2, IO_A3, IO_A4, IO_A5, IO_A6, IO_A7, IO_A8, IO_A9, IO_A10, IO_A11, IO_A12, IO_A13, IO_A14, IO_A15,
    IO_B0, IO_B1, IO_B2, IO_B3, IO_B4, IO_B5, IO_B6, IO_B7, IO_B8, IO_B9, IO_B10, IO_B11, IO_B12, IO_B13, IO_B14, IO_B15,
    IO_C0, IO_C1, IO_C2, IO_C3, IO_C4, IO_C5, IO_C6, IO_C7, IO_C8, IO_C9, IO_C10, IO_C11, IO_C12, IO_C13, IO_C14, IO_C15,
    IO_D0, IO_D1, IO_D2, IO_D3, IO_D4, IO_D5, IO_D6, IO_D7, IO_D8, IO_D9, IO_D10, IO_D11, IO_D12, IO_D13, IO_D14, IO_D15,
    IO_E0, IO_E1, IO_E2, IO_E3, IO_E4, IO_E5, IO_E6, IO_E7, IO_E8, IO_E9, IO_E10, IO_E11, IO_E12, IO_E13, IO_E14, IO_E15,
    IO_F0, IO_F1, IO_F2, IO_F3, IO_F4, IO_F5, IO_F6, IO_F7, IO_F8, IO_F9, IO_F10, IO_F11, IO_F12, IO_F13, IO_F14, IO_F15
} io_generic_e;

typedef enum {
    IO_USART2_TX = IO_A2,
    IO_USART2_RX = IO_A3,
    IO_USER_LED = IO_A5 
} io_e;

typedef enum {
    IO_GPIO_INPUT,
    IO_GPIO_OUTPUT,
    IO_ALTERNATE_FUNCTION,
    IO_ANALOG
} io_mode_e;

typedef enum {
    IO_AF0,
    IO_AF1,
    IO_AF2,
    IO_AF3,
    IO_AF4,
    IO_AF5,
    IO_AF6,
    IO_AF7
} io_func_e;

typedef enum {
    IO_PUSH_PULL,
    IO_OPEN_DRAIN
} io_type_e;

typedef enum {
    IO_VERY_LOW_S,
    IO_LOW_S,
    IO_HIGH_S,
    IO_VERY_HIGH_S
} io_speed_e;

typedef enum {
    IO_NONE,
    IO_UP,
    IO_DOWN
} io_pull_e;

typedef enum {
    IO_LOW,
    IO_HIGH
} io_val_e;


typedef struct {
    io_mode_e mode;
    io_func_e function;
    io_type_e type;
    io_speed_e speed;
    io_pull_e resistor;
    io_val_e out;
} io_config;

void io_init(void);
void io_configure(io_e io, io_config config);
void io_configure_mode(uint8_t port, uint8_t pin, io_mode_e mode);
void io_configure_function(uint8_t port, uint8_t pin, io_func_e function);
void io_configure_type(uint8_t port, uint8_t pin, io_type_e type);
void io_configure_speed(uint8_t port, uint8_t pin, io_speed_e speed);
void io_configure_pull(uint8_t port, uint8_t pin, io_pull_e pull);
void io_configure_value(uint8_t port, uint8_t pin, io_val_e value);

#endif // IO_H
