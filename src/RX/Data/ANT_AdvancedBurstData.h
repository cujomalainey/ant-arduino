#ifndef ANT_ADVANCEDBURSTDDATA_h
#define ANT_ADVANCEDBURSTDDATA_h

#include <RX/ANT_AntRxDataResponse.h>

#include <ANT_defines.h>

/**
 * Represents a AdvancedBurstData message
 */
class AdvancedBurstData : public AntRxDataResponse {
public:
    AdvancedBurstData();
    /**
     * Returns source channel
     */
    uint8_t getChannelNumber();
    uint8_t getSequenceNumber();
    /**
     * Returns sepcified byte of data from payload
     */
    uint8_t getData(uint8_t index) override;
    uint8_t getDataLength() override;
    /**
     * AdvancedBurstData does not support extended data
     * therefore we lock it out with this method
     */
    uint8_t getFlagByte() override;

    static const uint8_t MSG_ID = ADVANCED_BURST_DATA;
};

#endif // ANT_ADVANCEDBURSTDDATA_h
