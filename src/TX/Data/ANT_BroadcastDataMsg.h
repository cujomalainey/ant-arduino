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
    explicit BroadcastDataMsg(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _channel = 0;
};

#endif // ANT_BROADCASTMSG_h
