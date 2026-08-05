#include <ESP32Servo.h>
#include "DHT.h"
#include <string>

#define ledPIN  25
#define DHT11_PIN  26
#define DHTTYPE  DHT11
#define servoPIN  27

DHT dht(DHT11_PIN, DHTTYPE);
Servo myServo;
String cmd;

uint32_t startTime;
uint32_t interval = 1000;

void setup() {
  Serial.begin(115200);
  pinMode(ledPIN, OUTPUT);
  dht.begin();
  myServo.attach(servoPIN);
  startTime = millis();
}

void loop() {
  if (Serial.available())
    {
        cmd = Serial.readStringUntil('\n');
        cmd.trim();
        process();
    }
}

void process(){
  if(cmd == "ledOn"){
    Serial.println("ledOn");
    ledOn();
  }else if(cmd == "ledOff"){
    Serial.println("ledOff");
    ledOff();
  }else if(cmd == "checkTemperature"){
    checkTemperature();
  }else if(cmd.startsWith("servo ")){
    int angle = cmd.substring(6).toInt();
    turnServo(angle);
  }
}

void ledOn(){
  digitalWrite(ledPIN, HIGH);
}

void ledOff(){
  digitalWrite(ledPIN, LOW);
}

void checkTemperature(){
  uint32_t currentTime = millis();
  if(currentTime - startTime > interval){
  startTime = currentTime;
  float t = dht.readTemperature();
  if (isnan(t))
    {
        Serial.println("Error reading from DHT");
    }
    Serial.println(t);
  }else{
    Serial.println("Wait...");
  }
}

  void turnServo(int angle){
    angle = constrain(angle, 0, 180);
    Serial.println(angle);
    myServo.write(angle);
  }