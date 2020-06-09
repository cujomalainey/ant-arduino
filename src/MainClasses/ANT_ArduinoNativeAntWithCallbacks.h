#ifndef ANT_ARDUINONATIVEANTWITHCALLBACKS_h
#define ANT_ARDUINONATIVEANTWITHCALLBACKS_h

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_ArduinoNativeAnt.h>

#if defined(ARDUINO) && defined(NATIVE_API_AVAILABLE)

class ArduinoNativeAntWithCallbacks : public ArduinoNativeAnt, public BaseAntWithCallbacks {
public:
    ArduinoNativeAntWithCallbacks();
};

#endif // defined(ARDUINO) && defined(NATIVE_API_AVAILABLE)

#endif // ANT_ARDUINONATIVEANTWITHCALLBACKS_h
