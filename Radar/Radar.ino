#include <ESP32Servo.h>

#define trigPin  27
#define echoPin  26
#define servoPin 25

Servo myServo;
int pos = 0;   
float duration,distance;
void setup(){
Serial.begin(9600);
Serial.println("Radar Start");
pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);
myServo.attach(servoPin);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 1) { 
    myServo.write(pos);             
    delay(60); 
    dist_calc(pos);
  }
 
  for (pos = 180; pos >= 0; pos -= 1) { 
    myServo.write(pos);              
    delay(60);
    dist_calc(pos);
  }
}

void dist_calc(int pos){
  digitalWrite(trigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin,LOW);
  duration = pulseIn(echoPin, HIGH, 30000);
  distance = duration * 0.0343 / 2.0;
  Serial.print(pos); 
  Serial.print(","); 
  Serial.println(distance);
}

