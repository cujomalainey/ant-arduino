#ifndef ANT_BASEFRAMEWORK_h
#define ANT_BASEFRAMEWORK_h

#if (defined(__MBED__) && !defined(ARDUINO))
    #define IS_MBED
#endif

#ifdef UNIT_TEST
#include <string.h>
#include "Util/Testing.h"
#elif defined(ARDUINO)
#include "Arduino.h"
#elif IS_MBED
#include "mbed.h"
#endif

#endif // ANT_BASEFRAMEWORK_h
