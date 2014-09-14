// This #include statement was automatically added by the Spark IDE.
#include "idDHT22/idDHT22.h"

int idDHT22pin = D4;
void dht22_wrapper(); // must be declared before the lib initialization

// DHT instantiate
idDHT22 DHT22(idDHT22pin, dht22_wrapper);


void setup()
{
	Serial.begin(9600);
}

// This wrapper is in charge of calling
// must be defined like this for the lib work
void dht22_wrapper() {
	DHT22.isrCallback();
}

void loop()
{

	DHT22.acquire();
	while (DHT22.acquiring())
		;
	int result = DHT22.getStatus();
	switch (result)
	{
		case IDDHTLIB_OK:
// 			Serial.println("OK");
			break;
		case IDDHTLIB_ERROR_CHECKSUM:
			Serial.println("Error\n\r\tChecksum error");
			break;
		case IDDHTLIB_ERROR_ISR_TIMEOUT:
			Serial.println("Error\n\r\tISR Time out error");
			break;
		case IDDHTLIB_ERROR_RESPONSE_TIMEOUT:
			Serial.println("Error\n\r\tResponse time out error");
			break;
		case IDDHTLIB_ERROR_DATA_TIMEOUT:
			Serial.println("Error\n\r\tData time out error");
			break;
		case IDDHTLIB_ERROR_ACQUIRING:
			Serial.println("Error\n\r\tAcquiring");
			break;
		case IDDHTLIB_ERROR_DELTA:
			Serial.println("Error\n\r\tDelta time to small");
			break;
		case IDDHTLIB_ERROR_NOTSTARTED:
			Serial.println("Error\n\r\tNot started");
			break;
		default:
			Serial.println("Unknown error");
			break;
	}
	Serial.print("Humidity (%): ");
	Serial.println(DHT22.getHumidity(), 2);

	Serial.print("Temperature (oC): ");
	Serial.println(DHT22.getCelsius(), 2);

	delay(10000);
}
