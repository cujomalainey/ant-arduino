#ifndef ANT_BASEFRAMEWORK_h
#define ANT_BASEFRAMEWORK_h

#ifdef UNIT_TEST
#include "Util/Testing.h"
#elif defined(ARDUINO)
#include "Arduino.h"
#elif defined(__MBED__)
#include "mbed.h"
#endif

class BaseFramework {
protected:
    virtual uint8_t read() = 0;
    virtual uint8_t available() = 0;
    virtual void write(uint8_t byte) = 0;

    virtual uint32_t getMs() = 0;
};

#endif // ANT_BASEFRAMEWORK_h
