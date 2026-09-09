#pragma once

#include <cstdint>
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"
#include "driver/gpio.h"

class GPIO {
public:
    void enableOutput(uint8_t pin);
    void setOutput(uint8_t pin);
    void clearOutput(uint8_t pin);
    void setInput(uint8_t pin);
    void pullUp(uint8_t pin);
};