#ifndef ANT_CONFIGUREADVANCEDBURST_h
#define ANT_CONFIGUREADVANCEDBURST_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a configure advanced burst packet
 *
 */
class ConfigureAdvancedBurst : public AntRequest {
public:
    ConfigureAdvancedBurst();
    ConfigureAdvancedBurst(uint8_t enable, uint8_t maxPacketLength);
    void setEnable(uint8_t enable);
    void setMaxPacketLength(uint8_t maxPacketLength);
    void setRequiredFeatures(uint32_t requiredFeatures);
    void setOptionalFeatures(uint32_t optionalFeatures);
    void setStallCount(uint16_t stallCount);
    void setRetryCount(uint8_t retryCount);
    uint8_t getEnable();
    uint8_t getMaxPacketLength();
    uint32_t getRequiredFeatures();
    uint32_t getOptionalFeatures();
    uint16_t getStallCount();
    uint8_t getRetryCount();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _enable = 0;
    uint8_t _maxPacketLength = 0;
    uint32_t _requiredFeatures = 0;
    uint32_t _optionalFeatures = 0;
    uint16_t _stallCount = 0;
    uint8_t _retryCount = 0;
    uint8_t _extended = 0;
};

#endif // ANT_CONFIGUREADVANCEDBURST_h
