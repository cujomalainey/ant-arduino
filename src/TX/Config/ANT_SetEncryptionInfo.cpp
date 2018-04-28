#include <TX/Config/ANT_SetEncryptionInfo.h>

#include <ANT_private_defines.h>

#ifdef UNIT_TEST
#include "Util/Testing.h"
#else
#include "Arduino.h"
#endif

SetEncryptionInfo::SetEncryptionInfo() : AntRequest(SET_ENCRYPTION_INFO) {
}

SetEncryptionInfo::SetEncryptionInfo(uint8_t param, uint8_t* data) : AntRequest(SET_ENCRYPTION_INFO), _setParameter(param) {
    memcpy(_dataString, data, getDataStringSize());
}

void SetEncryptionInfo::setParameter(uint8_t param) {
    _setParameter = param;
}

void SetEncryptionInfo::setDataString(uint8_t* data) {
    memcpy(_dataString, data, getDataStringSize());
}

void SetEncryptionInfo::setDataStringByte(uint8_t byte, uint8_t pos) {
    _dataString[pos] = byte;
}

uint8_t SetEncryptionInfo::getParameter() {
    return _setParameter;
}

void SetEncryptionInfo::getDataString(uint8_t* arr) {
    memcpy(arr, _dataString, getDataStringSize());
}

uint8_t SetEncryptionInfo::getDataStringByte(uint8_t pos) {
    return _dataString[pos];
}

uint8_t SetEncryptionInfo::getData(uint8_t pos) {
    if (pos == 0) {
        return _setParameter;
    } else {
        return _dataString[pos - 1];
    }
}

uint8_t SetEncryptionInfo::getDataLength() {
    return SET_ENCRYPTION_INFO_LENGTH + getDataStringSize();
}

#ifdef NATIVE_API_AVAILABLE
uint8_t SetEncryptionInfo::execute() {
    // TODO
    return 0;
}
#endif // NATIVE_API_AVAILABLE

uint8_t SetEncryptionInfo::getDataStringSize() {
    switch (_setParameter) {
    case SET_ENCRYPTION_INFO_SET_PARAMETER_ENCRYPTION_ID:
        return SET_ENCRYPTION_INFO_DATA_STRING_ENCRYPTION_ID_SIZE;
    case SET_ENCRYPTION_INFO_SET_PARAMETER_USER_INFORMATION_STRING:
        return SET_ENCRYPTION_INFO_DATA_STRING_USER_INFORMATION_STRING_SIZE;
    case SET_ENCRYPTION_INFO_SET_PARAMETER_RANDOM_NUMBER_SEED:
        return SET_ENCRYPTION_INFO_DATA_STRING_RANDOM_NUMBER_SEED_SIZE;
    default:
        return 0;
    }
}
