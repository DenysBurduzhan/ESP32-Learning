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

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print("%   ");

    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.println(" C");
    uint32_t elapsed = millis() - startTime;

    if((elapsed / 1000) % 2 != 0){
    int temp = (int)t;

    int digitOneT = temp / 10;
    int digitTwoT = temp % 10;

    disp.display(0, digitOneT);
    disp.display(1, digitTwoT);
    disp.display(2, 12);
    disp.display(3, 0);
    }else{
      int hum = (int)h;

    int digitOneH = hum / 10;
    int digitTwoH = hum % 10;

    disp.display(0, digitOneH);
    disp.display(1, digitTwoH);
    disp.display(2, 15);
    disp.display(3, 0);
    }
    }
}