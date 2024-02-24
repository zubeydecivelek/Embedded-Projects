#include <avr/io.h>
#include <avr/interrupt.h>
const int ledPin = 13; // Pin connected to the LED on Arduino Uno
volatile int hours = 0;
volatile int minutes = 0;
volatile int seconds = 0;

void setup() {
  pinMode(ledPin, OUTPUT); // initialize the digital pin as an output
  Serial.begin(9600); // initialize serial communication
  // Set up Timer1 for interrupt every second
  cli(); // Disable interrupts
  TCCR1A = 0; // Set entire TCCR1A register to 0
  TCCR1B = 0; // Set entire TCCR1B register to 0
  // Set compare match register to desired timer count:
  OCR1A = 15624;
  (Clear Timer on Compare Match)
  TCCR1B |= (1 << WGM12);// Enable CTC mode
  TCCR1B |= (1 << CS12) | (1 << CS10);// Set CS12, CS10 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A);// Enable timer compare interrupt
  sei(); // Enable interrupts
}

void loop() {
  Serial.print("Time: ");
  Serial.print(hours);
  Serial.print(":");
  Serial.print(minutes);
  Serial.print(":");
  Serial.println(seconds);
  delay(1000);
}

ISR(TIMER1_COMPA_vect) {
  // Update the clock values
  seconds++;
  if (seconds == 60) {
    seconds = 0;
    minutes++;
    if (minutes == 60) {
    minutes = 0;
    hours++;
      if (hours == 24) {
      hours = 0;
      }
    }
  }
digitalWrite(ledPin, !digitalRead(ledPin));
}
