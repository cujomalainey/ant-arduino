#include <MainClasses/ANT_ArduinoNativeAntWithCallbacks.h>

#if defined(ARDUINO) && defined(NATIVE_API_AVAILABLE)

ArduinoNativeAntWithCallbacks::ArduinoNativeAntWithCallbacks() : ArduinoNativeAnt(), BaseAntWithCallbacks() {}

#endif // defined(ARDUINO) && defined(NATIVE_API_AVAILABLE)
