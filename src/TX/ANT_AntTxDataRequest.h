#include <TX/ANT_AntRequest.h>

/**
 * Common functionality for Ant messages to set/send channel data
 */
// class AntTxDataRequest : public AntRequest {
// public:
    // AntTxDataRequest();
    /**
     * Returns the specified index of the payload.  The index may be 0 to getDataLength() - 1
     * This method is deprecated; use uint8_t* getData()
     */
    // uint8_t getData(int index);
    /**
     * Copies payload into buffer.  This may be accessed from index 0 to getDataLength() - 1
     */
    // void getData(uint8_t* buffer);
    /**
     * Returns the length of the payload
     */
    // virtual uint8_t getDataLength() = 0;
    /**
     * Returns the position in the frame data where the data begins,
     * its the same for all messages
     */

//     void setData(uint8_t* data);

// protected:
//     uint8_t getDataOffset();

// private:
//     uint8_t _data[MESSAGE_SIZE];
// };