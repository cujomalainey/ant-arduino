#ifndef ANT_ANTVERSION_h
#define ANT_ANTVERSION_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a ANT Version message
 */
class AntVersion : public AntResponse {
public:
    AntVersion();
    uint8_t getVersionByte(uint8_t pos);

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t subId, uint8_t *buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = ANT_VERSION;
};

#endif // ANT_ANTVERSION_h
