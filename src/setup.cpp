#include <ESP8266WiFi.h>
#include "ap.h"
#include "stringfunctions.cpp"

String clientMac ="";
unsigned char mac[6];
int inc = 0;

localAP failsafeAP;

void setup()
{
    Serial.begin(115200);
    delay(500);
    Serial.println("Setting up WiFi");
    delay(1);

    WiFi.macAddress(mac);
    clientMac += macToString(mac);
    Serial.print("My MAC address: ");
    Serial.println(clientMac);

    if (!wifiConnect())
    {
        failsafeAP.setupAP();
    }
}