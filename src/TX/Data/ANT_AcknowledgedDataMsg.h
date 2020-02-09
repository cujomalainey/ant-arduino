#ifndef ANT_ACKNOWLEDGEDMSG_h
#define ANT_ACKNOWLEDGEDMSG_h

#include <TX/ANT_AntTxDataRequest.h>

#include <ANT_defines.h>

/**
 * Represents a Acknowledged Tx message, it is used to send a message from the ANT radio
 */
class AcknowledgedDataMsg : public AntTxDataRequest {
public:
    AcknowledgedDataMsg();
    AcknowledgedDataMsg(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _channel;
};

#endif // ANT_ACKNOWLEDGEDMSG_h
