#include <TX/Config/ANT_ConfigIdList.h>

#include <ANT_private_defines.h>

ConfigIdList::ConfigIdList() : AntRequest(CONFIG_ID_LIST) {

}

ConfigIdList::ConfigIdList(uint8_t channel, uint8_t size, uint8_t type) : AntRequest(CONFIG_ID_LIST) {
    setChannel(channel);
    setListSize(size);
    setExclusion(type);
}

void ConfigIdList::setChannel(uint8_t channel) {
    _channel = channel;
}

void ConfigIdList::setListSize(uint8_t size) {
    _size = size <= CONFIG_ID_LIST_LIST_MAX_SIZE ? size : CONFIG_ID_LIST_LIST_MAX_SIZE;
}

void ConfigIdList::setExclusion(uint8_t type) {
    _type = type;
}

uint8_t ConfigIdList::getChannel() {
    return _channel;
}

uint8_t ConfigIdList::getListSize() {
    return _size;
}

uint8_t ConfigIdList::getListType() {
    return _type;
}

uint8_t ConfigIdList::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _size;
    } else {
        return _type;
    }
}

uint8_t ConfigIdList::getDataLength() {
    return CONFIG_ID_LIST_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ConfigIdList::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
