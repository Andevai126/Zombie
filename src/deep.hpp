#include <avr/io.h>
#include <avr/sleep.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>
// #include <avr/power.h>

volatile bool buttonISRtriggered = false;

void disable() {
  ADCSRA &= ~(1 << ADEN); // Disable ADC
  // ACSR |= (1 << ACD);     // Disable analog comparator
  // sleep_bod_disable();    // Disable brown-out detector
  // power_timer1_disable(); // Disable Timer1
  // power_usi_disable();    // Disable USI
}

// Configure and start deep sleep
void deepSleep() {
  // Double check peripherals are off
  digitalWrite(0, LOW);
  digitalWrite(1, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(4, HIGH);

  cli(); // Disable interrupts
    // Setup button
    GIMSK |= (1 << INT0); // Enable INT0 interrupt
    // Setup Watchdog to wake up in ~8 seconds
    MCUSR &= ~(1 << WDRF); // Clear reset flag
    WDTCR |= (1 << WDCE) | (1 << WDE); // Enable changes
    WDTCR = (1 << WDIE) | (1 << WDP3) | (1 << WDP0); // Interrupt, ~8s
    wdt_reset(); // Reset watchdog timer
  sei(); // Enable interrupts

  // Setup deep sleep
  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // Deepest sleep
  sleep_enable();

  // Enter deep sleep
  sleep_cpu();

  // Exit deep sleep here after an ISR wakes it
  sleep_disable();
}

// Button Interrupt
ISR(INT0_vect) {
  buttonISRtriggered = true;
}

// Watchdog Interrupt
ISR(WDT_vect) {
}