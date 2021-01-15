#ifndef ANT_SERIALNUMBERSETCHANNELID_h
#define ANT_SERIALNUMBERSETCHANNELID_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a serial number set channel id message
 *
 * used to configure a radio to use a devices serial number
 */
class SerialNumberSetChannelId : public AntRequest {
public:
    SerialNumberSetChannelId();
    explicit SerialNumberSetChannelId(uint8_t channel);
    void setChannel(uint8_t channel);
    void setDeviceType(uint8_t deviceType);
    void setPairingBit(bool paringBit);
    void setTransmissionType(uint8_t transmissionType);
    uint8_t getChannel();
    uint8_t getDeviceType();
    bool getPairingBit();
    uint8_t getTransmissionType();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel = 0;
    uint8_t _deviceType = 0;
    // TODO figure out default for pairing bit, assuming false
    bool _pairingBit = false;
    uint8_t _transmissionType = 0;
};

#endif // ANT_SERIALNUMBERSETCHANNELID_h
