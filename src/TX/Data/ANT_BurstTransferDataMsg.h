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
    void setChannelNumber(uint8_t channel);
    /**
     * Sets the sequence number for the message (upper 3 bits of first byte)
     *
     * Make sure your read up on seqno in the ant docs before you use this
     */
    void setSequenceNumber(uint8_t seqNo);
    uint8_t getChannelSequence();
    uint8_t getSequenceNumber();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
    void setDataLength(uint8_t length);
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
};

#endif // ANT_BURSTTRANSFERDATAMSG_h
