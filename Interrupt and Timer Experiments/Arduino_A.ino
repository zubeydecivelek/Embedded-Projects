const int buttonPin = 2;
void setup() {
 Serial.begin(9600);
 pinMode(buttonPin, INPUT);
}
void loop() {
 if (digitalRead(buttonPin) == LOW) {
   Serial.write('A');
   delay(1000);
 }
}