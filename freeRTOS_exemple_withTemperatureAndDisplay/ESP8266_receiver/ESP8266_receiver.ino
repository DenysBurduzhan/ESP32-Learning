#include <SoftwareSerial.h>

SoftwareSerial mySerial(D7, D8);

void setup()
{
    Serial.begin(115200);
    mySerial.begin(9600);
}

void loop(){
    if(mySerial.available()){
    String mes = mySerial.readStringUntil('\n');
    Serial.println(mes);
    }
}