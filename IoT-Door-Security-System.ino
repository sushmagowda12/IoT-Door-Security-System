#include <ESP8266WiFi.h>      // Include ESP8266 Wi-Fi library
#include <ESP8266HTTPClient.h> // Include HTTP client library for sending HTTP requests

// Wi-Fi credentials (replace with your Wi-Fi network details)
const char* ssid = "SSID";           // Wi-Fi SSID (name)
const char* password = "PASSWORD";   // Wi-Fi password

// ThingSpeak API details
const char* server = "SERVER";       // ThingSpeak server URL (e.g., "api.thingspeak.com")
const String apiKey = "API KEY";     // ThingSpeak API key for your channel

// Pin configuration
const int irSensorPin = 2; // IR sensor connected to GPIO2 (D4 on ESP8266)
const int buzzerPin = 4;   // Buzzer connected to GPIO4 (D2 on ESP8266)

// Create a WiFiClient instance for HTTP requests
WiFiClient client;

void setup() {
  Serial.begin(115200);           // Initialize serial communication for debugging
  pinMode(irSensorPin, INPUT);    // Configure the IR sensor pin as input
  pinMode(buzzerPin, OUTPUT);     // Configure the buzzer pin as output

  // Connect to the Wi-Fi network
  WiFi.begin(ssid, password);

  Serial.println("Connecting to Wi-Fi...");
  while (WiFi.status() != WL_CONNECTED) { // Wait until the ESP8266 connects to Wi-Fi
    delay(500);
    Serial.print("."); // Print dots to indicate connection progress
  }
  Serial.println("\nConnected to Wi-Fi");
}

void loop() {
  // Read IR sensor value (HIGH if an object is detected, LOW otherwise)
  int irValue = digitalRead(irSensorPin);
  Serial.print("IR Sensor Value: "); // Log the sensor value
  Serial.println(irValue);

  // Turn the buzzer ON if the IR sensor detects something (HIGH)
  if (irValue == HIGH) {
    digitalWrite(buzzerPin, HIGH);  // Activate the buzzer
  } else {
    digitalWrite(buzzerPin, LOW);   // Deactivate the buzzer
  }

  // Send data to ThingSpeak if Wi-Fi is connected
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http; // Create an HTTPClient object for sending HTTP requests

    // Construct the HTTP GET URL with the API key and sensor value
    String url = String(server) + "/update?api_key=" + apiKey + "&field1=" + String(irValue);
    http.begin(client, url); // Initialize the HTTP request with the URL

    int httpCode = http.GET(); // Send the HTTP GET request and get the response code

    if (httpCode > 0) { // If the request was successful
      Serial.println("Data sent to ThingSpeak"); // Log successful data transmission
      Serial.println("Response Code: " + String(httpCode)); // Log HTTP response code
    } else { // If the request failed
      Serial.println("HTTP GET failed, error: " + http.errorToString(httpCode)); // Log the error
    }
    http.end(); // Close the HTTP connection
  } else {
    // If Wi-Fi is disconnected, attempt to reconnect
    Serial.println("Wi-Fi disconnected. Reconnecting...");
    WiFi.begin(ssid, password);
  }

  delay(15000); // Delay for 15 seconds to comply with ThingSpeak's rate limit
}
