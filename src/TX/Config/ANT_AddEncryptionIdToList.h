#ifndef ANT_ADDENCRYPTIONIDTOLIST_h
#define ANT_ADDENCRYPTIONIDTOLIST_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Add Encryption Id To List message, it is used to add
 * an encryption id to a list
 */
class AddEncryptionIdToList : public AntRequest {
public:
    AddEncryptionIdToList();
    void setChannel(uint8_t channel);
    void setEncryptionId(uint32_t encryptionId);
    void setListIndex(uint8_t listIndex);
    uint8_t getChannel();
    uint32_t getEncryptionId();
    uint8_t getListIndex();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    // TODO missing var for list index?
    uint8_t _channel;
    uint32_t _encryptionId;
};

#endif // ANT_ADDENCRYPTIONIDTOLIST_h