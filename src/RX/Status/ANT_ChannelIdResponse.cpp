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

uint32_t ChannelIdResponse::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    uint16_t id;
    uint32_t ret;
    buf.ANT_MESSAGE_aucMesgData[0] = subId;
    ret = sd_ant_channel_id_get(subId, &id, &buf.ANT_MESSAGE_aucMesgData[3], &buf.ANT_MESSAGE_aucMesgData[4]);
    buf.ANT_MESSAGE_aucMesgData[1] = (uint8_t)id;
    buf.ANT_MESSAGE_aucMesgData[2] = (uint8_t)(id >> BITS_IN_BYTE);
    return ret;
}

#endif // NATIVE_API_AVAILABLE
