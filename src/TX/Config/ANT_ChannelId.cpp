#include <TX/Config/ANT_ChannelId.h>

#include <ANT_private_defines.h>


ChannelId::ChannelId() : AntRequest(CHANNEL_ID) {

}

ChannelId::ChannelId(uint8_t channel, uint16_t deviceNumber, uint8_t deviceType) : AntRequest(CHANNEL_ID) {
    setChannel(channel);
    setDeviceNumber(deviceNumber);
    setDeviceType(deviceType);
}

ChannelId::ChannelId(uint8_t channel, uint16_t deviceNumber, uint8_t deviceType, bool paringBit, uint8_t transmissionType) : AntRequest(CHANNEL_ID) {
    setChannel(channel);
    setDeviceNumber(deviceNumber);
    setDeviceType(deviceType);
    setPairingBit(paringBit);
    setTransmissionType(transmissionType);
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

void ChannelId::setPairingBit(bool paringBit) {
    _pairingBit = paringBit;
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

bool ChannelId::getPairingBit() {
    return _pairingBit;
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
        // TODO get rid of magic numbers
        return _pairingBit ? ( _deviceType | 0x80 ) : ( _deviceType & 0x7F );
    } else {
        return _transmissionType;
    }
}

#ifdef NATIVE_API_AVAILABLE

uint32_t ChannelId::execute() {
    return sd_ant_channel_id_set(_channel, _deviceNumber, _deviceType, _transmissionType);
}

#endif // NATIVE_API_AVAILABLE
