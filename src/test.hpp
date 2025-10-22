#include <Arduino.h>

#include <SoftwareSerial.h>

SoftwareSerial LOGSerial(0, 1); // RX, TX


void printCharValues(String str) {
  for (unsigned int i = 0; i < str.length(); i++) {
    char c = str[i];
    LOGSerial.print((int)c); // Print the ASCII value of the character
    if (i < str.length() - 1) {
      LOGSerial.print(".");    // Add a space between values
    }
  }
}

void test() {
  if (LOGSerial.available()) {
    delay(300);
    while (LOGSerial.peek() < '0' || LOGSerial.peek() > 'F') {
      LOGSerial.read();
      if (!LOGSerial.available()) {
        return;
      }
    }
    if (!LOGSerial.available()) {
      return;
    }
    String s1 = LOGSerial.readStringUntil(' ');
    String s2 = LOGSerial.readStringUntil(' ');
    String s3 = LOGSerial.readStringUntil('\n');
    LOGSerial.flush();

    LOGSerial.print("cmd: <");
    LOGSerial.print(s1);
    LOGSerial.print("^");
    printCharValues(s1);
    LOGSerial.print("_");
    LOGSerial.print(s2);
    LOGSerial.print("^");
    printCharValues(s2);
    LOGSerial.print("_");
    LOGSerial.print(s3);
    LOGSerial.print("^");
    printCharValues(s3);
    LOGSerial.println(">");

    if (!(s1.length() == 0 || s2.length() == 0 || s3.length() == 0)) {
      LOGSerial.println("cmd: <" + s1 + " " + s2 + " " + s3 + ">");

      uint8_t byte1 = (uint8_t) strtol(s1.c_str(), NULL, 16);
      uint8_t byte2 = (uint8_t) strtol(s2.c_str(), NULL, 16);
      uint8_t byte3 = (uint8_t) strtol(s3.c_str(), NULL, 16);
      

      if (byte1 == 0xF0) {
        LOGSerial.println("Test: Blink LED");
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        return;
      }
      if (byte1 == 0xF1) {
        LOGSerial.println("Test: Play track 1");
        play(1, 6);
        return;
      }
      

      DFSerial.listen();
      DFSerial.flush();

      DFSerial.write(createCommand(byte1, byte2, byte3), 10);

      unsigned long timer1 = millis();
      LOGSerial.print("reply: < ");
      while (millis() - timer1 < 2000) {
        if (DFSerial.available()) {
          LOGSerial.print(DFSerial.read(), HEX);
          LOGSerial.write(" ");
        }
      }
      LOGSerial.println(">");

      LOGSerial.listen();
      LOGSerial.flush();
    }
  }
}