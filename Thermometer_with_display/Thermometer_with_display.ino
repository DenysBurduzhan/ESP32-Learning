#include "DHT.h"
#include "TM1637.h"

#define DHTPIN   13
#define DHTTYPE  DHT11

#define CLK_PIN  27
#define DIO_PIN  26

uint32_t startTime;

DHT dht(DHTPIN, DHTTYPE);
TM1637 disp(CLK_PIN, DIO_PIN);

hw_timer_t *Timer0_Cfg = NULL;

volatile bool flag = false;

void IRAM_ATTR Timer0_ISR()
{
    flag = true;
}

void setup()
{
    Serial.begin(9600);

    dht.begin();

    disp.init();
    disp.set(2);

    Timer0_Cfg = timerBegin(2000000);

    if (Timer0_Cfg == NULL)
    {
        Serial.println("Timer init error");
        while (1);
    }

    timerAttachInterrupt(Timer0_Cfg, &Timer0_ISR);
    timerAlarm(Timer0_Cfg, 2000000, true, 0);
    startTime = millis();
}

void loop()
{
    if (flag){
    flag = false;

    float h = dht.readHumidity();
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t))
    {
        Serial.println("Error reading from DHT");
        return;
    }

    printInfo(t, h);
    uint32_t elapsed = millis() - startTime;

    if((elapsed / 1000) % 2 != 0){
    int temp = (int)t;
    showValue(temp, 12);
    }else{
      int hum = (int)h;
      showValue(hum, 15);
    }
    }
}
void showValue(int value, int symbol){
    disp.display(0, value / 10);
    disp.display(1, value % 10);
    disp.display(2, symbol);
    disp.display(3, 0);
}

void printInfo(int t, int h){
    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%   ");

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" C");
}