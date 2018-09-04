
#include <ESP8266WiFi.h>

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