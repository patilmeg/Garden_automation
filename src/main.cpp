#include <WiFiS3.h>
#include <secrets.h>
/*
// Replace with your network credentials
const char* ssid = "SECRET_SSID";
const char* password = "SECRET_PASS";

void setup() {
  // Start the Serial communication to see the output on the Serial Monitor
  Serial.begin(9800);

  // Attempt to connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(SECRET_SSID);

  // Initialize WiFi connection
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  // Wait for the connection to be established
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Connected to the WiFi network
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Put your main code here, to run repeatedly
}
*/