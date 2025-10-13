#include <Arduino.h>

#include <SoftwareSerial.h>

SoftwareSerial LOGSerial(0, 1); // RX, TX

void test() {
  if (LOGSerial.available()) {
    String s1 = LOGSerial.readStringUntil(' ');
    String s2 = LOGSerial.readStringUntil(' ');
    String s3 = LOGSerial.readStringUntil('\n');
    
    if (!(s1.length() == 0 || s2.length() == 0 || s3.length() == 0)) {
      LOGSerial.println("cmd: < " + s1 + " " + s2 + " " + s3 + " >");

      uint8_t byte1 = (uint8_t) strtol(s1.c_str(), NULL, 16);
      uint8_t byte2 = (uint8_t) strtol(s2.c_str(), NULL, 16);
      uint8_t byte3 = (uint8_t) strtol(s3.c_str(), NULL, 16);
      

      if (byte1 == 0 && byte2 == 0 && byte3 == 0) {
        LOGSerial.println("Test: Blink LED");
        digitalWrite(3, HIGH);
        delay(100);
        digitalWrite(3, LOW);
        return;
      }
      if (byte1 == 0 && byte2 == 0 && byte3 == 1) {
        LOGSerial.println("Test: Play track 1");
        play(1);
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