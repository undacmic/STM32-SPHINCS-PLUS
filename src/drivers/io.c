#include "common/defines.h"
#include "drivers/io.h"

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
#define IO_PIN_CNT     (16U)
#define IO_PORT_OFFSET (4U)
#define IO_PORT_MASK   (0x7U << IO_PORT_OFFSET)
#define IO_PIN_MASK    (0xFU)

static volatile GPIO_Def *const gpio_ports[IO_PORT_CNT] = {
    GPIOA, GPIOB, GPIOC,
    GPIOD, GPIOE, GPIOF
};
static const io_config io_default_configs[IO_PORT_CNT * IO_PIN_CNT] = {
    [0 ... (IO_PORT_CNT * IO_PIN_CNT -1)] = { IO_ANALOG, 0, 0, 0, 0, 0 },
    [IO_USART2_TX] = { IO_ALTERNATE_FUNCTION,  IO_AF1, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_LOW },
    [IO_USART2_RX] = { IO_ALTERNATE_FUNCTION,  IO_AF1, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_LOW },
    [IO_USER_LED] = { IO_GPIO_OUTPUT, 0, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_HIGH },
    [IO_MCO] = { IO_ALTERNATE_FUNCTION, IO_AF0, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_LOW },
    [IO_MCO2] = { IO_ALTERNATE_FUNCTION, IO_AF3, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_LOW },
    [IO_B14] = { IO_ALTERNATE_FUNCTION, IO_AF5, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_LOW},
    [IO_B15] = { IO_ALTERNATE_FUNCTION, IO_AF5, IO_PUSH_PULL, IO_VERY_HIGH_S, IO_NONE, IO_LOW}
};

static inline uint8_t io_port(io_e io) {
    return (io & IO_PORT_MASK) >> IO_PORT_OFFSET;
}
static inline uint8_t io_pin(io_e io) {
    return io & IO_PIN_MASK;
}

static void io_configure_mode(uint8_t port, uint8_t pin, io_mode_e mode) {

    gpio_ports[port]->MODER &= ~GPIO_MODER_MODE_MASK(pin);
    gpio_ports[port]->MODER |= GPIO_MODER_MODE(mode, pin);
}
static void io_configure_function(uint8_t port, uint8_t pin, io_func_e function) {
    if (pin < 8) {
        gpio_ports[port]->AFRL &= ~GPIO_AFRx_AFSEL_MASK(pin);
        gpio_ports[port]->AFRL |= GPIO_AFRx_AFSEL(function, pin);
    } else {
        pin = pin - 8;
        gpio_ports[port]->AFRH &= ~GPIO_AFRx_AFSEL_MASK(pin);
        gpio_ports[port]->AFRH |= GPIO_AFRx_AFSEL(function, pin);
    }
}
static void io_configure_type(uint8_t port, uint8_t pin, io_type_e type) {
    if (type == IO_PUSH_PULL) {
        gpio_ports[port]->OTYPER &= ~GPIO_OTYPER_OT_MASK(pin);
    } else {  
        gpio_ports[port]->OTYPER |= GPIO_OTYPER_OT_MASK(pin);
    }
}
static void io_configure_speed(uint8_t port, uint8_t pin, io_speed_e speed) {
    gpio_ports[port]->OSPEEDR &= ~GPIO_OSPEEDR_OSPEED_MASK(pin);
    gpio_ports[port]->OSPEEDR |= GPIO_OSPEEDR_OSPEED(speed, pin);
}
static void io_configure_pull(uint8_t port, uint8_t pin, io_pull_e pull) {
    gpio_ports[port]->PUPDR &= ~GPIO_PUPDR_PUPD_MASK(pin);
    gpio_ports[port]->PUPDR |= GPIO_PUPDR_PUPD(pull, pin);
}
static void io_configure_value(uint8_t port, uint8_t pin, io_val_e value) {
    if (value == IO_HIGH) {
        gpio_ports[port]->BSRR |= (1 << pin);
    } else {
        gpio_ports[port]->BSRR &= ~(1 << (16 +pin));
    }
}

static void io_configure(io_e io, io_config config) {
    const uint8_t port = io_port(io);
    const uint8_t pin = io_pin(io);

    RCC->IOPENR |= (1 << port);

    io_configure_mode(port, pin, config.mode);

    if (config.mode == IO_ALTERNATE_FUNCTION) {
        io_configure_function(port, pin, config.function);
    }
    
    io_configure_type(port, pin ,config.type);
    io_configure_speed(port, pin ,config.speed);
    io_configure_pull(port, pin ,config.resistor);
    io_configure_value(port, pin, config.out);

}

void io_init(void) {
    for(io_e io = (io_e) IO_A0; io < ARRAY_SIZE(io_default_configs); io++) {
        if(io_default_configs[io].mode == IO_ANALOG) {
            continue;
        }

        io_configure(io, io_default_configs[io]);
    }
}



