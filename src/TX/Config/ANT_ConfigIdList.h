#ifndef ANT_CONFIGIDLIST_h
#define ANT_CONFIGIDLIST_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Config Id List message, it is used to
 * configure a  ID list for a specific channel for
 * inclusion/exclusion purposes. This only works in slave mode.
 */
class ConfigIdList : public AntRequest {
public:
    ConfigIdList();
    void setChannel(uint8_t channel);
    void setListSize(uint8_t size); // [0-4]
    void setExclusion(uint8_t type);
    uint8_t getChannel();
    uint8_t getListSize();
    uint8_t getListType();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _size;
    uint8_t _type;
};

#endif // ANT_CONFIGIDLIST_h