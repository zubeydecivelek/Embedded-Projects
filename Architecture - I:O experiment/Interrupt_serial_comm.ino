const int buttonPin = 2; // The pin to which the touch button is connected
const int ledPin = 13; // The pin to which the LED is connected
volatile bool buttonPressed = false; // Flag for interrupt processing


void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT); // Set the touch button pin as input
  pinMode(ledPin, OUTPUT); // Set the LED pin as output
  // Attach a function to the falling edge interrupt
  attachInterrupt(digitalPinToInterrupt(buttonPin), buttonInterrupt, FALLING);
}

void loop() {
  if (buttonPressed) {
    noInterrupts(); // Disable interrupts to ensure atomic operation
    Serial.println("Touch button pressed! Interrupt processing occurred.");
    digitalWrite(ledPin, HIGH); // Turn on the LED
    interrupts(); // Re-enable interrupts
    buttonPressed = false; // Reset the flag
  }
}

void buttonInterrupt() {
  // Interrupt function
  noInterrupts(); // Disable interrupts to ensure atomic operation
  Serial.println("Interrupt function called.");
  buttonPressed = true;
  digitalWrite(ledPin, LOW); // Turn off the LED
  interrupts(); // Re-enable interrupts
}