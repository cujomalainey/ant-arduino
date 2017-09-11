#include <TX/Control/ANT_CloseChannel.h>

#include <ANT_private_defines.h>


CloseChannel::CloseChannel() : AntRequest(CLOSE_CHANNEL) {

}

CloseChannel::CloseChannel(uint8_t channel) : AntRequest(CLOSE_CHANNEL) {
    setChannel(channel);
}

void CloseChannel::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t CloseChannel::getChannel() {
    return _channel;
}

uint8_t CloseChannel::getDataLength() {
    return CLOSE_CHANNEL_LENGTH;
}

uint8_t CloseChannel::getData(uint8_t pos) {
    return _channel;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t CloseChannel::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE