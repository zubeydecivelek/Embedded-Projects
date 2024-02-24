#include <WiFi.h>
#include <WebServer.h>
#include <Ultrasonic.h>

// WiFi credentials
const char* ssid = "ssid"; // WiFi network name
const char* password = "password"; // WiFi network password

// Server and sensor initialization
WebServer server(80);
Ultrasonic ultrasonic(5, 18); // Ultrasonic sensor pins (Trig, Echo)
const int buzzerPin = 17; // GPIO pin number for buzzer
const int ledPin = 16; // GPIO pin number for LED
bool systemActive = false; // Flag to check if the system is active
bool alarmTriggered = false; // Flag to check if the alarm has been triggered

void setup() {
  Serial.begin(115200);
  // Set pin modes
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  pinMode(ledPin, OUTPUT); // Set LED pin as output

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  // Print the IP address
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the IP address

  // Handle root URL ("/")
  server.on("/", HTTP_GET, []() {
    String html = "<html><head><title>ESP32 Security System</title></head><body>";
    html += "<h1>ESP32 Security System</h1>";

    // Display current status of the system on the web page
    if (systemActive) {
      html += "<p>Status: Active</p>";
      // Show if alarm has been triggered
      if (alarmTriggered) {
        html += "<p>Alarm: Triggered!</p>";
      } else {
        html += "<p>Alarm: Not triggered</p>";
      }
      html += "<button onclick=\"location.href='/deactivate'\">Deactivate</button>";
    } else {
      html += "<p>Status: Inactive</p>";
      html += "<button onclick=\"location.href='/activate'\">Activate</button>";
    }

    html += "</body></html>";
    server.send(200, "text/html", html);
  });

  // Handle "/activate" URL
  server.on("/activate", HTTP_GET, []() {
    systemActive = true; // Activate the system
    alarmTriggered = false; // Reset alarm trigger
    server.sendHeader("Location", "/"); // Redirect to root
    server.send(303);
  });

  // Handle "/deactivate" URL
  server.on("/deactivate", HTTP_GET, []() {
    systemActive = false; // Deactivate the system
    // Turn off buzzer and LED
    digitalWrite(buzzerPin, LOW); // Turn off buzzer
    digitalWrite(ledPin, LOW); // Turn off LED
    server.sendHeader("Location", "/"); // Redirect to root
    server.send(303);
  });

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Check if system is active
  if (systemActive) {
    long distance = ultrasonic.read(); // Read distance from ultrasonic sensor
    Serial.print("Distance: ");
    Serial.println(distance);
    // If distance is less than or equal to 20 cm, trigger the alarm
    if (distance > 0 && distance <= 20) {
      alarmTriggered = true; // Set alarm trigger
      // Activate buzzer and LED
      digitalWrite(buzzerPin, HIGH); // Activate buzzer
      digitalWrite(ledPin, HIGH); // Activate LED
    } else {
      // If distance is more than 20 cm, reset the alarm
      alarmTriggered = false; // Reset alarm trigger
      // Deactivate buzzer and LED
      digitalWrite(buzzerPin, LOW); // Deactivate buzzer
      digitalWrite(ledPin, LOW); // Deactivate LED
    }
  }
}
