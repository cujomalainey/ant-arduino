#include <TX/Config/ANT_ConfigEncryptionIdList.h>

#include <ANT_private_defines.h>

ConfigEncryptionIdList::ConfigEncryptionIdList() : AntRequest(CONFIG_ENCRYPTION_ID_LIST) {

}

ConfigEncryptionIdList::ConfigEncryptionIdList(uint8_t channel, uint8_t size, uint8_t type) : AntRequest(CONFIG_ENCRYPTION_ID_LIST) {
    setChannel(channel);
    setListSize(size);
    setListType(type);
}

void ConfigEncryptionIdList::setChannel(uint8_t channel) {
    _channel = channel;
}

void ConfigEncryptionIdList::setListSize(uint8_t size) {
    // TODO verify range is [0-4]
    _size = size <= CONFIG_ENCRYPTION_ID_LIST_MAX_LIST_SIZE ? size : CONFIG_ENCRYPTION_ID_LIST_MAX_LIST_SIZE;
}

void ConfigEncryptionIdList::setListType(uint8_t type) {
    _type = type;
}

uint8_t ConfigEncryptionIdList::getChannel() {
    return _channel;
}

uint8_t ConfigEncryptionIdList::getListSize() {
    return _size;
}

uint8_t ConfigEncryptionIdList::getListType() {
    return _type;
}

uint8_t ConfigEncryptionIdList::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t ConfigEncryptionIdList::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ConfigEncryptionIdList::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE