#ifndef ANT_NATIVEANTWITHCALLBACKS_h
#define ANT_NATIVEANTWITHCALLBACKS_h

#include <MainClasses/ANT_NativeAnt.h>
#include <BaseClasses/ANT_BaseAntWithCallbacks.h>

#ifdef NATIVE_API_AVAILABLE

class NativeAntWithCallbacks : public NativeAnt, public BaseAntWithCallbacks
{
public:
    NativeAntWithCallbacks();
};

#endif

#endif // ANT_NATIVEANTWITHCALLBACKS_h