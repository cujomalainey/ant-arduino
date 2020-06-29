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
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _deviceNumber & 0xFF;
    } else if (pos == 2) {
        return _deviceNumber >> 8;
    } else if (pos == 3) {
        return _deviceType & 0x7F;
    } else if (pos == 4) {
        return _transmissionType;
    } else {
        return _listIndex;
    }
}

uint8_t AddChannelIdToList::getDataLength() {
    return ADD_CHANNEL_ID_TO_LIST_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t AddChannelIdToList::execute() {
    uint8_t buf[4];
    buf[0] = _deviceNumber;
    buf[1] = _deviceNumber << BITS_IN_BYTE;
    buf[2] = _deviceType;
    buf[3] = _transmissionType;
    return sd_ant_id_list_add(_channel, buf, _listIndex);
}

#endif // NATIVE_API_AVAILABLE
