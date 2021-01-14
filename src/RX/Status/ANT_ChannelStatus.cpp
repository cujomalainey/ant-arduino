#include <RX/Status/ANT_ChannelStatus.h>

#include <ANT_private_defines.h>

ChannelStatus::ChannelStatus() : AntResponse() {

}

uint8_t ChannelStatus::getChannelNumber() {
    return getFrameData()[0];
}

// cppcheck-suppress unusedFunction
uint8_t ChannelStatus::getChannelState() {
    return getFrameData()[1] & CHANNEL_STATUS_STATE_MASK;
}

// cppcheck-suppress unusedFunction
uint8_t ChannelStatus::getNetworkNumber() {
    return ( getFrameData()[1] >> CHANNEL_STATUS_NETWORK_NUMBER_SHIFT ) & CHANNEL_STATUS_NETWORK_NUMBER_MASK;
}

// cppcheck-suppress unusedFunction
uint8_t ChannelStatus::getChannelType() {
    return getFrameData()[1] >> CHANNEL_STATUS_CHANNEL_TYPE_SHIFT;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t ChannelStatus::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_ucSize = MESG_CHANNEL_STATUS_SIZE;
    buf.ANT_MESSAGE_aucMesgData[0] = subId;
    return sd_ant_channel_status_get(subId, &buf.ANT_MESSAGE_aucMesgData[1]);
}

#endif // NATIVE_API_AVAILABLE
