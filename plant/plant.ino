#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include "ssid.h"

const int moistureDet = A0;
const int humidityDet = D1;
DHTesp dht;

void setup() {
  Serial.begin(9600);
  pinMode(moistureDet, INPUT);
  dht.setup(humidityDet, DHTesp::DHT11);
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected!");
  Serial.print("Your IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  int moisture = analogRead(moistureDet);
  float humidity = dht.getHumidity();
  float temperat = dht.getTemperature();
  /*
   * 560 maans that the plant needs water
   * 580ish is probually good.
   */
  if (not isnan(humidity)) { // So we don't get a wrong value during cooldown
    Serial.print("moisture: ");
    Serial.print(moisture);
    Serial.print(" - humidity: ");
    Serial.print(humidity);
    Serial.print(" - temperature: ");
    Serial.println(temperat * 1.8 + 32); // Convert to fahrenheit
  }
  delay(500);
}
