#ifndef ANT_BASEFRAMEWORK_h
#define ANT_BASEFRAMEWORK_h

#define IS_MBED (defined(__MBED__) && !defined(ARDUINO))

#ifdef UNIT_TEST
#include "Util/Testing.h"
#elif defined(ARDUINO)
#include "Arduino.h"
#elif IS_MBED
#include "mbed.h"
#endif

#endif // ANT_BASEFRAMEWORK_h
