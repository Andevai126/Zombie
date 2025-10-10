#include <Arduino.h>
#include <SoftwareSerial.h>

// Serial for DFPlayer
SoftwareSerial DFSerial(10, 11); // RX, TX

// Function to create DFPlayer command
uint16_t calculateCheckSum(uint8_t *buffer) {
  uint16_t sum = 0;
  for (int i = 1; i < 7; i++) {
    sum += buffer[i];
  }
  return -sum;
}

uint8_t* createCommand(uint8_t command, uint8_t argHigh, uint8_t argLow) {
  static uint8_t array[10] = {0x7E, 0xFF, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xEF};
  array[3] = command;
  array[5] = argHigh;
  array[6] = argLow;
  uint16_t checksum = calculateCheckSum(array);
  array[7] = (uint8_t)(checksum >> 8);
  array[8] = (uint8_t)(checksum & 0xFF);
  return array;
}

void setup() {
  Serial.begin(9600);        // For Serial Monitor
  DFSerial.begin(9600);      // For DFPlayer
  Serial.println("Ready. Send command like: 03 00 01");
}

void loop() {
  // Check if user sent data via Serial Monitor
  if (Serial.available()) {
    String s1 = Serial.readStringUntil(' ');
    String s2 = Serial.readStringUntil(' ');
    String s3 = Serial.readStringUntil('\n');

    if (!(s1.length() == 0 || s2.length() == 0 || s3.length() == 0)) {
      uint8_t byte1 = (uint8_t) strtol(s1.c_str(), NULL, 16);
      uint8_t byte2 = (uint8_t) strtol(s2.c_str(), NULL, 16);
      uint8_t byte3 = (uint8_t) strtol(s3.c_str(), NULL, 16);

      uint8_t* command = createCommand(byte1, byte2, byte3);

      // Send command to DFPlayer
      DFSerial.write(command, 10);
      Serial.print("Sent: ");
      for (int i = 0; i < 10; i++) {
        Serial.print(command[i], HEX);
        Serial.print(" ");
      }
      Serial.println();

      // Wait and read response
      unsigned long start = millis();
      Serial.print("Reply: < ");
      while (millis() - start < 1000) {
        if (DFSerial.available()) {
          uint8_t b = DFSerial.read();
          Serial.print(b, HEX);
          Serial.print(" ");
        }
      }
      Serial.println(">");
    }
  }
}
