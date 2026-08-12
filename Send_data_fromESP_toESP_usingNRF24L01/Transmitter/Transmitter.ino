#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "DHT.h"
#include "TM1637.h"


#define DHTPIN   5
#define DHTTYPE  DHT11
#define CE_PIN 22
#define CSN_PIN 21

DHT dht(DHTPIN, DHTTYPE);

const byte slaveAddress[5] = {'R','x','A','A','A'};


RF24 radio(CE_PIN, CSN_PIN);

int dataToSend[2];
float temp;
float hum;


unsigned long currentMillis;
unsigned long prevMillis;
unsigned long txIntervalMillis = 1000;


void setup() {

    Serial.begin(9600);
    dht.begin();
    Serial.println("SimpleTx Starting");

    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.setRetries(3,5);
    radio.openWritingPipe(slaveAddress);
}


void loop() {
    currentMillis = millis();
    if (currentMillis - prevMillis >= txIntervalMillis) {
        send();
        prevMillis = millis();
    }
}

void send() {

    
    radio.write( &dataToSend, sizeof(dataToSend) );
        
    Serial.println("Data Sent: ");
    Serial.println("Humidity: " + String(dataToSend[0]) + " Temperature: " + String(dataToSend[1]));
    Serial.println("  Acknowledge received");
    updateMessage();
}


void updateMessage() {
    hum = dht.readHumidity();
    temp = dht.readTemperature();

    if (isnan(hum) || isnan(temp))
    {
        Serial.println("Error reading from DHT");
        return;
    }
    
    dataToSend[0] = (int) hum;
    dataToSend[1] = (int) temp;
}