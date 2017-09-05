#include <RX/Status/ANT_ChannelStatus.h>

#include <ANT_private_defines.h>

ChannelStatus::ChannelStatus() : AntResponse() {

}

uint8_t ChannelStatus::getChannelNumber() {
    return getFrameData()[0];
}

uint8_t ChannelStatus::getChannelState() {
    return getFrameData()[1] & CHANNEL_STATUS_STATE_MASK;
}

uint8_t ChannelStatus::getNetworkNumber() {
    return ( getFrameData()[1] >> CHANNEL_STATUS_NETWORK_NUMBER_SHIFT ) & CHANNEL_STATUS_NETWORK_NUMBER_MASK;
}

uint8_t ChannelStatus::getChannelType() {
    return getFrameData()[1] >> CHANNEL_STATUS_CHANNEL_TYPE_SHIFT;
}
