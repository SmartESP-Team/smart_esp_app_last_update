#include "SmartESP32Utils.h"   // version adaptée ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "N1";
const char* password = "yannyann";

AsyncWebServer server(80);
String lastCommand = "";
AutoUpdatePayload payload;
unsigned long lastUpdateTime = 0;
const unsigned long updateInterval = 500;



void setup() {
  Serial.begin(115200);
  connectToWiFi(ssid, password);
  setupWebSocket(server, &lastCommand);

  pinMode(smokeSensorPin, INPUT);
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
ESP32 by Espressif Systems (Board package → inclut WiFi.h, HTTPClient.h, WiFiClientSecure.h)

AsyncTCP

ESP Async WebServer

ArduinoJson  */
