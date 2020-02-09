#ifndef ANT_CONFIGENCRYPTIONIDLIST_h
#define ANT_CONFIGENCRYPTIONIDLIST_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Config Encryption Id List message, it is used to
 * configure a encryption ID list for a specific channel
 * IDs must be configured using AddEncryptionIdToList
 */
class ConfigEncryptionIdList : public AntRequest {
public:
    ConfigEncryptionIdList();
    ConfigEncryptionIdList(uint8_t channel, uint8_t size, uint8_t type);
    void setChannel(uint8_t channel);
    void setListSize(uint8_t size); // [0-4]
    void setListType(uint8_t type);
    uint8_t getChannel();
    uint8_t getListSize();
    uint8_t getListType();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _size;
    uint8_t _type;
};

#endif // ANT_CONFIGENCRYPTIONIDLIST_h
