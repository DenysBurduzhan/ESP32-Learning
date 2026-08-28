#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"

#define yellowLED 12
#define redLED 13
#define greenLED 14
#define button 26
uint32_t startTime;
volatile bool humanPresent = false;

void IRAM_ATTR ISR(){
  humanPresent = true;
}

void setup() {
  Serial.begin(9600);
  REG_SET_BIT(GPIO_ENABLE_REG,
            (1 << yellowLED) |
            (1 << redLED) |
            (1 << greenLED));
  startTime = millis();
  REG_CLR_BIT(GPIO_ENABLE_REG, (1 << button));
  REG_SET_BIT(button, FUN_PU);
  attachInterrupt(digitalPinToInterrupt(button), ISR, FALLING);
}

void buttonClicked(){
  uint32_t currentTime = millis();
    REG_WRITE(GPIO_OUT_W1TC_REG, 
            (1 << yellowLED) |
            (1 << redLED) |
            (1 << greenLED));
  if(currentTime - startTime > 10000){
    humanPresent = false;
    startTime = currentTime;
  }
}

void loop() {
uint32_t currentTime = millis();
if(!humanPresent){
if(currentTime - startTime <= 1000 ){
  REG_WRITE(GPIO_OUT_W1TC_REG, 
            1 << redLED);
  REG_WRITE(GPIO_OUT_W1TS_REG, 
            1 << greenLED);
}else if(currentTime - startTime <= 2000){
  REG_WRITE(GPIO_OUT_W1TC_REG, 
            1 << greenLED);
  REG_WRITE(GPIO_OUT_W1TS_REG, 
            1 << yellowLED);
}else if(currentTime - startTime <= 3000){
  REG_WRITE(GPIO_OUT_W1TC_REG, 
            1 << yellowLED);
  REG_WRITE(GPIO_OUT_W1TS_REG, 
            1 << redLED);
}else {
  startTime = currentTime;
}
}else{
  buttonClicked();
}
}


