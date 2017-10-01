#include <TX/Config/ANT_AddEncryptionIdToList.h>

#include <ANT_private_defines.h>

AddEncryptionIdToList::AddEncryptionIdToList() : AntRequest(ADD_ENCRYPTION_ID_TO_LIST) {

}

AddEncryptionIdToList::AddEncryptionIdToList(uint8_t channel, uint32_t encryptionId, uint8_t listIndex) : AntRequest(ADD_ENCRYPTION_ID_TO_LIST) {
    setChannel(channel);
    setEncryptionId(encryptionId);
    setListIndex(listIndex);
}

void AddEncryptionIdToList::setChannel(uint8_t channel) {
    _channel = channel;
}

void AddEncryptionIdToList::setEncryptionId(uint32_t encryptionId) {
    _encryptionId = encryptionId;
}

void AddEncryptionIdToList::setListIndex(uint8_t listIndex) {
    _listIndex = listIndex;
}

uint8_t AddEncryptionIdToList::getChannel() {
    return _channel;
}

uint32_t AddEncryptionIdToList::getEncryptionId() {
    return _encryptionId;
}

uint8_t AddEncryptionIdToList::getListIndex() {
    return _listIndex;
}

uint8_t AddEncryptionIdToList::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _encryptionId & 0xFF;
    } else if (pos == 2) {
        return (_encryptionId >> 8) & 0xFF;
    } else if (pos == 3) {
        return (_encryptionId >> 16) & 0xFF;
    } else if (pos == 4) {
        return _encryptionId >> 24;
    } else {
        return _listIndex;
    }
}

uint8_t AddEncryptionIdToList::getDataLength() {
    return ADD_ENCRYPTION_ID_TO_LIST_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t AddEncryptionIdToList::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE