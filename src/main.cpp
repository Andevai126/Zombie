#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial LOGSerial(-1, 1); // RX, TX

#include "df.hpp"
#include "deep.hpp"
#include "menu.hpp"

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

  // Randomizer
  randomSetup();

  LOGSerial.print(F("Setup complete"));
}

void loop() {
  static unsigned long nHeartbeats = 0;
  static unsigned long nWakeups = 0;

  // Sleep until interrupt
  LOGSerial.print(F("\nSleeping"));
  while (!buttonISRtriggered) {
    deepSleep();
    // Heartbeat
    nHeartbeats++;
    LOGSerial.print(F("."));
  }
  buttonISRtriggered = false;
  nWakeups++;
  LOGSerial.println(F("Awoken"));

  // ---------------------------------

  // Select action
  uint8_t action = getSelection();

  // Perform action
  switch (action) {
    case PLAY_TRACK_1:
    play(1, 9);
    break;
  
  case BLINK_LED:
    blink();
    break;
  
  case PLAY_RANDOM_TRACK:
    playRandom();
    break;
  
  case PRINT_N_HEARTBEATS:
    LOGSerial.print(F("Heartbeats: "));
    LOGSerial.println(nHeartbeats);
    break;
  
  case PRINT_N_WAKEUPS:
    LOGSerial.print(F("Wakeups: "));
    LOGSerial.println(nWakeups);
    break;
  
  default:
    break;
  }
}