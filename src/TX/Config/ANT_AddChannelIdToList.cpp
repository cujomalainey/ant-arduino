#include <TX/Config/ANT_AddChannelIdToList.h>

#include <ANT_private_defines.h>


AddChannelIdToList::AddChannelIdToList() : AntRequest(ADD_CHANNEL_ID_TO_LIST) {

}

AddChannelIdToList::AddChannelIdToList(uint8_t channel, uint16_t deviceNumber, uint8_t deviceType,  uint8_t transmissionType, uint8_t listIndex) : AntRequest(ADD_CHANNEL_ID_TO_LIST) {
    setChannel(channel);
    setDeviceNumber(deviceNumber);
    setDeviceType(deviceType);
    setTransmissionType(transmissionType);
    setListIndex(listIndex);
}

void AddChannelIdToList::setChannel(uint8_t channel) {
    _channel = channel;
}

void AddChannelIdToList::setDeviceNumber(uint16_t deviceNumber) {
    _deviceNumber = deviceNumber;
}

void AddChannelIdToList::setDeviceType(uint8_t deviceType) {
    _deviceType = deviceType;
}

void AddChannelIdToList::setTransmissionType(uint8_t transmissionType) {
    _transmissionType = transmissionType;
}

void AddChannelIdToList::setListIndex(uint8_t listIndex) {
    _listIndex = listIndex;
}

uint8_t AddChannelIdToList::getChannel() {
    return _channel;
}

uint16_t AddChannelIdToList::getDeviceNumber() {
    return _deviceNumber;
}

uint8_t AddChannelIdToList::getDeviceType() {
    return _deviceType;
}

uint8_t AddChannelIdToList::getTransmissionType() {
    return _transmissionType;
}

uint8_t AddChannelIdToList::getListIndex() {
    return _listIndex;
}

uint8_t AddChannelIdToList::getData(uint8_t pos) {
    // TODO not implemented
    return 0;
}

uint8_t AddChannelIdToList::getDataLength() {
    // TODO not implemented
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t AddChannelIdToList::execute() {
    // TODO not implemented
    return 0;
}

#endif // NATIVE_API_AVAILABLE