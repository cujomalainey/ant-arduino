#ifndef ANT_BASEFRAMEWORK_h
#define ANT_BASEFRAMEWORK_h

#ifdef UNIT_TEST
#include "Util/Testing.h"
#elif defined(ARDUINO)
#include "Arduino.h"
#elif defined(__MBED__)
#include "mbed.h"
#endif

#endif // ANT_BASEFRAMEWORK_h
