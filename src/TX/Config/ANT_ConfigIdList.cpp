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
    // TODO size [0-4] (needs verification)
    _size = size;
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
    // TODO
    return 0;
}

uint8_t ConfigIdList::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ConfigIdList::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE