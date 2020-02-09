#include <TX/Control/ANT_OpenChannel.h>

#include <ANT_private_defines.h>


OpenChannel::OpenChannel() : AntRequest(OPEN_CHANNEL) {

}

OpenChannel::OpenChannel(uint8_t channel) : AntRequest(OPEN_CHANNEL) {
    setChannel(channel);
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

#ifdef NATIVE_API_AVAILABLE

uint32_t OpenChannel::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
