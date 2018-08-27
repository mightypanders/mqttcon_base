#include <PubSubClient.h>
#include <ESP8266WiFi.h>
#include "ap.h"

namespace
{
const char *SSID = "TheCommonwealth";
const char *WIFI_PASS = "97459596711813014854";
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

localAP failsafeAP;
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
    delay(500);
    Serial.println("Setting up.");
    delay(1);

    WiFi.macAddress(mac);
    clientMac += macToString(mac);
    Serial.println(clientMac);

    if (!wifiConnect())
    {
        failsafeAP.setupAP();
    }
}

void loop()
{
    if (client.connected())
    {
        String p = String(inc);
        client.publish("/test/temp",p.c_str());
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
