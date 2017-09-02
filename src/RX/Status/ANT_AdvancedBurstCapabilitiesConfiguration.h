#ifndef ANT_ADVANCEDBURSTCAPABILITIESCONFIGURATION_h
#define ANT_ADVANCEDBURSTCAPABILITIESCONFIGURATION_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Advanced Burst Capabilities or Current Configuration message
 */
class AdvancedBurstCapabilitiesConfiguration : public AntResponse {
public:
    AdvancedBurstCapabilitiesConfiguration();
    uint8_t getMsgType();
    // Capabilities Methods
    uint8_t getSupportedMaxPacketLength();
    uint32_t getSupportedFeatures();
    // Current Configuration Methods
    bool enable();
    uint8_t getMaxPacketLength();
    uint32_t getRequiredFeatures();
    uint32_t getOptionalFeatures();

    static const uint8_t MSG_ID = ADVANCED_BURST_CAPABILITES;
};

#endif // ANT_ADVANCEDBURSTCAPABILITIESCONFIGURATION_h