
#define yellowLED 12
#define redLED 13
#define greenLED 14



void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  startTime = millis();
}

void loop() {
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
  delayMicroseconds(1000000);
  digitalWrite(14, LOW);
  digitalWrite(12, HIGH);
  delayMicroseconds(1000000);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delayMicroseconds(1000000);
}

