#include "soc/gpio_reg.h"
#include "soc/io_mux_reg.h"

const uint16_t LEDpin = 13;
const uint16_t switchPin = 25;
const uint16_t piezoPin = 32;
const uint32_t interval = 10000; 

volatile bool motionDetected = false;
volatile bool newMotion = false;
uint32_t startAlarmAndSignalTime;
uint8_t value = 0;


void IRAM_ATTR motionISR() 
{
    motionDetected = true;
    newMotion = true;
}

void setup() {
  attachInterrupt(switchPin, motionISR, HIGH);
  REG_SET_BIT(GPIO_ENABLE_REG, (1 << LEDpin));
  REG_CLR_BIT(GPIO_ENABLE_REG, (1 << switchPin));
  REG_CLR_BIT(GPIO_OUT_REG, (1 << LEDpin));
}

void loop() {
  process();
}

void counter(){
 if(newMotion){
    newMotion = false;
    startAlarmAndSignalTime = millis();
 }
}

void alarm(){
  if(motionDetected){
    uint32_t elapsedForAlarm = millis() - startAlarmAndSignalTime;
    if((elapsedForAlarm / 1000) % 2 == 0){
    tone(piezoPin, 1500, 500);
    }else{
      noTone(piezoPin);
    }
  }
}
void LEDSignal(){
  if(motionDetected){
    uint32_t elapsed = millis() - startAlarmAndSignalTime;
    if((elapsed / 1000) % 2 == 0){
    REG_CLR_BIT(GPIO_OUT_REG, (1 << LEDpin));
    }else{
       REG_SET_BIT(GPIO_OUT_REG, (1 << LEDpin));
    }
    }
  }

void alarmOff(){
  uint32_t reg_state = REG_READ(GPIO_IN_REG);
  if (!(reg_state & (1 << switchPin)) &&
    millis() - startAlarmAndSignalTime >= interval)
{
    motionDetected = false;
    noTone(piezoPin);
    digitalWrite(LEDpin, LOW);
}
}

void process(){
    counter();
    alarm();
    LEDSignal();
    alarmOff();
}