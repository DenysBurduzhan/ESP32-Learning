#include <ESP32Servo.h>

#define trigPin  27
#define echoPin  26
#define servoPin 25
Servo myServo;  
int duration,distance;

void setup(){
Serial.begin(9600);
Serial.println("Radar Start");
pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);
myServo.attach(servoPin);
}

void loop() {
  findPos();
  
}

void printStepAndDistance(int value , int step){
  if (value <= 15 && value > 0){
      Serial.println(step);
      delay(100);
      Serial.println("Distance: " + String(value));
  }
}

void findPos(){
  for (int step = 0; step <= 180; step += 3){
  myServo.write(step);
  delay(60);
  printStepAndDistance(dist_calc(), step);
  }

  for (int step = 180; step >= 0; step -= 3){
   myServo.write(step);
   delay(60);
   printStepAndDistance(dist_calc(), step);
  }
}


int dist_calc(){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.0343 / 2.0;
  return distance;
}

