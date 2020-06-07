#include <DHTesp.h>

const int moistureDet = D2;
const int humidityDet = D1;
DHTesp dht;

void setup() {
  Serial.begin(9600);
  dht.setup(humidityDet, DHTesp::DHT11);
}

void loop() {
  int moisture = analogRead(moistureDet);
  float humidity = dht.getHumidity();
  float temperat = dht.getTemperature();
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
