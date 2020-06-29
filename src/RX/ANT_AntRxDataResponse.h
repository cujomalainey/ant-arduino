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
    virtual uint8_t getData(uint8_t index);
    /**
     * Returns the payload array.  This may be accessed from index 0 to getDataLength() - 1
     */
    virtual uint8_t* getData();
    /**
     * Returns the length of the payload
     */
    virtual uint8_t getDataLength() = 0;
    /**
     * Returns the position in the frame data where the data begins,
     * its the same for all messages
     */
    uint8_t getDataOffset();
    /**
     * Call this method to determine what extended fields are available
     * Use LIB_CONFIG defines to check bits if they are set
     */
    virtual uint8_t getFlagByte() = 0;
    /**
     * Will return device number if getFlagByte() & LIB_CONFIG_CHANNEL_ID is true
     */
    uint16_t getDeviceNumber();
    /**
     * Will return device type if getFlagByte() & LIB_CONFIG_CHANNEL_ID is true
     */
    uint8_t getDeviceType();
    /**
     * Will return transmission type if getFlagByte() & LIB_CONFIG_CHANNEL_ID is true
     */
    uint8_t getTransmissionType();
    /**
     * Will return measurement type if getFlagByte() & LIB_CONFIG_RSSI is true
     */
    uint8_t getMeasurementType();
    /**
     * Will return rssi value if getFlagByte() & LIB_CONFIG_RSSI is true
     */
    int8_t getRSSIValue();
    /**
     * Will return threshoold configuration value if getFlagByte() & LIB_CONFIG_RSSI is true
     */
    int8_t getThresholdConfigurationValue();
    /**
     * Will return RX timestamp if getFlagByte() & LIB_CONFIG_RX_TIMESTAMP is true
     */
    uint16_t getRxTimestamp();
};
#endif //ANT_ANTRXDATARESPONSE_h
