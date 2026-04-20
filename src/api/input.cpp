#include "input.h"

// Pins are D2 -> D7
void updateButtons(Buttons *buttons) {
  // SEL, END, UP, DOWN, RIGHT, LEFT
  uint8_t mask = (~PIND >> 2) & 0x3F;

  buttons->event.mask = (mask & ~buttons->is.mask);
  buttons->is.mask = mask;
}

