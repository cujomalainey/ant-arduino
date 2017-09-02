#ifndef ANT_BROADCASTDATA_h
#define ANT_BROADCASTDATA_h

#include <RX/ANT_AntRxDataResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Ant Broadcast data message
 */
class BroadcastData : public AntRxDataResponse {
public:
    BroadcastData();
    /**
     * Returns source channel
     */
    uint8_t getChannelNumber();
    /**
     * Returns sepcified byte of data from payload
     */
    uint8_t getData(uint8_t index);
    uint8_t* getData();
    uint8_t getExtendedDataLength();
    uint8_t getExtendedData(uint8_t index);
    uint8_t getDataLength();
    static const uint8_t MSG_ID = BROADCAST_DATA;
};

#endif // ANT_BROADCASTDATA_h