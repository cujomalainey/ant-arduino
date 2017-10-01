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
    void setExtendedAssignment(uint8_t extended);
    uint8_t getChannel();
    uint8_t getChannelType();
    uint8_t getChannelNetwork();
    uint8_t getExtendedAssignment();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    uint8_t _channel;
    uint8_t _channelType;
    uint8_t _network;
    uint8_t _extended = 0;
};

#endif // ANT_ASSIGNCHANNEL_h