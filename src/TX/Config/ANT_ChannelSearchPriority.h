#ifndef ANT_CHANNELSEARCHPRIORITY_h
#define ANT_CHANNELSEARCHPRIORITY_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel search priority message, it is used to
 * configure a channels priority when searching for its device.
 * Higher priority channels will pre-empt lower priority channels
 */
class ChannelSearchPriority : public AntRequest {
public:
    ChannelSearchPriority();
    ChannelSearchPriority(uint8_t channel, uint8_t priority);
    void setChannel(uint8_t channel);
    void setPriority(uint8_t priority);
    uint8_t getChannel();
    uint8_t getPriority();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _priority;
};

#endif // ANT_CHANNELSEARCHPRIORITY_h