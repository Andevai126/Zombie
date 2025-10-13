#include <Arduino.h>


#include "df.hpp"
#include "test.hpp"
#include "deep.hpp"


void setup() {
  // Setup Serials
  LOGSerial.begin(2400);
  DFSerial.begin(9600);
  // Set focus, writing always works
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

  // Save power
  disable();

  LOGSerial.print(F("Setup complete"));
}

void loop() {
  static unsigned long Nwakeups = 0;
  Nwakeups++;

  // Blink LED to show wakeup
  digitalWrite(3, HIGH);
  delay(500);
  digitalWrite(3, LOW);

  // Print wakeup count, i.e. heartbeat
  LOGSerial.print(Nwakeups);
  LOGSerial.print(F(" "));

  // Run possible tests
  unsigned long timer = millis();
  while (millis() - timer < 8000) {
    test();
  }
  LOGSerial.print(F("end test"));

  // Sleep until interrupt
  while (!buttonISRtriggered) {
    deepSleep();
    LOGSerial.print(F("."));
  }
  LOGSerial.print(F(" btn: "));
  LOGSerial.println(buttonISRtriggered);
  buttonISRtriggered = false;
}