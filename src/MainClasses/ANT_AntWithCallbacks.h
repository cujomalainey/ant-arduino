#ifndef ANT_ANTWITHCALLBACKS_h
#define ANT_ANTWITHCALLBACKS_h

#include <BaseClasses/ANT_BaseAntWithCallbacks.h>
#include <MainClasses/ANT_Ant.h>

class AntWithCallbacks : public Ant, public BaseAntWithCallbacks {
public:
    AntWithCallbacks();
};

#endif // ANT_ANTWITHCALLBACKS_h