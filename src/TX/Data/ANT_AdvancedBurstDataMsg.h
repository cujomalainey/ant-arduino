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
    void setChannelSequence(uint8_t channel);
    uint8_t getChannelSequence();
    uint8_t getData(uint8_t pos);
    void setDataLength(uint8_t length);
    uint8_t getDataLength();
    uint8_t _data[MESSAGE_SIZE];
    uint8_t _channel;
};

#endif // ANT_ADVANCEDBURSTDATAMSG_h