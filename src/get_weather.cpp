#include <WiFiS3.h>
#include <Arduino_JSON.h>
#include <secrets.h>


// Replace with your OpenWeatherMap API key and desired location
const char* location = "Pfinztal, DE"; // City name and country code
const char* server = "api.openweathermap.org";

void getTemperature() {
  WiFiClient client;
  const int httpPort = 80;

  // Connect to the server
  if (!client.connect(server, httpPort)) {
    Serial.println("Connection to host failed");
    return;
  }

  // Create the URL for the GET request
  String url = "/data/2.5/weather?q=" + String(location) + "&appid=" + String(SECRET_APIKEY) + "&units=metric";

  // Send the HTTP request
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + server + "\r\n" +
               "Connection: close\r\n\r\n");

  // Wait for the response
  while (client.connected() && !client.available()) {
    delay(100);
  }

  // Read the response
  String response = "";
  while (client.available()) {
    response += client.readString();
  }

  // Close the connection
  client.stop();

  // Print the response for debugging
  Serial.println("Response:");
  Serial.println(response);

  // Extract JSON part from the HTTP response
  int jsonStart = response.indexOf('{');
  int jsonEnd = response.lastIndexOf('}');
  if (jsonStart == -1 || jsonEnd == -1) {
    Serial.println("Failed to parse the response");
    return;
  }
  String jsonResponse = response.substring(jsonStart, jsonEnd + 1);

  // Parse the JSON
  JSONVar json = JSON.parse(jsonResponse);

  // Check if parsing was successful
  if (JSON.typeof(json) == "undefined") {
    Serial.println("Parsing input failed!");
    return;
  }

  // Extract temperature
  // Since JSONVar does not support .as<float>(), use casting
  double temperature = json["main"]["temp"];
  Serial.print("Current temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}

void setup() {
  // Start the Serial communication
  Serial.begin(9800);

  // Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(SECRET_SSID);
  WiFi.begin(SECRET_SSID, SECRET_PASS);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");

  // Print the local IP address
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Fetch and print the current temperature
  getTemperature();
}

void loop() {
  // Add other code if necessary
}

