#ifndef ANT_ANTTXDATAREQUEST_h
#define ANT_ANTTXDATAREQUEST_h

#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

/**
 * Common functionality for Ant messages to set/send channel data
 */
class AntTxDataRequest : public AntRequest {
public:
    AntTxDataRequest(uint8_t msgId);
    /**
     * Returns a pointer to the buffer
     */
    uint8_t* getDataBuffer();
    /**
     * Returns the length of the payload
     */
    uint8_t getDataBufferLength();
    /**
     * Sets the data array
     */
    void setDataBuffer(uint8_t* dataPtr);

protected:
    void setDataLength(uint8_t length);

private:
    uint8_t* _data;
    uint8_t  _dataLength;
};

#endif // ANT_ANTTXDATAREQUEST_h
