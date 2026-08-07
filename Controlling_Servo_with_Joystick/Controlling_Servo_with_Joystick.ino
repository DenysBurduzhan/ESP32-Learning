#include <ESP32Servo.h>
// using mg90s 180°
#define VRY_PIN 33
#define VRX_PIN 25
#define SERVO_X_PIN 13 


Servo myServo;


uint32_t start;
void setup() {
 Serial.begin(9600);
  myServo.attach(SERVO_X_PIN);
  start = millis();
}

void loop() {

  int valueX = analogRead(VRX_PIN);
  int valueY = analogRead(VRY_PIN);

  if(abs(valueX - 2048) < 50){
    valueX = 2048;
  }
  int xAngle = map(valueX, 0, 4095, 0, 180); 
  myServo.write(xAngle); 

  uint32_t current = millis();
  if(current - start > 3000){
    start = current;
  Serial.print("X: ");
  Serial.print(valueX);

  Serial.print("  Y: ");
  Serial.print(valueY);

  Serial.print("  Angle: ");
  Serial.println(xAngle);
  }
}
