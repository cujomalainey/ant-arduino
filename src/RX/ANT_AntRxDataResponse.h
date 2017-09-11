#ifndef ANT_ANTRXDATARESPONSE_h
#define ANT_ANTRXDATARESPONSE_h

#include <RX/ANT_AntRxDataResponse.h>
#include <RX/ANT_AntResponse.h>

/**
 * Common functionality for Ant messages to get channel data
 */
class AntRxDataResponse : public AntResponse {
public:
    AntRxDataResponse();
    /**
     * Returns the specified index of the payload.  The index may be 0 to getDataLength() - 1
     * This method is deprecated; use uint8_t* getData()
     */
    uint8_t getData(int index);
    /**
     * Returns the payload array.  This may be accessed from index 0 to getDataLength() - 1
     */
    uint8_t* getData();
    /**
     * Returns the length of the payload
     */
    virtual uint8_t getDataLength() = 0;
    /**
     * Returns the position in the frame data where the data begins,
     * its the same for all messages
     */
    uint8_t getDataOffset();
};
#endif //ANT_ANTRXDATARESPONSE_h