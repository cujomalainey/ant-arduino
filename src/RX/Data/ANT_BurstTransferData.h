#ifndef ANT_BURSTTRANSFERDATA_h
#define ANT_BURSTTRANSFERDATA_h

#include <RX/ANT_AntRxDataResponse.h>

#include <ANT_defines.h>

/**
 * Represents a BurstTransferData message
 */
class BurstTransferData : public AntRxDataResponse {
public:
    BurstTransferData();
    /**
     * Returns source channel
     */
    uint8_t getChannelNumber();
    uint8_t getSequenceNumber();
    /**
     * Returns sepcified byte of data from payload
     */
    uint8_t getData(uint8_t index) override;
    uint8_t* getData() override;
    uint8_t getDataLength() override;
    uint8_t getFlagByte() override;

    static const uint8_t MSG_ID = BURST_TRANSFER_DATA;
};

#endif // ANT_BURSTTRANSFERDATA_h
