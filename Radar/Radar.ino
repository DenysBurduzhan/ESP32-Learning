#include <ESP32Servo.h>

#define trigPin  27
#define echoPin  26
#define servoPin 25

Servo myServo;

void setup() {
  Serial.begin(115200);
  Serial.println("Radar Start");

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  myServo.attach(servoPin);
}

void loop() {
  scanForward();
  scanBackward();
}
void printResult(int step, int dist){
    Serial.print("Angle: ");
    Serial.print(step);
    Serial.print(" Distance: ");
    Serial.println(dist);
}

void scanForward() {
  for (int step = 0; step <= 180; step += 3) {
    myServo.write(step);
    delay(60);

    int dist = dist_calc();

    if (dist > 0 && dist <= 15) {
      printResult(step, dist);
    }
  }
}

void scanBackward() {
  for (int step = 180; step >= 0; step -= 3) {
    myServo.write(step);
    delay(60);

    int dist = dist_calc();

    if (dist > 0 && dist <= 15) {
      printResult(step, dist);
    }
  }
}

int dist_calc() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);

  if (duration == 0) {
    return -1; 
  }

  return duration * 0.0343 / 2.0;
}
