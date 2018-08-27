#ifndef localAP_H
#define localAP_H
#include <ESP8266WiFi.h>

class localAP
{
  private:
    uint16_t serverPort = 80;
    const char *APSSID = "ESP_AP";
    const char *AP_PASS = "ESP123";
    WiFiServer *server;
    bool writeAvailable = false;

  public:
    localAP();
    void setupAP();
};
#endif