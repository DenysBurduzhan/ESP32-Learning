#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <driver/gpio.h>
#include <esp_timer.h>
#include "sdkconfig.h"
#include "GPIO_driver/GPIO.hpp"

#define yellowLED GPIO_NUM_12
#define redLED GPIO_NUM_13
#define greenLED GPIO_NUM_14
#define button GPIO_NUM_26

volatile bool humanPresent = false;
volatile uint32_t interruptCount = 0;

uint32_t delayTime = 1000;

gpio_num_t leds[] = {yellowLED, redLED, greenLED};
uint16_t ledsLength = sizeof(leds) / sizeof(leds[0]);


int i = 0;

void process(gpio_num_t led_pin, uint32_t delayTime)
{
    GPIO::setOutput(led_pin);
    vTaskDelay(pdMS_TO_TICKS(delayTime));
    GPIO::clearOutput(led_pin);
    i = (i + 1) % ledsLength;
}

void buttonClicked(){
    process(greenLED, delayTime*10);
}

static void IRAM_ATTR button_isr_handler(void *arg)
{
    interruptCount += 1;
    humanPresent = true;
}

extern "C" void app_main()
{
    gpio_config_t io_conf = {
    .pin_bit_mask = (1ULL << button),
    .mode = GPIO_MODE_INPUT,
    .pull_up_en = GPIO_PULLUP_ENABLE,
    .pull_down_en = GPIO_PULLDOWN_DISABLE,
    .intr_type = GPIO_INTR_NEGEDGE
};
    gpio_config(&io_conf);

    for (int j = 0; j < ledsLength; j++){
        GPIO::initGPIO(leds[j]);
        GPIO::enableOutput(leds[j]);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    
    gpio_install_isr_service(0);
    gpio_isr_handler_add(button, button_isr_handler, NULL);

    while (true)
    {
      if(humanPresent){
        buttonClicked();
        printf("%ld\n", interruptCount);
        humanPresent = false;
       }else if(!humanPresent){
        process(leds[i], delayTime);
       }
    }
}
