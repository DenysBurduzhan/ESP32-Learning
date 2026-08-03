#define potentiometerPIN 35
#define ledPIN 5


void setup() {
  pinMode(potentiometerPIN, INPUT);
  pinMode(ledPIN, OUTPUT);
  ledcAttach(ledPIN, 5000, 12);
}

void loop() {
 uint32_t value = analogRead(potentiometerPIN);
 ledcWrite(ledPIN, value);
}
