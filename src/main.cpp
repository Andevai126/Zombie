#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial LOGSerial(-1, 1); // RX, TX

#include "df.hpp"
#include "deep.hpp"
#include "experiences.hpp"
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

  LOGSerial.println(F("\n\n --- Setup complete ---"));
}

void loop() {
  sleeping();

  // Select action
  uint8_t action = getSelection();

  // Perform action
  switch (action) {
    case START_EXP_1:
      experienceTest();
      break;
    
    case START_EXP_2:
      experienceGhost();
      break;
    
    case START_EXP_3:
      experienceAnimal();
      break;
    
    case START_EXP_4:
      experienceClown();
      break;
    
    case START_EXP_5:
      experienceBreakIn();
      break;
    
    default:
      break;
  }
}