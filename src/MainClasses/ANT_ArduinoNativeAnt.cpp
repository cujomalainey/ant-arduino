#include <MainClasses/ANT_ArduinoNativeAnt.h>

#if defined(ARDUINO) && defined(NATIVE_API_AVAILABLE)

ArduinoNativeAnt::ArduinoNativeAnt() : BaseNativeAnt() {}

uint32_t ArduinoNativeAnt::getMs() {
    return millis();
}

#endif // defined(ARDUINO) && defined(NATIVE_API_AVAILABLE)
