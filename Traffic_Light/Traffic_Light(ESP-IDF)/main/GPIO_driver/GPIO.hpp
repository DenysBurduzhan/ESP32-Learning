#pragma once

#include <cstdint>
#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"


class GPIO {
public:
    static bool initGPIO(uint8_t pin);
    static void enableOutput(uint8_t pin);
    static void setOutput(uint8_t pin);
    static void clearOutput(uint8_t pin);
    static void setInput(uint8_t pin);
    static void pullUp(uint8_t pin);
};