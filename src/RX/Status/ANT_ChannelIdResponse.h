#ifndef ANT_CHANNELIDRESPONSE_h
#define ANT_CHANNELIDRESPONSE_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Channel Id Response Message
 */
class ChannelIdResponse : public AntResponse {
public:
    ChannelIdResponse();
    uint8_t getChannelNumber();

    static const uint8_t MSG_ID = CHANNEL_ID;
};

#endif // ANT_CHANNELIDRESPONSE_h