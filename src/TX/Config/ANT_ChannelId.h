#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel id message, it is used to
 * configure a channel connection on the ANT radio
 */
class ChannelId : public AntRequest {
public:
    ChannelId();
    void setChannel(uint8_t channel);
    void setDeviceNumber(uint16_t deviceNumber);
    void setDeviceType(uint8_t deviceType);
    void setPairingBit(bool paringBit);
    void setTransmissionType(uint8_t transmissionType);
    uint8_t getChannel();
    uint16_t getDeviceNumber();
    uint8_t getDeviceType();
    bool getPairingBit();
    uint8_t getTransmissionType();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    uint8_t _channel;
    uint16_t _deviceNumber;
    uint8_t _deviceType;
    bool _pairingBit;
    uint8_t _transmissionType;
};