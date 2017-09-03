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
    // TODO
}

uint8_t AddEncryptionIdToList::getChannel() {
    return _channel;
}

uint32_t AddEncryptionIdToList::getEncryptionId() {
    return _encryptionId;
}

uint8_t AddEncryptionIdToList::getListIndex() {
    // TODO
    return 0;
}

uint8_t AddEncryptionIdToList::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t AddEncryptionIdToList::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t AddEncryptionIdToList::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE