#include <Arduino.h>

#include "deep.hpp"
#include "df.hpp"
#include "test.hpp"
#include "menu.hpp"

void setup() {
  // Setup Serials
  LOGSerial.begin(2400);
  DFSerial.begin(9600);
  // Set focus for listening, writing always works on any SoftwareSerial
  LOGSerial.listen();

  // Button with interrupt
  pinMode(2, INPUT);
  enable();
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

  // Randomizer
  randomSetup();

  LOGSerial.print(F("Setup complete"));
}

void loop() {
  // Sleep until interrupt
  LOGSerial.print(F("\nSleeping"));
  while (!buttonISRtriggered) {
    deepSleep();
    // Heartbeat
    LOGSerial.print(F("."));
  }
  LOGSerial.println(F("Awoken"));
  buttonISRtriggered = false;

  // ---------------------------------

  // Track number of wakeups
  static unsigned long Nwakeups = 0;
  Nwakeups++;

  // Select action
  uint8_t action = getSelection();

  // Perform action
  switch (action) {
    case PLAY_TRACK_1:
    play(1, 9);
    break;

  case RUN_TESTS: {
    unsigned long timer = millis();
    while (millis() - timer < 8000) {
      test();
    }
    break;
  }
  
  case BLINK_LED:
    blink();
    break;
  
  case PLAY_RANDOM_TRACK:
    playRandom();
    break;
  
  case PRINT_N_WAKEUPS:
    LOGSerial.print(F("Wakeups: "));
    LOGSerial.println(Nwakeups);
    break;
  
  default:
    break;
  }
}