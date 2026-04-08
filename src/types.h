#ifndef TYPES_H
#define TYPES_H

#include <Arduino.h>
#include <stdint.h>

#define PACKED __attribute__((packed))

typedef struct {
  uint32_t lastUpdate_ms;

  // Is pressed
  union {
    struct {
      uint8_t SEL:   1;
      uint8_t END:   1;
      uint8_t UP:    1;
      uint8_t DOWN:  1;
      uint8_t RIGHT: 1;
      uint8_t LEFT:  1;
      uint8_t _unused: 2;
    };
    uint8_t mask;
  } is;

  // Is pressed
  union {
    struct {
      uint8_t SEL:   1;
      uint8_t END:   1;
      uint8_t UP:    1;
      uint8_t DOWN:  1;
      uint8_t RIGHT: 1;
      uint8_t LEFT:  1;
      uint8_t _unused: 2;
    };
    uint8_t mask;
  } event;

  } PACKED Buttons;

#endif // TYPES_H

