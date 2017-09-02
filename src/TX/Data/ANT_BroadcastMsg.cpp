#include <TX/Data/ANT_BroadcastMsg.h>

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define BROADCAST_DATA_LENGTH 0x09

/* Extended message format not currently supported */
BroadcastMsg::BroadcastMsg() : AntRequest(BROADCAST_DATA) {

}

void BroadcastMsg::setData(uint8_t* data) {
    memcpy(_data, data, MESSAGE_SIZE);
}

void BroadcastMsg::getData(uint8_t* data) {
    memcpy(data, _data, MESSAGE_SIZE);
}

void BroadcastMsg::setByte(uint8_t index, uint8_t data) {
    _data[index] = data;
}

uint8_t BroadcastMsg::getByte(uint8_t index) {
    return _data[index];
}

void BroadcastMsg::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t BroadcastMsg::getChannel() {
    return _channel;
}

uint8_t BroadcastMsg::getDataLength() {
    return BROADCAST_DATA_LENGTH;
}

uint8_t BroadcastMsg::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    }
    else {
        return _data[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t BroadcastMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE