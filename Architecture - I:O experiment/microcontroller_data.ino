const int lm35Pin = A0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(lm35Pin);
  float temperature = (sensorValue * 5.0 / 1024.0) * 100.0;
  Serial.println(temperature);
  delay(1000);
}