#ifndef ANT_SETENCRYPTIONKEY_h
#define ANT_SETENCRYPTIONKEY_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a set encryption key packet
 *
 */
class SetEncryptionKey : public AntRequest {
public:
    SetEncryptionKey();
    SetEncryptionKey(uint8_t index, uint8_t* key);
    void setVolatileKeyIndex(uint8_t index);
    void setEncryptionKey(uint8_t* key);
    void setEncryptionKeyByte(uint8_t byte, uint8_t pos);
    uint8_t getVolatileKeyIndex();
    uint8_t getEncryptionKeyByte(uint8_t pos);
    void getEncryptionKey(uint8_t* arr);
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _volatileKeyIndex = 0;
    uint8_t _encryptionKey[ENCRYPTION_KEY_SIZE] = {0};
};

#endif // ANT_SETENCRYPTIONKEY_h
