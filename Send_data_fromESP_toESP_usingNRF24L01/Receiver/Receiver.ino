#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN 5
#define CSN_PIN 4

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

typedef struct{
    float temp;
    float hum;
}ReceivedData;

ReceivedData data;
bool newData = false;

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
}

void loop() {
    getData();
    showData();
}

void getData() {
    if ( radio.available() ) {
        radio.read( &data, sizeof(data) );
        newData = true;
    }
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println("Humidity: " + String(data.hum) + " Temperature: " + String(data.temp));
        newData = false;
    }
}