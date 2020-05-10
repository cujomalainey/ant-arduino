#ifndef ANT_ESPIDFSERIALANTWITHCALLBACKS_h
#define ANT_ESPIDFSERIALANTWITHCALLBACKS_h

#if defined(ESP_PLATFORM)

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_EspIdfSerialAnt.h>

class EspIdfSerialAntWithCallbacks : public EspIdfSerialAnt, public BaseAntWithCallbacks {
public:
    EspIdfSerialAntWithCallbacks();
};

#endif // defined(ESP_PLATFORM)

#endif // ANT_ESPIDFSERIALANTWITHCALLBACKS_h
