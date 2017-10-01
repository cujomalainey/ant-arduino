#ifndef ANT_CONFIGURESELECTIVEDATAUPDATES_h
#define ANT_CONFIGURESELECTIVEDATAUPDATES_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a configure SDU packet
 *
 */
class ConfigureSelectiveDataUpdates : public AntRequest {
public:
    ConfigureSelectiveDataUpdates();
    ConfigureSelectiveDataUpdates(uint8_t channel);
    void setChannelNumber(uint8_t channel);
    void setSDUMaskNumer(uint8_t maskNo);
    /**
     * 0 Filter broadcast only
     * 1 Filter broadcast and Acknowledged
     */
    void setFilterAcknowledged(uint8_t filterBit);
    /**
     * Do not call any other setters after calling this function
     *
     * Use this function to disable the SDU mask on the specified channel
     */
    void setDisableSDUOnChannel();
    uint8_t getChannelNumber();
    uint8_t getSDUMaskNumer();
    uint8_t getFilterAcknowledged();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _selectedData;
};

#endif // ANT_CONFIGURESELECTIVEDATAUPDATES_h