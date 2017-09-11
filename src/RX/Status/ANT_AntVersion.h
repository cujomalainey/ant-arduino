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

    static const uint8_t MSG_ID = ANT_VERSION;
};

#endif // ANT_ANTVERSION_h