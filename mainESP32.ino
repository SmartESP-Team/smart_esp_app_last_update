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

// ------- GPIO ESP32 (adapter si besoin) --------
const int smokeSensorPin = 34;   // Exemple : entrée analogique (ESP32 a plusieurs ADC)

bool smokeAlert = false;

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
    detect();

    sendAutoUpdate(payload);
    payload.notif = "false";
    payload.ia = "false";
    payload.ac = "";
    lastUpdateTime = millis();
  }
}

void detect() {
  int rawValue = analogRead(smokeSensorPin);  
  float normalized = rawValue / 4095.0;   // ESP32 ADC = 12 bits (0-4095)
  
  payload.indicateur1 = normalized;
  payload.ecran1 = String(rawValue);
}
