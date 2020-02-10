#ifndef ANT_ARDUINOSERIALANTWITHCALLBACKS_h
#define ANT_ARDUINOSERIALANTWITHCALLBACKS_h

#if defined(ARDUINO) || defined(UNIT_TEST)

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_ArduinoSerialAnt.h>

class ArduinoSerialAntWithCallbacks : public ArduinoSerialAnt, public BaseAntWithCallbacks {
public:
    ArduinoSerialAntWithCallbacks();
};

#endif // defined(ARDUINO) || defined(UNIT_TEST)

#endif // ANT_ARDUINOSERIALANTWITHCALLBACKS_h
