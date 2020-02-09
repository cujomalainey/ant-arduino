#include <TX/Config/ANT_UnAssignChannel.h>

#include <ANT_private_defines.h>


UnAssignChannel::UnAssignChannel() : AntRequest(UNASSIGN_CHANNEL) {

}

UnAssignChannel::UnAssignChannel(uint8_t channel) : AntRequest(UNASSIGN_CHANNEL) {
    setChannel(channel);
}

void UnAssignChannel::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t UnAssignChannel::getChannel() {
    return _channel;
}

uint8_t UnAssignChannel::getDataLength() {
    return UNASSIGN_CHANNEL_LENGTH;
}

uint8_t UnAssignChannel::getData(uint8_t pos) {
    return _channel;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t UnAssignChannel::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
