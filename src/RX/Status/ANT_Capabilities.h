#ifndef ANT_CAPABILITIES_h
#define ANT_CAPABILITIES_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Capabilities message
 */
class Capabilities : public AntResponse {
public:
    Capabilities();
    uint8_t getMaxChannels();
    uint8_t getMaxNetworks();
    uint8_t getStandardOptions();
    uint8_t getAdvancedOptions(uint8_t pos); //note, this is 1 indexed to match the spec sheet
    uint8_t getMaxSensRcoreChannels();

    static const uint8_t MSG_ID = CAPABILITIES;
};

#endif // ANT_CAPABILITIES_h