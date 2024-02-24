const int switchPin = 2;
int switchState = LOW; // Current switch state
int lastSwitchState = LOW; // Previous switch state
int debounceState = 0; // Debounce state: 0 - Idle, 1 - Possibly pressed, 2 - Pressed, 3 - Possibly released

void setup() {
  pinMode(switchPin, INPUT);
  Serial.begin(9600); // Serial connection for debugging
}

void loop() {
  int currentSwitchState = digitalRead(switchPin);
  if (currentSwitchState != lastSwitchState) {
    debounceState = 1;
  } 
  else {
    if (debounceState == 1) {
      debounceState = 2;
    } 
    else if (debounceState == 2) {
      switchState = currentSwitchState;
      debounceState = 0;
      Serial.print("Switch State: ");
      Serial.println(switchState == HIGH ? "Pressed" : "Released");
    }
  }
  lastSwitchState = currentSwitchState;
}