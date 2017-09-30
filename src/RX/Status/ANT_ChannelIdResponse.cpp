#include <RX/Status/ANT_ChannelIdResponse.h>

ChannelIdResponse::ChannelIdResponse() : AntResponse() {

}

uint8_t ChannelIdResponse::getChannelNumber() {
    return getFrameData()[0];
}

uint16_t ChannelIdResponse::getDeviceNumber() {
    uint16_t deviceNumber = getFrameData()[1];
    deviceNumber |= getFrameData()[2] << 8;
    return deviceNumber;
}

uint8_t ChannelIdResponse::getDeviceType() {
    return getFrameData()[3];
}

uint8_t ChannelIdResponse::getTransmissionType() {
    return getFrameData()[4];
}