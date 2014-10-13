// This #include statement was automatically added by the Spark IDE.
#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

#define UPDATE_DHT (15 * 1000) // 15 seconds
#define DHT_TIMEOUT (5 * 1000) // 5 seconds
unsigned long lastUpdateDht = millis();
bool updatingDht = false;

char temperature[10];
char humidity[10];

uint32_t currentTime;

void setup()
{
	Serial.begin(9600);

    dht.begin();
}

void loop() {
    currentTime = Time.now();
    uint32_t n = millis();

    if (!updatingDht && (n - lastUpdateDht > UPDATE_DHT || currentTime < lastUpdateDht)) {
        lastUpdateDht = n;
        Serial.println("updatingDht ");

				char data[64];
				sprintf(data, "{humidity:%3.1f,celsius:%3.1f,fahrenheit:%3.2f}", dht.readHumidity(), dht.readTemperature(), dht.readTemperature(true));
				Spark.publish("temperature", String(data), 60, PRIVATE);

//				char fdata[64];
//				sprintf(fdata, "%3.2f", dht.readTemperature(true));
//				Spark.publish("temperature/fahrenheit", fdata, 60);
    }
}
