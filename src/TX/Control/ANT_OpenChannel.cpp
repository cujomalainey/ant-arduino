#include <TX/Control/ANT_OpenChannel.h>

#include <ANT_defines.h>

#define OPEN_CHANNEL_LENGTH  0x01

OpenChannel::OpenChannel() : AntRequest(OPEN_CHANNEL) {

}

OpenChannel::OpenChannel(uint8_t channel) : AntRequest(OPEN_CHANNEL) {
    _channel = channel;
}

void OpenChannel::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t OpenChannel::getChannel() {
    return _channel;
}

uint8_t OpenChannel::getDataLength() {
    return OPEN_CHANNEL_LENGTH;
}

uint8_t OpenChannel::getData(uint8_t pos) {
    return _channel;
}