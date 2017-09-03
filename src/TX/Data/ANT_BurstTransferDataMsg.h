#ifndef ANT_BURSTTRANSFERDATAMSG_h
#define ANT_BURSTTRANSFERDATAMSG_h

#include <TX/ANT_AntTxDataRequest.h>

/**
 * Represents a Burst Transfer Data Tx message, it is used to send a message from the ANT radio
 */
class BurstTransferDataMsg : public AntTxDataRequest {
public:
    BurstTransferDataMsg();
    BurstTransferDataMsg(uint8_t channel);
    void setChannelSequence(uint8_t channel);
    uint8_t getChannelSequence();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _data[MESSAGE_SIZE];
    uint8_t _channel;
};

#endif // ANT_BURSTTRANSFERDATAMSG_h