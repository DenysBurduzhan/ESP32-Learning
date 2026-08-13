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


typedef struct{
    float temp;
    float hum;
}SensorData;


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
    SensorData data;
    data.hum = dht.readHumidity();
    data.temp = dht.readTemperature();

    if (isnan(data.hum) || isnan(data.temp))
    {
        Serial.println("Error reading from DHT");
        return;
    
    bool res = radio.write( &data, sizeof(data) );
    if(res){        
    Serial.println("Data Sent: ");
    Serial.println("Humidity: " + String(data.hum) + " Temperature: " + String(data.temp));
    }else{
        Serial.println("  Fail");
        return;
    }
}

