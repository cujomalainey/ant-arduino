#include <TX/Config/ANT_ChannelId.h>

#include <ANT_defines.h>

#define CHANNEL_ID_LENGTH  0x05

ChannelId::ChannelId() : AntRequest(CHANNEL_ID) {

}

void ChannelId::setChannel(uint8_t channel) {
    _channel = channel;
}

void ChannelId::setDeviceNumber(uint16_t deviceNumber) {
    _deviceNumber = deviceNumber;
}

void ChannelId::setDeviceType(uint8_t deviceType) {
    _deviceType = deviceType;
}

void ChannelId::setTransmissionType(uint8_t transmissionType) {
    _transmissionType = transmissionType;
}

uint8_t ChannelId::getChannel() {
    return _channel;
}

uint16_t ChannelId::getDeviceNumber() {
    return _deviceNumber;
}

uint8_t ChannelId::getDeviceType() {
    return _deviceType;
}

uint8_t ChannelId::getTransmissionType() {
    return _transmissionType;
}

uint8_t ChannelId::getDataLength() {
    return CHANNEL_ID_LENGTH;
}

uint8_t ChannelId::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return (uint8_t)_deviceNumber;
    } else if (pos == 2) {
        return (uint8_t)(_deviceNumber >> BITS_IN_BYTE);
    } else if (pos == 3) {
        return _pairingBit ? ( _deviceType | 0x80 ) : ( _deviceType & 0x7F );
    } else {
        return _transmissionType;
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ChannelId::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE