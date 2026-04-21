#ifndef MEMORY_H
#define MEMORY_H


#include "core/app.h"
#include "core/types.h"
#include "core/config.h"


typedef struct {

  App *runningApp;
  Buttons buttons;

  uint8_t nextAppId;  // For menu

  uint32_t bootTime;
  uint32_t currentTime;

  // Flags
  struct {
    uint8_t needRedraw  : 1;
    uint8_t needExit    : 1;
    uint8_t _unused     : 6;
  } PACKED;

} PACKED SystemMemory;
extern SystemMemory sysmem;

#define GLOBAL_RAM_SIZE 256 // (768 + 128)
extern uint8_t globalMemory[GLOBAL_RAM_SIZE];


#endif // MEMORY_H

