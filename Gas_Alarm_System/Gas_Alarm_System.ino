#include <WiFi.h>
#define ledPin 32
#define piezoPin 13
#define MQ_7_DO 26
#define MQ_7_AO 27
uint32_t startSysTime;
uint32_t interval = 10000;
volatile bool gasPresent = false;
uint16_t piezoDelay = 1000;

const char* ssid = "HUAWEI-N1ATO4";
const char* password = "43e1429mh4";

void IRAM_ATTR gasCheckerISR(){
  gasPresent = true;
}

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("\nConnecting to WiFi Network ..");
  while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
  }
  // Serial.println("\nConnected to the WiFi network");
  // Serial.print("Local ESP32 IP: ");
  // Serial.println(WiFi.localIP());
  pinMode(ledPin, OUTPUT);
  attachInterrupt(MQ_7_DO, gasCheckerISR, RISING);
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
  int analogValue = analogRead(MQ_7_AO);
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
    turnOff();
  }else{
    turnOn();
  }
}

void turnOff(){
  gasPresent = false;
  noTone(piezoPin);
  digitalWrite(ledPin, LOW);
}
