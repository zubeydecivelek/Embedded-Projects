const int switchPin = 2;
int switchState = 0; // 0 for released, 1 for pressed
int lastSwitchState = 0; // Last recorded switch state
unsigned long lastDebounceTime = 0; // Timestamp of the last state change
unsigned long debounceDelay = 50; // Debounce time in milliseconds

void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600); // Serial connection for debugging
}

void loop() {
  int currentSwitchState = digitalRead(switchPin);
  if (currentSwitchState != lastSwitchState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (currentSwitchState != switchState) {
    switchState = currentSwitchState;
    Serial.print("Switch State: ");
    Serial.println(switchState == HIGH ? "Pressed" : "Released");
    }
  }
  lastSwitchState = currentSwitchState;
}