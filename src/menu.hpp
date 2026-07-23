#define PLAY_TRACK_1 1
#define BLINK_LED 2
#define PLAY_RANDOM_TRACK 3
#define PRINT_N_HEARTBEATS 4
#define PRINT_N_WAKEUPS 5

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