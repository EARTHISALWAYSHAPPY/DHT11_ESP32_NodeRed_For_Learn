#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define WIFI_SSID "--------------"
#define WIFI_PASSWORD "--------------"

#define MQTT_SERVER "broker.hivemq.com"

WiFiClient espClient;
PubSubClient client(espClient);

#define DHTPIN 5
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void reconnect()
{
  while (!client.connected())
  {
    Serial.print(F("!!!!!......"));
    if (client.connect("ESP32Client"))
    {
      Serial.println(F("Connected to MQTT"));
      // Set youe Topic For subscribe
      client.subscribe("--------------"); //<---
      client.subscribe("--------------"); //<---
      client.subscribe("--------------"); //<---
    }
    else
    {
      Serial.print(F("Failed, rc="));
      Serial.print(client.state());
      Serial.println(F(" try again in 5 seconds"));
      delay(1000);
    }
  }
}
void setup()
{
  Serial.begin(115200);
  dht.begin();
  client.setServer(MQTT_SERVER, 1883);
  // WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(F("."));
  }
  Serial.println(F("Connected Done!!!"));
  delay(5000);
}

void loop()
{
  //reconnect
  if (!client.connected())
  {
    reconnect();
  }
  client.loop();

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  float f_temperature = dht.readTemperature(true);

  // Set youe Topic For publish
  client.publish("--------------", String(humidity).c_str(), false);      //<---
  client.publish("--------------", String(temperature).c_str(), false);   //<---
  client.publish("--------------", String(f_temperature).c_str(), false); //<---

  //For Serialmonitor
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("%  Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C "));
  Serial.print(f_temperature);
  Serial.println(F("°F"));

  //if DHT11 failed//
  if (isnan(humidity) || isnan(temperature) || isnan(f_temperature))
  {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  delay(10000);
}
