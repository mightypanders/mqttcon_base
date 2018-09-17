// #include "ap.h"

// localAP::localAP()
// {
//     setupAP();
// }

// void localAP::setupAP()
// {
//     server = new WiFiServer(serverPort);
//     if (Serial)
//         writeAvailable = true;
//     WiFi.mode(WIFI_AP);
//     WiFi.softAP(APSSID, AP_PASS);
//     server->begin();
//     if (writeAvailable)
//     {
//         Serial.println("Server started on:");
//         Serial.print("SSID: ");
//         Serial.println(APSSID);
//         Serial.print("IP: ");
//         Serial.println(WiFi.localIP());
//     }
// }
