#ifndef ANT_BROADCASTMSG_h
#define ANT_BROADCASTMSG_h

#include <TX/ANT_AntTxDataRequest.h>

#include <ANT_defines.h>

/**
 * Represents a Broadcast Tx message, it is used to send a message from the ANT radio
 */
class BroadcastDataMsg : public AntTxDataRequest {
public:
    BroadcastDataMsg();
    BroadcastDataMsg(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    uint8_t _channel;
};

#endif // ANT_BROADCASTMSG_h
