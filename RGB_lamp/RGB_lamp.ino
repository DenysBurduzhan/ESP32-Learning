
#define potentiometer 33
#define button 32
#define blue 25
#define green 26
#define red 27

int lastState = HIGH;
int currentState;
uint32_t startTime;
int count = 0;

void setup() {
  Serial.begin(9600);
  pinMode(blue, OUTPUT);
  pinMode(potentiometer, INPUT);
  pinMode(button, INPUT_PULLUP);
  ledcAttach(blue, 1000, 12);
  ledcAttach(green, 1000, 12);
  ledcAttach(red, 1000, 12);
  startTime = millis();
}

void loop() {
  uint32_t currentTime = millis();
  currentState = digitalRead(button);
  if(lastState == HIGH && currentState == LOW){
    Serial.println("The state changed from HIGH to LOW");
    if(currentTime - startTime > 50){
      count++;
      Serial.println(count);
      startTime = currentTime;
    }
  }
  lastState = currentState;
  process();
}

void process()
{
    switch (count)
    {
        case 1:
            blueON();
            break;

        case 2:
            ledOff(blue);
            greenON();
            break;

        case 3:
            ledOff(green);
            redON();
            break;

        case 4:
            ledOff(red);
            blueON();
            greenON();
            break;

        case 5:
            ledOff(green);
            blueON();
            redON();
            break;

        case 6:
            ledOff(blue);
            redON();
            greenON();
            break;

        case 7:
            blueON();
            redON();
            greenON();
            break;

        default:
            ledOff(blue);
            ledOff(green);
            ledOff(red);
            count = 0;
            break;
    }
}

void ledOff(uint8_t led){
  ledcWrite(led, 0);
}

void blueON(){
  ledcWrite(blue, analogRead(potentiometer));
}

void greenON(){
  ledcWrite(green, analogRead(potentiometer));
}


void redON(){
  ledcWrite(red, analogRead(potentiometer));
}


