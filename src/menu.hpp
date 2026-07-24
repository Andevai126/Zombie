#define START_EXP_1 1
#define START_EXP_2 2
#define START_EXP_3 3
#define START_EXP_4 4
#define START_EXP_5 5

void blink() {
  digitalWrite(3, HIGH);
  delay(100);
  digitalWrite(3, LOW);
}

uint8_t getSelection() {
  // Wait for button release
  while (buttonISRtriggered) {
    buttonISRtriggered = false;
    delay(100);
  }
  uint8_t counter = 0;
  LOGSerial.print(F("Counting presses"));
  unsigned long timer = millis();
  while (millis() - timer < 6000) {
    if (buttonISRtriggered) {
      // Wait for button release
      while (buttonISRtriggered) {
        buttonISRtriggered = false;
        delay(100);
      }
      counter++;
      LOGSerial.print(F("."));
    }
  }
  LOGSerial.println();
  LOGSerial.print(F("Selected option: "));
  LOGSerial.println(counter);
  for (int i = 0; i < counter; i++) {
    blink();
    delay(200);
  }
  return counter;
}