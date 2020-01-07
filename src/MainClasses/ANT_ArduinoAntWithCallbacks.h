#ifndef ANT_ARDUINOANTWITHCALLBACKS_h
#define ANT_ARDUINOANTWITHCALLBACKS_h

#ifdef ARDUINO

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_ArduinoAnt.h>

class ArduinoAntWithCallbacks : public ArduinoAnt, public BaseAntWithCallbacks {
public:
    ArduinoAntWithCallbacks();
};

#endif // ARDUINO

#endif // ANT_ARDUINOANTWITHCALLBACKS_h
