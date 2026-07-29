#include "DHT.h"
#include "TM1637.h"

#define DHTPIN   13
#define DHTTYPE  DHT11

#define CLK_PIN  27
#define DIO_PIN  26

QueueHandle_t sensorQueue = NULL;
QueueHandle_t printQueue = NULL;

DHT dht(DHTPIN, DHTTYPE);
TM1637 disp(CLK_PIN, DIO_PIN);

typedef struct {
  float temperature;
  float humidity;
} SensorData;


void SensorTask(void *pvParameters){
  while(1){
    SensorData data;
    data.temperature = dht.readTemperature();
    data.humidity = dht.readHumidity();
    if (isnan(data.temperature) || isnan(data.humidity))
    {
    Serial.println("Error reading from DHT");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    continue;
    }
    xQueueSend(sensorQueue, &data, portMAX_DELAY);
    xQueueSend(printQueue, &data, portMAX_DELAY);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void DisplayTask(void *pvParameters){
   while(1){
    SensorData data;
    if(xQueueReceive(sensorQueue, &data, portMAX_DELAY)){
      int temp = (int)data.temperature;
      disp.display(0, temp / 10);
      disp.display(1, temp % 10);
      disp.display(2, 12);
      disp.display(3, 0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);

      int hum = (int)data.humidity;
      disp.display(0, hum / 10);
      disp.display(1, hum % 10);
      disp.display(2, 15);
      disp.display(3, 0);
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
  }
}

void printInfoTask(void *pvParameters){
  while(1){
    SensorData data;
  if(xQueueReceive(printQueue, &data, portMAX_DELAY)){
      Serial.print("Humidity: ");
      Serial.print(data.humidity);
      Serial.print("%   ");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
      Serial.print("Temperature: ");
      Serial.print(data.temperature);
      Serial.println(" C");
      vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
}
void setup()
{
    Serial.begin(115200);
    sensorQueue = xQueueCreate(5, sizeof(SensorData));
    printQueue = xQueueCreate(5, sizeof(SensorData));
    if (sensorQueue == NULL || printQueue == NULL) {
    Serial.println("Failed to create queue!");
    while (1);
  }

    dht.begin();

    disp.init();
    disp.set(2);

    xTaskCreatePinnedToCore(
    SensorTask,
    "SensorTask",
    4000,  
    NULL,
    2,
    NULL,
    1  
  );
  xTaskCreatePinnedToCore(
    DisplayTask,
    "DisplayTask",
    4000,  
    NULL,
    1,
    NULL,
    1  
  );
  xTaskCreatePinnedToCore(
    printInfoTask,
    "printInfoTask",
    4000,  
    NULL,
    1,
    NULL,
    1  
  );

}

void loop()
{
}