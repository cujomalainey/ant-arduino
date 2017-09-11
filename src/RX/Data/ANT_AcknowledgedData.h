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
    uint8_t getData(uint8_t index);
    uint8_t getDataLength();
    uint8_t getExtendedDataLength();
    uint8_t getExtendedData(uint8_t index);

    static const uint8_t MSG_ID = ACKNOWLEDGED_DATA;
};

#endif // ANT_ACKNOWLEDGEDDATA_h