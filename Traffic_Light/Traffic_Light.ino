
#define yellowLED 12
#define redLED 13
#define greenLED 14
#define button 26
uint32_t startTime;
volatile bool humanPresent = false;

void IRAM_ATTR ISR(){
  humanPresent = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(14, OUTPUT);
  startTime = millis();
  pinMode(button, INPUT);
  digitalWrite(button, PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), ISR, FALLING);
}

void buttonClicked(){
  uint32_t currentTime = millis();
    digitalWrite(12, LOW);
    digitalWrite(13, HIGH);
    digitalWrite(14, LOW);
  if(currentTime - startTime > 10000){
    humanPresent = false;
    startTime = currentTime;
  }
}

void loop() {

uint32_t currentTime = millis();
if(!humanPresent){
if(currentTime - startTime <= 1000 ){
  digitalWrite(13, LOW);
  digitalWrite(14, HIGH);
}else if(currentTime - startTime <= 2000){
  digitalWrite(14, LOW);
  digitalWrite(12, HIGH);
}else if(currentTime - startTime <= 3000){
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
}else {
  startTime = currentTime;
}
}else{
  buttonClicked();
}
}


