#include <TX/Config/ANT_SerialNumberSetChannelId.h>

#include <ANT_private_defines.h>

SerialNumberSetChannelId::SerialNumberSetChannelId() : AntRequest(SERIAL_NUMBER_SET_CHANNEL_ID) {

}

SerialNumberSetChannelId::SerialNumberSetChannelId(uint8_t channel) : AntRequest(SERIAL_NUMBER_SET_CHANNEL_ID) {
    setChannel(channel);
}

void SerialNumberSetChannelId::setChannel(uint8_t channel) {
    _channel = channel;
}

void SerialNumberSetChannelId::setDeviceType(uint8_t deviceType) {
    _deviceType = deviceType;
}

void SerialNumberSetChannelId::setPairingBit(bool paringBit) {
    _pairingBit = paringBit;
}

void SerialNumberSetChannelId::setTransmissionType(uint8_t transmissionType) {
    _transmissionType = transmissionType;
}

uint8_t SerialNumberSetChannelId::getChannel() {
    return _channel;
}

uint8_t SerialNumberSetChannelId::getDeviceType() {
    return _deviceType;
}

bool SerialNumberSetChannelId::getPairingBit() {
    return _pairingBit;
}

uint8_t SerialNumberSetChannelId::getTransmissionType() {
    return _transmissionType;
}

uint8_t SerialNumberSetChannelId::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _deviceType;
    } else {
        return _transmissionType;
    }
}

uint8_t SerialNumberSetChannelId::getDataLength() {
    return SERIAL_NUMBER_SET_CHANNEL_ID_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t SerialNumberSetChannelId::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE