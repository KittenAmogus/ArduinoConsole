#ifndef MEMORY_H
#define MEMORY_H

#include <Arduino.h>
#include "types.h"

// Menu
typedef struct {
  uint8_t selected;
} PACKED MenuMemory;

typedef union {
  MenuMemory menu;
} PACKED SharedMemory;

typedef struct {

  uint32_t curTime;
  uint8_t needRedraw  : 1;
  uint8_t needExit    : 1;
  uint8_t _unused_flags : 6;

} PACKED GlobalMemory;

extern SharedMemory sharedMemory;
extern GlobalMemory globalMemory;

#endif // MEMORY_H

