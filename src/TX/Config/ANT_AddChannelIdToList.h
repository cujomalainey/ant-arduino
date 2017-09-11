#ifndef ANT_ADDCHANNELIDTOLIST_h
#define ANT_ADDCHANNELIDTOLIST_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents Add Channel Id To List message, it is used to add
 * a channel to a specified list
 */
class AddChannelIdToList : public AntRequest {
public:
    AddChannelIdToList();
    AddChannelIdToList(uint8_t channel, uint16_t deviceNumber, uint8_t deviceType,  uint8_t transmissionType, uint8_t listIndex);
    void setChannel(uint8_t channel);
    void setDeviceNumber(uint16_t deviceNumber);
    void setDeviceType(uint8_t deviceType);
    void setTransmissionType(uint8_t transmissionType);
    void setListIndex(uint8_t listIndex);
    uint8_t getChannel();
    uint16_t getDeviceNumber();
    uint8_t getDeviceType();
    uint8_t getTransmissionType();
    uint8_t getListIndex();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint16_t _deviceNumber;
    uint8_t _deviceType;
    uint8_t _transmissionType;
    uint8_t _listIndex;
};

#endif // ANT_ADDCHANNELIDTOLIST_h