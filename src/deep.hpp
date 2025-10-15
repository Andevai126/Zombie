#include <Arduino.h>

#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>

volatile bool buttonISRtriggered = false;

void disable() {
  ADCSRA &= ~(1 << ADEN); // Disable ADC
  ACSR |= (1 << ACD);     // Disable analog comparator
}

void enable() {
  cli();
  GIMSK |= (1 << INT0); // Maybe remove!
  GIMSK|= (1<<PCIE);
  PCMSK|=(1<<PCINT2);
  sei();
}

// Configure and start deep sleep
void deepSleep() {
  // Double check DFPlayer is off
  digitalWrite(0, LOW);

  // Setup Watchdog to wake up in ~8 seconds
  cli(); // Disable interrupts
  MCUSR &= ~(1 << WDRF); // Clear reset flag
  WDTCR |= (1 << WDCE) | (1 << WDE); // Enable changes
  WDTCR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // Interrupt, ~8s
  wdt_reset();
  sei(); // Enable interrupts

  // Setup deep sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Deepest sleep
  sleep_enable();
  sleep_bod_disable(); // Disable brown-out detector during sleep (saves power)

  // Enter deep sleep
  sleep_cpu();

  // Exit deep sleep here after ISR wakes it
  sleep_disable();
}

// Button Interrupt
ISR(INT0_vect) {
  buttonISRtriggered = true;
}

// Watchdog Interrupt
ISR(WDT_vect) {
}