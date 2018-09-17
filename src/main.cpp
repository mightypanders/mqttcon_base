#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>
#include <ConfigManager.h>

#define DHTPIN 2
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

namespace
{
const char *SSID = "";
const char *WIFI_PASS = "";
//const char *MQTT_SERVER = "192.168.178.40";
//int SENSOR = 1;
} // namespace

char topic[150];
char payload[50];
String clientMac = "";
unsigned char mac[6];
int inc = 0;

IPAddress ip(192, 168, 178, 128);
IPAddress mqttserver(192, 168, 178, 40);

WiFiClient wificlient;
PubSubClient client(mqttserver, 1883, wificlient);

void callback(char *topic, byte *payload, unsigned int length) {}

String macToString(const uint8_t *mac)
{
    String result;
    for (int i = 0; i < 6; i++)
    {
        result += String(mac[i], 16);
        if (i < 5)
            result += ":";
    }
    return result;
}

bool wifiConnect()
{
    uint8_t counter = 0;
    Serial.println("Starting up WiFi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, WIFI_PASS);
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        counter++;
        delay(500);
    }
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("Connected!");
        Serial.println("IP: " + WiFi.localIP());
        return true;
    }
    else
    {
        Serial.println("No Connection!");
        Serial.println("Falling back to Access Point Mode.");
        return false;
    }
}

bool setupMQTTConnection()
{
    Serial.print("Connection to MQTT Server: ");
    Serial.println(mqttserver);
    Serial.print("Using client name: ");
    Serial.println(clientMac);

    if (client.connect(clientMac.c_str()))
    {
        Serial.println("Connect successful");
        Serial.println("Publishing test message.");
        client.publish("/test/temp", "123");
        return true;
    }
    Serial.println("Connect failed.");
    return false;
}
void setup()
{
    Serial.begin(9600);
    dht.begin();
    sensor_t sensor;
    delay(500);
    Serial.println("Setting up.");
    delay(1);
    dht.temperature().getSensor(&sensor);
    dht.humidity().getSensor(&sensor);
    delayMS = sensor.min_delay / 1000;

    WiFi.macAddress(mac);
    clientMac += macToString(mac);
    Serial.println(clientMac);

    if (!wifiConnect())
    {
    }
}

void loop()
{
    if (client.connected())
    {
        sensors_event_t event;

        dht.temperature().getEvent(&event);
        if (!isnan(event.temperature))
            client.publish("/test/temp", String(event.temperature).c_str());

        dht.humidity().getEvent(&event);

        if (!isnan(event.relative_humidity))
            client.publish("/test/hum", String(event.relative_humidity).c_str());
            
        client.publish("val/debug", String(inc).c_str());
        inc++;

        client.loop();
        Serial.println("loop");
    }
    else
    {
        setupMQTTConnection();
    }
    delay(1000);
    // put your main code here, to run repeatedly:
}
