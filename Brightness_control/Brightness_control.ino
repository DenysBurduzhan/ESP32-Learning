#define potentiometerPIN 35
#define ledPIN 5
#define PWM1_Freq  1000
#define PWM1_Res   12

int AN_Pot1_Result = 0;
void setup() {
  Serial.begin(115200);
  pinMode(potentiometerPIN, INPUT);
  pinMode(ledPIN, OUTPUT);
  ledcAttach(ledPIN, PWM1_Freq, PWM1_Res);
}

void loop() {
 AN_Pot1_Result = analogRead(potentiometerPIN);
 Serial.println(AN_Pot1_Result);
 AN_Pot1_Result = map(AN_Pot1_Result, 0, 2480, 0, 4095); 
 AN_Pot1_Result = constrain(AN_Pot1_Result, 0, 4095);
 Serial.println(AN_Pot1_Result);
 ledcWrite(ledPIN, AN_Pot1_Result);
}
