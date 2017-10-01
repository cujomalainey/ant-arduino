#ifndef ANT_ENABLESINGLECHANNELENCRYPTION_h
#define ANT_ENABLESINGLECHANNELENCRYPTION_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a enable single channel encryption
 *
 * used to enable encryption on a single channel
 */
class EnableSingleChannelEncryption : public AntRequest {
public:
    EnableSingleChannelEncryption();
    EnableSingleChannelEncryption(uint8_t channel);
    void setChannel(uint8_t channel);
    void setEncryptionMode(uint8_t encryptionMode);
    void setVolatileKeyIndex(uint8_t index);
    void setDecimationRate(uint8_t rate);
    uint8_t getChannel();
    uint8_t getEncryptionMode();
    uint8_t getVolatileKeyIndex();
    uint8_t getDecimationRate();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _encryptionMode;
    uint8_t _volatileKeyIndex;
    uint8_t _decimationRate;
};

#endif // ANT_ENABLESINGLECHANNELENCRYPTION_h