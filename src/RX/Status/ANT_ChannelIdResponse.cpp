#include <RX/Status/ANT_ChannelIdResponse.h>

ChannelIdResponse::ChannelIdResponse() : AntResponse() {

}

uint8_t ChannelIdResponse::getChannelNumber() {
    return getFrameData()[0];
}

uint16_t ChannelIdResponse::getDeviceNumber() {
    uint16_t deviceNumber = getFrameData()[1];
    deviceNumber |= getFrameData()[2] << BITS_IN_BYTE;
    return deviceNumber;
}

uint8_t ChannelIdResponse::getDeviceType() {
    return getFrameData()[3];
}

uint8_t ChannelIdResponse::getTransmissionType() {
    return getFrameData()[4];
}

#ifdef NATIVE_API_AVAILABLE

static uint32_t ChannelIdResponse::backFill(uint8_t subId, uint8_t *buf) {
    return
}

#endif // NATIVE_API_AVAILABLE
