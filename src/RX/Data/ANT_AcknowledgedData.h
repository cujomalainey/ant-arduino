#ifndef ANT_ACKNOWLEDGEDDATA_h
#define ANT_ACKNOWLEDGEDDATA_h

#include <RX/ANT_AntRxDataResponse.h>

#include <ANT_defines.h>

/**
 * Represents a AcknowledgedData message
 */
class AcknowledgedData : public AntRxDataResponse {
public:
    AcknowledgedData();
    /**
     * Returns source channel
     */
    uint8_t getChannelNumber();
    /**
     * Returns sepcified byte of data from payload
     */
    uint8_t getData(uint8_t index) override;
    uint8_t* getData() override;
    uint8_t getDataLength() override;
    uint8_t getFlagByte() override;

    static const uint8_t MSG_ID = ACKNOWLEDGED_DATA;
};

#endif // ANT_ACKNOWLEDGEDDATA_h
