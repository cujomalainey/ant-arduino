#ifndef ANT_MBEDSERIALANTWITHCALLBACKS_h
#define ANT_MBEDSERIALANTWITHCALLBACKS_h

#include <BaseClasses/ANT_BaseFramework.h>

#if IS_MBED

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_MbedSerialAnt.h>

class MbedSerialAntWithCallbacks : public MbedSerialAnt, public BaseAntWithCallbacks {
public:
    MbedSerialAntWithCallbacks();
};

#endif // IS_MBED

#endif // ANT_MBEDSERIALANTWITHCALLBACKS_h
