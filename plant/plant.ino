#include <DHTesp.h>
#include <ESP8266WiFi.h>
#include "ssid.h"

const int moistureDet = A0;
const int humidityDet = D1;
DHTesp dht;

unsigned long currentTime = millis();
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// Set the web server port to the HTTP port
WiFiServer server(80);

// Variable to store the HTTP request
String header;

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
}

void loop() {
  WiFiClient client = server.available(); // Listen for incoming clients
  
  if (client) {
    
  Serial.println("New Client!");
  String currentLine = "";
  currentTime = millis();
  previousTime = currentTime;
  while (client.connected() && currentTime - previousTime <= timeoutTime) { // Loop while client is connected
    currentTime = millis();
    if (client.available()) {
      char c = client.read(); // Read a byte and then
      Serial.write(c);
      header += c;
      if (c == '\n') { // if the byte is a newline character
        if (currentLine.length() == 0) {
          client.println("HTTP/1.1 200 OK");
          client.println("Content-type:text/html");
          client.println("Connection: close");
          client.println();

          int moisture = analogRead(moistureDet);
          float humidity = dht.getHumidity(); // TODO: Make it so it doesn't return NaN
          float temperat = dht.getTemperature();
          
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
          client.println(temperat);
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
