#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT11.h>

#define WIFI_SSID "Pee Kub_2.4G"
#define WIFI_PASSWORD "Pee1542547"

#define MQTT_HOST "--------------"
#define MQTT_PORT 1883
WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN 5
DHT11 dht11(DHTPIN);

float temperature;
u_int8_t humhumidity;
void setup()
{
    Serial.begin(112500);
    //WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(100);
        Serial.print(".");
    }
    Serial.println("Connected Done!!!");
    delay(2000);
}

void loop()
{
    int temperature = 0;
    int humidity = 0;
    int result = dht11.readTemperatureHumidity(temperature, humidity);
    if (result == 0)
    {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C\tHumidity: ");
        Serial.print(humidity);
        Serial.println(" %");
    }
    else
    {
        Serial.println(DHT11::getErrorString(result));
    }
}
