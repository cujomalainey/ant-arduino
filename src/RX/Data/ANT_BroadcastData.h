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
    /**
     * Returns a pointer to the 8 byte payload
     */
    uint8_t* getData();
    /**
     * Returns the size of the payload
     */
    uint8_t getDataLength();
    /**
     * returns flag byte for extended data messages
     */
    uint8_t getFlagByte();
    static const uint8_t MSG_ID = BROADCAST_DATA;
};

#endif // ANT_BROADCASTDATA_h
