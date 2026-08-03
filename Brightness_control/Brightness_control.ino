#define potentiometerPIN 35
#define ledPIN 5
#define PWM1_Freq  1000
#define PWM1_Res   12

int AN_Pot1_Result = 0;
void setup() {
  pinMode(potentiometerPIN, INPUT);
  pinMode(ledPIN, OUTPUT);
  ledcAttach(ledPIN, PWM1_Freq, PWM1_Res);
}

void loop() {
 AN_Pot1_Result = analogRead(potentiometerPIN);
 ledcWrite(ledPIN, AN_Pot1_Result);
}
