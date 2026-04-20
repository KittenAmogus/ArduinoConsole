#ifndef MEMORY_H
#define MEMORY_H


#include "core/types.h"
#include "core/config.h"


typedef struct {

  App *runningApp;
  Buttons buttons;

  // Flags
  struct {
    uint8_t needRedraw  : 1;
    uint8_t needExit    : 1;
    uint8_t _unused     : 6;
  } PACKED;

} PACKED SystemMemory;
extern SystemMemory sysmem;

#define GLOBAL_RAM_SIZE 1024
extern uint8_t globalMemory[GLOBAL_RAM_SIZE];


#endif // MEMORY_H

