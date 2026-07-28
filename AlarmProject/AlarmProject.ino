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
  attachInterrupt(switchPin, motionISR, RISING);
  pinMode(LEDpin, OUTPUT);
  pinMode(switchPin, INPUT);
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
    tone(piezoPin, 1500, 500);
  }
}
void LEDSignal(){
  if(motionDetected){
    uint32_t elapsed = millis() - startAlarmAndSignalTime;
    if((elapsed / 1000) % 2 == 0){
    digitalWrite(LEDpin, HIGH);
    }else{
      digitalWrite(LEDpin, LOW);
    }
    }
  }

void alarmOff(){
  uint32_t currentAlarmAndSignalTime = millis();
  if(currentAlarmAndSignalTime - startAlarmAndSignalTime >= interval){
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