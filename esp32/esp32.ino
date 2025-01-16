#include <WiFi.h>

const char* ssid = "Grinkeviciai Network"; // Replace with your SSID
const char* password = "grinkeviciai08"; // Replace with your password

WiFiServer server(80); // Create a TCP server on port 80

const int signalPin = 5; // GPIO pin to signal Arduino

// Non-blocking signal duration management
unsigned long signalDuration = 10; // Duration the signal pin stays HIGH (in milliseconds)
unsigned long previousMillis = 0; // Store last time the signal was set HIGH
bool signalActive = false; // Flag to track if signal is active

void setup() {
    Serial.begin(115200); // Start Serial communication
    WiFi.begin(ssid, password);

    pinMode(signalPin, OUTPUT); // Set signal pin as OUTPUT
    digitalWrite(signalPin, LOW); // Ensure the pin is LOW initially

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000); // Wait for connection
    }

    Serial.println("Connected to WiFi");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP()); // Print the ESP32's IP address
    server.begin(); // Start the server
}

void loop() {
    WiFiClient client = server.available(); // Check for incoming client connections
    if (client) {
        String request = client.readStringUntil('\n'); // Read the request
        Serial.println("Received request: " + request); // Log the request

        String responseBody; // Initialize response body

        // Check if the request is a POST
        if (request.indexOf("POST /") >= 0) {
            // Read the headers and check for the content length
            while (client.connected() && !client.available()) {
                delay(1); // Wait for data
            }

            // Read the body of the POST request and ignore it
            while (client.available()) {
                char c = client.read(); // Read one character at a time
                // Process character if needed, but here we ignore it to remove it immediately
            }

            // Set the GPIO pin HIGH to signal the Arduino immediately
            digitalWrite(signalPin, HIGH);
            previousMillis = millis(); // Record the time the signal was set HIGH
            signalActive = true; // Mark signal as active

            // Create a response with a confirmation message
            responseBody = "Signal sent to Arduino."; // Confirm the signal was sent

        } else {
            // For GET requests, show a message
            responseBody = "Hello from ESP32! Send data via POST request.";
        }

        // Send HTTP response
        client.println("HTTP/1.1 200 OK");
        client.println("Content-Type: text/html");
        client.println("Connection: close");
        client.println();
        client.println("<html><body><h1>ESP32 Server</h1><p>" + responseBody + "</p><p>Sent input through: GPIO Pin " + String(signalPin) + "</p></body></html>"); // HTML response
        client.stop(); // Close the connection
    }

    // Check if the signal is active and manage timing
    if (signalActive) {
        if (millis() - previousMillis >= signalDuration) {
            digitalWrite(signalPin, LOW); // Set the pin LOW after the specified duration
            signalActive = false; // Reset signal active flag
        }
    }
}
