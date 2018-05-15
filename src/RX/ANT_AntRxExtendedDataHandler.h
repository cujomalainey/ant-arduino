#ifndef ANT_ANTRXEXTENDEDDATAHANDLER_h
#define ANT_ANTRXEXTENDEDDATAHANDLER_h
#include <RX/ANT_AntRxDataResponse.h>

/**
 * Handles Extended Fields in data messages
 */
class AntRxExtendedDataHandler : virtual public AntRxDataResponse {
public:
    AntRxExtendedDataHandler();
    /**
     * Call this method to determine what extended fields are available
     * TODO explain how to use
     */
    uint8_t getFlagByte();
    /**
     * TODO
     */
    uint16_t getDeviceNumber();
    /**
     * TODO
     */
    uint8_t getDeviceType();
    /**
     * TODO
     */
    uint8_t getTransmissionType();
    /**
     * TODO
     */
    uint8_t getMeasurementType();
    /**
     * TODO
     */
    int8_t getRSSIValue();
    /**
     * TODO
     */
    int8_t getThresholdConfigurationValue();
    /**
     * TODO
     */
    uint16_t getRxTimestamp();
protected:
    void setExtendedDataAvailibility(bool extendedAvailable);
private:
    bool enabled;
};

#endif // ANT_ANTRXEXTENDEDDATAHANDLER_h
