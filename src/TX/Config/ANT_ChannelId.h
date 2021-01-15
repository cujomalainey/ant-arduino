#ifndef ANT_CHANNELID_h
#define ANT_CHANNELID_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel id message, it is used to
 * configure a channel connection on the ANT radio
 */
class ChannelId : public AntRequest {
public:
    ChannelId();
    ChannelId(uint8_t channel, uint16_t deviceNumber, uint8_t deviceType);
    ChannelId(uint8_t channel, uint16_t deviceNumber, uint8_t deviceType, bool paringBit, uint8_t transmissionType);
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
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _channel = 0;
    uint16_t _deviceNumber = 0;
    uint8_t _deviceType = 0;
    // TODO figure out default for pairing bit, assuming false
    bool _pairingBit = false;
    uint8_t _transmissionType = 0;
};

#endif // ANT_CHANNELID_h
