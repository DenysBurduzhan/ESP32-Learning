
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define yellowLED GPIO_NUM_12
#define redLED GPIO_NUM_13
#define greenLED GPIO_NUM_14
#define button GPIO_NUM_26
volatile bool humanPresent = false;

uint32_t delayTime = 1000;

gpio_num_t leds[] = {yellowLED, redLED, greenLED};
uint16_t ledsLength = sizeof(leds) / sizeof(leds[0]);

int i = 0;

void process(gpio_num_t led_pin, uint32_t delayTime)
{
    gpio_set_level(led_pin, 1);
    vTaskDelay(pdMS_TO_TICKS(delayTime));
    gpio_set_level(led_pin, 0);
    i = (i + 1) % ledsLength;
}

extern "C" void app_main()
{
    gpio_set_direction(yellowLED, GPIO_MODE_OUTPUT);
    gpio_set_direction(redLED, GPIO_MODE_OUTPUT);
    gpio_set_direction(greenLED, GPIO_MODE_OUTPUT);
    gpio_set_direction(button, GPIO_MODE_INPUT);
    gpio_set_pull_mode(button, GPIO_PULLUP_ONLY);

    while (true)
    {
       
            process(leds[i], delayTime);
    }
}
