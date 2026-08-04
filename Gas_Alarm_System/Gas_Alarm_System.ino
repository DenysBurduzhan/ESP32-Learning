
#define ledPin 32
#define piezoPin 13
#define MQ_7_DO 26
#define MQ_7_AO 27
uint32_t startSysTime;
uint32_t interval = 10000;
volatile bool gasPresent = false;
uint16_t piezoDelay = 1000;

void IRAM_ATTR gasCheckerISR(){
  gasPresent = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  attachInterrupt(MQ_7_AO, gasCheckerISR, RISING);
  startSysTime = millis();
}

void loop() {
  process();
}

uint16_t gasDetecting(){
  uint16_t value = analogRead(MQ_7_AO);
  return value;
}

void soundSignal(uint16_t piezoFreq){
  tone(piezoPin,piezoFreq, piezoDelay);
}

void ledSignal(){
  digitalWrite(ledPin, HIGH);
}
void writeToSerialValueIfGasPresent(){
  int analogValue = digitalRead(MQ_7_AO);
  Serial.println(analogValue);
  int logicValue = digitalRead(MQ_7_DO);
  Serial.println(logicValue);
}

void turnOn(){
  if(gasPresent){
    uint16_t value = gasDetecting();
    soundSignal(value);
    ledSignal();
    writeToSerialValueIfGasPresent();
  }
}
void process(){
  uint32_t currentSysTime = millis();
  if(currentSysTime - startSysTime <= interval){
    startSysTime = currentSysTime;
    turnOn();
  }else{
    turnOff();
  }
}

void turnOff(){
  gasPresent = false;
  noTone(piezoPin);
  digitalWrite(ledPin, LOW);
}
