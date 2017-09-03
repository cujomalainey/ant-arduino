#include <TX/Config/ANT_ChannelSearchSharing.h>

#include <ANT_private_defines.h>

ChannelSearchSharing::ChannelSearchSharing() : AntRequest(CHANNEL_SEARCH_SHARING) {

}

ChannelSearchSharing::ChannelSearchSharing(uint8_t channel, uint8_t cycles) : AntRequest(CHANNEL_SEARCH_SHARING) {
    setChannel(channel);
    setSearchcycles(cycles);
}

void ChannelSearchSharing::setChannel(uint8_t channel) {
    _channel = channel;
}

void ChannelSearchSharing::setSearchcycles(uint8_t cycles) {
    _cycles = cycles;
}

uint8_t ChannelSearchSharing::getChannel() {
    return _channel;
}

uint8_t ChannelSearchSharing::getSearchCycles() {
    return _cycles;
}

uint8_t ChannelSearchSharing::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t ChannelSearchSharing::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ChannelSearchSharing::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE