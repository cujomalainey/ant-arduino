#include <TX/Config/ANT_SetEncryptionKey.h>

#include <ANT_private_defines.h>
#include <BaseClasses/ANT_BaseFramework.h>

SetEncryptionKey::SetEncryptionKey() : AntRequest(SET_ENCRYPTION_KEY) {
}

SetEncryptionKey::SetEncryptionKey(uint8_t index, uint8_t* key) : AntRequest(SET_ENCRYPTION_KEY), _volatileKeyIndex(index) {
    memcpy(_encryptionKey, key, ENCRYPTION_KEY_SIZE);
}

void SetEncryptionKey::setVolatileKeyIndex(uint8_t index) {
    _volatileKeyIndex = index;
}

void SetEncryptionKey::setEncryptionKey(uint8_t* key) {
    memcpy(_encryptionKey, key, ENCRYPTION_KEY_SIZE);
}

void SetEncryptionKey::setEncryptionKeyByte(uint8_t byte, uint8_t pos) {
    if (pos < ENCRYPTION_KEY_SIZE) {
        _encryptionKey[pos] = byte;
    }
}

uint8_t SetEncryptionKey::getVolatileKeyIndex() {
    return _volatileKeyIndex;
}

uint8_t SetEncryptionKey::getEncryptionKeyByte(uint8_t pos) {
    return _encryptionKey[pos];
}

void SetEncryptionKey::getEncryptionKey(uint8_t* arr) {
    memcpy(arr, _encryptionKey, ENCRYPTION_KEY_SIZE);
}

uint8_t SetEncryptionKey::getData(uint8_t pos) {
    if (pos == 0) {
        return _volatileKeyIndex;
    } else {
        return _encryptionKey[pos - 1];
    }
}

uint8_t SetEncryptionKey::getDataLength() {
    return SET_ENCRYPTION_KEY_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE
uint8_t SetEncryptionKey::execute() {
    // TODO
    return 0;
}
#endif // NATIVE_API_AVAILABLE
