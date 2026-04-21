#ifndef UTILS_H
#define UTILS_H

#include "core/types.h"
#include "core/memory.h"

// System callbacks
uint8_t launchApp(uint8_t appId);
uint8_t getEndItem();
const __FlashStringHelper* getAppName(uint8_t appId);

#define CHECK_EVENT(event) (event ? (event = 0, 1) : 0)
#define CHECK_EVENT_BTN(btn) (CHECK_EVENT(sysmem.buttons.event.btn))

#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? b : a)
#define ABS(a)    (a > 0 ? a : -a)
#define CLAMP(a, mn, mx)  (MIN(mx, MAX(a, mn)))

// For system info
int getFreeRAM();

#define RANDOM_SEED (0xACE1u)
uint16_t xorShift16();

#endif // UTILS_H

