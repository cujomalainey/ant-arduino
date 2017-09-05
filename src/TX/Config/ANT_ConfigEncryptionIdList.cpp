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
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _size;
    } else {
        return _type;
    }
}

uint8_t ConfigEncryptionIdList::getDataLength() {
    return CONFIG_ENCRYPTION_ID_LIST_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ConfigEncryptionIdList::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
