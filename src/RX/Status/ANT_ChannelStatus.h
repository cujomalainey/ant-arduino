#ifndef ANT_CHANNELSTATUS_h
#define ANT_CHANNELSTATUS_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Channel Status message
 */
class ChannelStatus : public AntResponse {
public:
    ChannelStatus();
    uint8_t getChannelNumber();
    uint8_t getChannelState();
    uint8_t getNetworkNumber();
    uint8_t getChannelType();

    static const uint8_t MSG_ID = CHANNEL_STATUS;
};

#endif // ANT_CHANNELSTATUS_h
