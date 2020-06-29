#ifndef ANT_ADVANCEDBURSTDATAMSG_h
#define ANT_ADVANCEDBURSTDATAMSG_h

#include <TX/ANT_AntTxDataRequest.h>

/**
 * Represents a Advanced Burst Data Tx message, it is used to send a message from the ANT radio
 */
class AdvancedBurstDataMsg : public AntTxDataRequest {
public:
    AdvancedBurstDataMsg();
    AdvancedBurstDataMsg(uint8_t channel, uint8_t length);
    void setChannelNumber(uint8_t channel);
    void setSequenceNumber(uint8_t seqNo);
    uint8_t getChannelNumber();
    uint8_t getSequenceNumber();
    uint8_t getData(uint8_t pos) override;
    void setDataLength(uint8_t length);
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
};

#endif // ANT_ADVANCEDBURSTDATAMSG_h
