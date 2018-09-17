#include <ESP8266WiFi.h>
#include <ConfigManager.h>
#include "ap.h"
#include "stringfunctions.cpp"

String clientMac ="";
unsigned char mac[6];
int inc = 0;

struct Config {
    char name[20];
    bool enabled;
    int8_t hour;
    char password[20];
} config;

ConfigManager confMan;
localAP failsafeAP;

void setup()
{
    Serial.begin(115200);
    confMan.setAPName("esp_ap");
    confMan.setAPFilename("index.html");
    confMan.addParameter("name",config.name,20);
    confMan.begin(config);
    delay(500);
    Serial.println("Setting up WiFi");

    WiFi.macAddress(mac);
    clientMac += macToString(mac);
    Serial.print("My MAC address: ");
    Serial.println(clientMac);

}