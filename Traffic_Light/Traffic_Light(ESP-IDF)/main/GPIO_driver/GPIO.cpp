#include "GPIO.hpp"
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "driver/gpio.h"

bool GPIO::initGPIO(uint8_t pin){
    switch (pin){
        case 12:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_MTDI_GPIO12);
            break;
        case 13:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U, FUNC_MTCK_GPIO13);
            break;
        case 14:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U, FUNC_MTMS_GPIO14);
            break;
        default: return false;
    }
    return true;
}
void GPIO::enableOutput(uint8_t pin) {
    REG_SET_BIT(GPIO_ENABLE_REG, (1UL << pin));
}

void GPIO::setOutput(uint8_t pin) {
    REG_WRITE(GPIO_OUT_W1TS_REG, (1UL << pin));
}

void GPIO::clearOutput(uint8_t pin) {
    REG_WRITE(GPIO_OUT_W1TC_REG, (1UL << pin));
}

void GPIO::setInput(uint8_t pin) {
    REG_CLR_BIT(GPIO_ENABLE_REG, (1UL << pin));
}

void GPIO::pullUp(uint8_t pin) {
    if (pin >= 34) return; 
    gpio_pullup_en((gpio_num_t)pin);
    gpio_pulldown_dis((gpio_num_t)pin);
}