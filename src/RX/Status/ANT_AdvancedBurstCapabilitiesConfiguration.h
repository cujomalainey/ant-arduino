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
    /**
     * returns 0 for a capabilities message, 1 for a current configuration
     */
    uint8_t getMsgType();
    // Capabilities Methods
    uint8_t getSupportedMaxPacketLength();
    uint32_t getSupportedFeatures();

    // Current Configuration Methods

    /**
     * Defines whether advanced burst is enabled
     */
    uint8_t enable();
    uint8_t getMaxPacketLength();
    uint32_t getRequiredFeatures();
    uint32_t getOptionalFeatures();

    // TODO Stall count, retry count

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t subId, uint8_t *buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = ADVANCED_BURST_CAPABILITES;
};

#endif // ANT_ADVANCEDBURSTCAPABILITIESCONFIGURATION_h
