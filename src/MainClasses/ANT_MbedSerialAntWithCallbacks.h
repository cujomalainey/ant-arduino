#ifndef ANT_MBEDSERIALANTWITHCALLBACKS_h
#define ANT_MBEDSERIALANTWITHCALLBACKS_h

#ifdef __MBED__

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_MbedSerialAnt.h>

class MbedSerialAntWithCallbacks : public MbedSerialAnt, public BaseAntWithCallbacks {
public:
    MbedSerialAntWithCallbacks();
};

#endif // __MBED__

#endif // ANT_MBEDSERIALANTWITHCALLBACKS_h
