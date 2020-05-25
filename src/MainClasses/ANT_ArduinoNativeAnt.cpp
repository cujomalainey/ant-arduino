#include <MainClasses/ANT_ArduinoNativeAnt.h>
#include <ANT_defines.h>

#ifdef NATIVE_API_AVAILABLE

ArduinoNativeAnt::ArduinoNativeAnt() : BaseNativeAnt() {}

uint32_t ArduinoNativeAnt::getMs() {
    return millis();
}

#endif // NATIVE_API_AVAILABLE
