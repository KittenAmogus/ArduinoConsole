#ifndef PMEM_H
#define PMEM_H

// Get strings from PROGMEM
#define GET_STR_ADDR(source)          ((const char *)pgm_read_word(&source))
#define GET_STR_U8G2_FLASH(source)    ((const __FlashStringHelper*)(source))
#define GET_STR_U8G2_ARRAY(source)    ((const __FlashStringHelper*)GET_STR_ADDR(source))

#endif // PMEM_H

