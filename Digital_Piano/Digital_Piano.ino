#include <Keypad.h>
#include <iostream>
#include <map>

constexpr uint8_t ROWS = 4;
constexpr uint8_t COLS = 4;
constexpr uint8_t piezoPin = 13;

char keyMap[ROWS][COLS] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

uint8_t rowPins[ROWS] = {14, 27, 26, 25}; // GIOP14, GIOP27, GIOP26, GIOP25
uint8_t colPins[COLS] = {33, 32, 18, 19}; // GIOP33, GIOP32, GIOP18, GIOP19
Keypad keypad = Keypad(makeKeymap(keyMap), rowPins, colPins, ROWS, COLS );
const std::map<char, uint16_t> notes = {
{'1' , 262},
{'2' , 294},
{'3' , 330},
{'4' , 349},
{'5' , 392},
{'6' , 440},
{'7' , 494},
{'8' , 523},
{'9' , 587},
{'0' , 659},
{'A' , 698},
{'B' , 784},
{'C' , 880},
{'D' , 988},
{'*' , 1047},
{'#' , 1175}
};

void setup() {
  Serial.begin(115200);
}

uint16_t getFreq(char key){
   auto it = notes.find(key);
    if (it != notes.end())
        return it->second;

    return 0;
}

void play(uint16_t freq){
  Serial.println("play");
  Serial.println(freq);
  if (freq == 0)
        return;
    tone(piezoPin, freq, 200);
}


void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY)
  {
    Serial.print("Pressed: ");
    Serial.println(key);
    uint16_t freq = getFreq(key);
    Serial.println(freq);
    play(freq);
  }
}
