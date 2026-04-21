#include "input.h"

void updateButtons(Buttons *buttons) {
  uint8_t rawD = ~PIND; // Digital
  uint8_t rawC = ~PINC; // Analog
 
  // D-PAD (Analog)
  uint8_t mask = (rawC & 0x0F);  // A0-A3
 
  // Special buttons (Digital)
  mask |= (rawD & (1 << PD2)) << 2; // D2
  mask |= (rawD & (1 << PD4)) << 1; // D4
  mask |= (rawD & (1 << PD7)) >> 1; // D7

  // Events
  buttons->event.mask |= (~buttons->is.mask) & mask;
  buttons->is.mask = mask;
}

