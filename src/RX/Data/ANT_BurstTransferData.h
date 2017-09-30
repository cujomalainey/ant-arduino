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
    /**
     * Returns sepcified byte of data from payload
     */
    uint8_t getData(uint8_t index);
    uint8_t* getData();
    uint8_t getDataLength();
    uint8_t getExtendedDataLength();
    uint8_t getExtendedData(uint8_t index);

    static const uint8_t MSG_ID = BURST_TRANSFER_DATA;
};

#endif // ANT_BURSTTRANSFERDATA_h