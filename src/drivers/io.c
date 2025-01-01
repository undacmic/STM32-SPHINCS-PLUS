#include "drivers/io.h"
#include "common/defines.h"

/*
*
* Need to extract the port and pin number from the io_e value.
* With compiler flag '-fshort-enums', each enumeration type has
* the smallest size possible to hold the largest enumerator value,
* in our case 8 bits.
* On STM32G0B1RE we have 6 ports (A-F) and at most 16 pins per port.
*  +--------------+----------------+----------------------+
*  | Zero (1bit)  | Port (3 bits)  |  Pin number (4 bits) |
*  +--------------+----------------+----------------------+
*/
#define IO_PORT_CNT    (6U)
#define IO_PORT_OFFSET (4U)
#define IO_PORT_MASK   (0x7U << IO_PORT_OFFSET)
#define IO_PIN_MASK    (0xFU)


static volatile GPIO_Def *const gpio_ports[IO_PORT_CNT] = {
    GPIOA, GPIOB, GPIOC,
    GPIOD, GPIOE, GPIOF
};

static inline uint8_t io_port(io_e io) {
    return (io & IO_PORT_MASK) >> IO_PORT_OFFSET;
}

static inline uint8_t io_pin(io_e io) {
    return 1 << (io & IO_PIN_MASK);
}


void io_configure(io_e io, io_config config) {
    const uint8_t port = io_port(io);
    const uint8_t pin = io_pin(io);

    io_configure_mode(port, pin, config.mode);

    if (config.mode == IO_ALTERNATE_FUNCTION) {
        io_configure_function(port, pin, config.function);
    }
    
    io_configure_type(port, pin ,config.type);
    io_configure_speed(port, pin ,config.speed);
    io_configure_pull(port, pin ,config.resistor);
    io_configure_value(port, pin, config.out);

}

void io_configure_mode(uint8_t port, uint8_t pin, io_mode_e mode) {

    gpio_ports[port]->MODER &= ~GPIO_MODER_MODE_MASK(pin);
    gpio_ports[port]->MODER |= GPIO_MODER_MODE(mode, pin);
}
void io_configure_function(uint8_t port, uint8_t pin, io_func_e function) {
    if (pin < 8) {
        gpio_ports[port]->AFRL &= ~GPIO_AFRx_AFSEL_MASK(pin);
        gpio_ports[port]->AFRL |= GPIO_AFRx_AFSEL(function, pin);
    } else {
        gpio_ports[port]->AFRH &= ~GPIO_AFRx_AFSEL_MASK(pin);
        gpio_ports[port]->AFRH |= GPIO_AFRx_AFSEL(function, pin);
    }
}
void io_configure_type(uint8_t port, uint8_t pin, io_type_e type) {
    if (type == IO_PUSH_PULL) {
        gpio_ports[port]->OTYPER &= ~GPIO_OTYPER_OT_MASK(pin);
    } else {  
        gpio_ports[port]->OTYPER |= GPIO_OTYPER_OT_MASK(pin);
    }
}
void io_configure_speed(uint8_t port, uint8_t pin, io_speed_e speed) {
    gpio_ports[port]->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED_MASK(pin);
    gpio_ports[port]->OSPEEDR |= GPIO_OSPEEDR_OSPEED(speed, pin);
}
void io_configure_pull(uint8_t port, uint8_t pin, io_pull_e pull) {
    gpio_ports[port]->PUPDR &= ~GPIO_PUPDR_PUPD_MASK(pin);
    gpio_ports[port]->PUPDR |= GPIO_PUPDR_PUPD(pull, pin);
}
void io_configure_value(uint8_t port, uint8_t pin, io_val_e value) {
    if (value == IO_HIGH) {
        gpio_ports[port]->BSRR |= (1 << pin);
    } else {
        gpio_ports[port]->BSRR &= ~(1 << (16 +pin));
    }
}



