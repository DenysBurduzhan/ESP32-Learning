#include "GPIO.hpp"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "driver/gpio.h"

void GPIO::enableOutput(uint8_t pin) {
    REG_SET_BIT(GPIO_ENABLE_REG, (1 << pin));
}

void GPIO::setOutput(uint8_t pin) {
    REG_WRITE(GPIO_OUT_W1TS_REG, (1 << pin));
}

void GPIO::clearOutput(uint8_t pin) {
    REG_WRITE(GPIO_OUT_W1TC_REG, (1 << pin));
}

void GPIO::setInput(uint8_t pin) {
    REG_CLR_BIT(GPIO_ENABLE_REG, (1 << pin));
}

void GPIO::pullUp(uint8_t pin) {
    if (pin >= 34) return; 
    gpio_pullup_en((gpio_num_t)pin);
    gpio_pulldown_dis((gpio_num_t)pin);
}