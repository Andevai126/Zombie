#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial LOGSerial(-1, 1); // RX, TX

#include "df.hpp"
#include "deep.hpp"

void setup() {
  // Setup Serials
  LOGSerial.begin(2400);
  DFSerial.begin(9600);

  // Button with interrupt
  pinMode(2, INPUT);
  // Transistor controlpin / Power DFPlayer
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);
  // Led indicator
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  // Transistor controlpin / Connect Speaker
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);

  // Save power
  disable();

  LOGSerial.print(F("Setup complete"));
}

void loop() {
  static unsigned long nHeartbeats = 0;
  static unsigned long nWakeups = 0;

  // Sleep until interrupt
  LOGSerial.print(F("\nSleeping"));
  while (!buttonISRtriggered) {
    deepSleep();
    nHeartbeats++;
    LOGSerial.print(F("."));
  }
  buttonISRtriggered = false;
  nWakeups++;
  LOGSerial.println(F("Awoken"));

  // ---------------------------------

  // Wait for button release
  unsigned long timer = millis();
  while (millis() - timer < 6000) {
    if (buttonISRtriggered) {
      // Wait for button release
      while (buttonISRtriggered) {
        buttonISRtriggered = false;
        delay(100);
      }
    }
  }
  
  // ---------------------------------

  randomSeed(nHeartbeats+67487);
  playRandom();
}