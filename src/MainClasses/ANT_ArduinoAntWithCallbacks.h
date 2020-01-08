#ifndef ANT_ARDUINOANTWITHCALLBACKS_h
#define ANT_ARDUINOANTWITHCALLBACKS_h

#if defined(ARDUINO) || defined(UNIT_TEST)

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_ArduinoAnt.h>

class ArduinoAntWithCallbacks : public ArduinoAnt, public BaseAntWithCallbacks {
public:
    ArduinoAntWithCallbacks();
};

#endif // defined(ARDUINO) || defined(UNIT_TEST)

#endif // ANT_ARDUINOANTWITHCALLBACKS_h
