/*
 * For my soil:
 * 230 range means the plant is dry
 * 290 range means the plant is damp
 * 340 range means the plant is wet
 * 
 * Honestly that's confusing as it changes too slow for me, thast just the hygrometer if I'm correct through.
 */

#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include "ssid.h"

const int moistureDet = A0;
const int humidityDet = D1;
DHTesp dht;

// Variable to store the HTTP request
String header;
// Plant status variables
int moisture;
float humidity;
float temperat;
// Time variables, they should be unsigned longs and WILL overflow after 50 days
unsigned long aimTime;
unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;
// Set the web server port to the HTTP port
WiFiServer server(80);

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
  server.begin();

  moisture = analogRead(moistureDet);
  humidity = dht.getHumidity();
  temperat = dht.getTemperature();
  aimTime = 0;
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients
  currentTime = millis();

  if (currentTime - aimTime > 60000) {
    moisture = analogRead(moistureDet);
    humidity = dht.getHumidity();
    temperat = dht.getTemperature();
    aimTime = currentTime;
    while (isnan(humidity)) { // If the humidity value is NaN
      moisture = analogRead(moistureDet);
      humidity = dht.getHumidity();
      temperat = dht.getTemperature();
      aimTime = currentTime;
      Serial.println("Humidity was NaN!");
      delay(500); // So we don't keep getting NaN
    }
    Serial.println("Updated values!");
  }
  
  if (client) {
    
  Serial.println("New Client!");
  String currentLine = "";
  unsigned long previousTime = currentTime;
  
  while (client.connected() && currentTime - previousTime <= timeoutTime) { // Loop while client is connected
    unsigned long currentTime = millis();
    if (client.available()) {
      char c = client.read(); // Read a byte
      header += c;
      if (c == '\n') { // if the byte is a newline character it probably means that the HTTP request is done.
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();
          
          client.println("<!DOCTYPE html>");
          client.println("<html>");
          client.println("<head>");
          client.println("<title>Plant monitor</title>");
          client.println("</head>");
          client.println("<body>");
          client.println("<h1>Plant monitor</h1>");
          client.print("<p>Moisture: ");
          client.println(moisture);
          client.print("</p><p>Humidity: ");
          client.println(humidity);
          client.print("</p><p>Temperature: ");
          client.println(temperat * 1.8 + 32); // Fahrenheit temperature
          client.print("</p><p>Time: ");
          client.println(floor((aimTime - (currentTime - aimTime))/1000)); // Fahrenheit temperature
          client.println("</p></body>");
          client.println("</html>");

          client.println();
          break;
        } else {
          currentLine = "";
        }
      } else if (c != '\r') {
        currentLine += c;
      }
    }
  }
  header = "";

  client.stop();
  Serial.println("Client disconnected.");
  Serial.println("");
  }
  /*
   * 560 maans that the plant needs water
   * 580ish is probually good.
   */
}
