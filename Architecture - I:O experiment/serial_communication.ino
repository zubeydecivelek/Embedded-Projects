void setup() {
  // Initialize serial communication
  Serial.begin(9600);
}

void loop() {
  // Send a message over serial communication
  Serial.println("Hello, this is a serial communication message!");
  // Delay for 5 seconds
  delay(5000);
}