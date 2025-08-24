#include <SmartESP8266Utils.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "N1";
const char* password = "yannyann";

AsyncWebServer server(80);
String lastCommand = "";
AutoUpdatePayload payload;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500;

// ------- GPIO ESP8266 (adapter si besoin) --------

bool smokeAlert = false ;

void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);
  setupWebSocket(server, &lastCommand);

 
}

void loop() {
 


  Autoupdate();
}

void Autoupdate() {
  processCommandIfNeeded(lastCommand, payload);

  if (millis() - lastUpdateTime > updateInterval) {
 

    sendAutoUpdate(payload);
    payload.notif = "false";
    payload.ia = "false";
    payload.ac = "";
    lastUpdateTime = millis();
  }
}


/* 

Au  cas où , Voici la liste des noms à chercher dans le Library Manager :

ESP8266 by ESP8266 Community (Board package → inclut ESP8266WiFi, ESP8266HTTPClient, BearSSL)

ESPAsyncTCP

ESP Async WebServer

ArduinoJson


*/
