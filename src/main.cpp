#include <Arduino.h>
#include <SoftwareSerial.h>

#include "deep.hpp"
#include "df.hpp"

SoftwareSerial LOGSerial(0, 1); // RX, TX

void setup() {
  // Setup Serials
  LOGSerial.begin(2400);
  DFSerial.begin(9600);
  // Set focus, writing always works
  LOGSerial.listen();

  // Button
  pinMode(2, INPUT);
  // Transistor controlpin / Power DFPlayer
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  // Led indicator
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);

  // Save power
  disable();

  LOGSerial.print(F("Setup complete"));
}

void loop() {
  static unsigned long Nwakeups = 0;
  Nwakeups++;

  // Blink LED to show wakeup
  digitalWrite(3, HIGH);
  delay(100);
  digitalWrite(3, LOW);

  // Print wakeup count
  LOGSerial.println(Nwakeups);

  // Play a track
  play(1);

  // Sleep
  for (int i = 0; i < 1; i++) {
    deepSleep();
  }
}