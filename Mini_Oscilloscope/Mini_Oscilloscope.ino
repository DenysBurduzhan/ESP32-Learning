
#define contactPin 32
void setup() {
  Serial.begin(9600);
}

void loop() {
  checkVoltage();
}

void checkVoltage(){
  float fromADC = analogRead(contactPin);
  float value = fromADC * 3.3 / 4095;
  Serial.println(fromADC);
  Serial.println(value);
}
