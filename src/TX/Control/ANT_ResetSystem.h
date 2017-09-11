#ifndef ANT_RESETSYSTEM_h
#define ANT_RESETSYSTEM_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a reset system message, it is used to reset the ANT radio
 */
class ResetSystem : public AntRequest {
public:
    ResetSystem();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
};

#endif // ANT_RESETSYSTEM_h