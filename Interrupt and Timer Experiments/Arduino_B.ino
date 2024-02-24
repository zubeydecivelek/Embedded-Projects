unsigned long lastPressTime = 0;
void setup() {
 Serial.begin(9600);
}
void loop() {
 if (Serial.available() > 0) {
   char receivedChar = Serial.read();
   if (receivedChar == 'A') {
     unsigned long currentTime = millis();
     unsigned long timePassed = currentTime - lastPressTime;
     Serial.print("Received 'A'. Time passed since last press: ");
     Serial.print(timePassed);
     Serial.println(" ms");
     lastPressTime = currentTime;
   }
} }