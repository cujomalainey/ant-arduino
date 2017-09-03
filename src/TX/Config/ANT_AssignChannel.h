#ifndef ANT_ASSIGNCHANNEL_h
#define ANT_ASSIGNCHANNEL_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a assign channel packet, which is used to associate a channel
 *
 */
class AssignChannel : public AntRequest {
public:
    AssignChannel();
    AssignChannel(uint8_t channel, uint8_t channelType, uint8_t network);
    void setChannel(uint8_t channel);
    void setChannelType(uint8_t channelType);
    void setChannelNetwork(uint8_t network);
    uint8_t getChannel();
    uint8_t getChannelType();
    uint8_t getChannelNetwork();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
protected:
    uint8_t _channel;
    uint8_t _channelType;
    uint8_t _network;
    // TODO what is this var??
    uint8_t _extended;
};

#endif // ANT_ASSIGNCHANNEL_h