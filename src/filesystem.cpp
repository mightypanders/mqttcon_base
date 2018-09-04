#include <ESP8266WiFi.h>
#include <FS.h>

void openFS()
{
    SPIFFS.begin();
}