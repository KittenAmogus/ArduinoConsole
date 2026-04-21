#ifndef UTILS_H
#define UTILS_H

#include "core/types.h"
#include "core/memory.h"

// System callbacks
uint8_t launchApp(uint8_t appId);
uint8_t getEndItem();
const __FlashStringHelper* getAppName(uint8_t appId);

// Temporary utils file
#define CHECK_EVENT(event) (event ? (event = 0, 1) : 0)
#define CHECK_EVENT_BTN(btn) (CHECK_EVENT(sysmem.buttons.event.btn))

#endif // UTILS_H

