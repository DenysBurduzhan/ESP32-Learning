
#define piezoPin 27
void setup() {
  pinMode(piezoPin, OUTPUT);
}

void loop() {
  tone(piezoPin, 349, 3000);
  
}
