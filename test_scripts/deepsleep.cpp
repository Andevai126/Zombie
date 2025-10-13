#include <Arduino.h>

#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
#include <SoftwareSerial.h>

SoftwareSerial LOGSerial(0, 1); // RX, TX

volatile bool watchdogTriggered = false;

void setup() {
  LOGSerial.begin(2400);
  // Setup an LED on pin 0 for testing
  pinMode(0, OUTPUT);
  digitalWrite(0, LOW);

  // Disable ADC and other peripherals for lower power
  ADCSRA &= ~(1 << ADEN); // Disable ADC
  ACSR |= (1 << ACD);     // Disable analog comparator
}

void setupWatchdogTimer();
void goToSleep();

void loop() {
  static unsigned long Nwakeups = 0;
  Nwakeups++;
  // Blink LED to show wakeup
  // digitalWrite(0, HIGH);
  // delay(100);
  // digitalWrite(0, LOW);

  // Setup watchdog to wake up in ~8 seconds
  setupWatchdogTimer();

  // Go to sleep
  goToSleep();

  // MCU will resume here after waking up
  LOGSerial.println(Nwakeups);
}

// ---------------------------------------
// Setup Watchdog to interrupt every ~8s
void setupWatchdogTimer() {
  cli(); // Disable interrupts

  MCUSR &= ~(1 << WDRF); // Clear reset flag
  WDTCR |= (1 << WDCE) | (1 << WDE); // Enable changes
  WDTCR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // Interrupt, ~8s

  sei(); // Enable interrupts
}

// ---------------------------------------
// Go to sleep (deep sleep mode)
void goToSleep() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Deepest sleep
  sleep_enable();
  sleep_bod_disable(); // Disable brown-out detector during sleep (saves power)
  sleep_cpu();         // Sleep here

  // MCU continues here after ISR wakes it
  sleep_disable();
}

// ---------------------------------------
// Watchdog Interrupt
ISR(WDT_vect) {
  // Wakes up the MCU from sleep — no code needed
}
