#include <dht.h>

dht dhtlib;
const int moistureDet = A1;
const int humidityDet = A2;

void setup() {
  Serial.begin(9600);
}

void loop() {
  int moisture = analogRead(moistureDet);
  int humidity = dhtlib.read11(humidityDet);
  if (dhtlib.humidity != -999) { // So we don't get a wrong value during cooldown
    Serial.print("moisture: ");
    Serial.print(moisture);
    Serial.print(" - humidity: ");
    Serial.print(dhtlib.humidity);
    Serial.print(" - temperature: ");
    Serial.println(dhtlib.temperature * 1.8 + 32); // Convert to fahrenheit
  }
  delay(500);
}
