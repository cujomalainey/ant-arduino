#include <TX/ANT_AntRequest.h>

/**
 * Represents a Config Encryption Id List message, it is used to
 * configure a encryption ID list for a specific channel
 * IDs must be configured using AddEncryptionIdToList
 */
class ConfigEncryptionIdList : public AntRequest {
public:
    ConfigEncryptionIdList();
    void setChannel(uint8_t channel);
    void setListSize(uint8_t size); // [0-4]
    void setListType(uint8_t type);
    uint8_t getChannel();
    uint8_t getListSize();
    uint8_t getListType();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
    uint8_t _size;
    uint8_t _type;
};