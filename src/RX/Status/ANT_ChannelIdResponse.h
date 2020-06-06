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
    uint16_t getDeviceNumber();
    uint8_t getDeviceType();
    uint8_t getTransmissionType();

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t subId, ANT_MESSAGE &buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = CHANNEL_ID;
};

#endif // ANT_CHANNELIDRESPONSE_h
