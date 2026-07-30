#include <ESP32Servo.h>

#define trigPin  27
#define echoPin  26
#define servoPin 25

Servo myServo;
int pos = 0;   
int duration,distance;
void setup(){
Serial.begin(9600);
Serial.println("Radar Start");
pinMode(echoPin, INPUT);
pinMode(trigPin, OUTPUT);
myServo.attach(servoPin);
}

void loop() {
  for (pos = 0; pos <= 180; pos += 3) { 
    myServo.write(pos);             
    delay(60); 
  }
 
  for (pos = 180; pos >= 0; pos -= 3) { 
    myServo.write(pos);              
    delay(60);
  }

  int dis = dist_calc();
  detect(dis);
}

void detect(int dis){
  if(dis > 15){
    Serial.println("No objects on the way");
  }else{
    Serial.println(dis);
    Serial.println("Distance to object is " + String(dis));
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

