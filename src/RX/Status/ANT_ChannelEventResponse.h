#ifndef ANT_CHANNELEVENTRESPONSE_h
#define ANT_CHANNELEVENTRESPONSE_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Channel Event or Channel Response Message
 */
class ChannelEventResponse : public AntResponse {
public:
    ChannelEventResponse();
    uint8_t getChannelNumber();
    uint8_t getResponseMsgId();
    uint8_t getCode();
    uint8_t getExtendedEventParameters();

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t chan, uint8_t msgId, uint8_t retCode, ANT_MESSAGE &buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = CHANNEL_RESPONSE;
};

#endif // ANT_CHANNELEVENTRESPONSE_h
