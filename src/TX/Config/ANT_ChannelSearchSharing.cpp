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

// cppcheck-suppress unusedFunction
uint8_t ChannelSearchSharing::getSearchCycles() {
    return _cycles;
}

uint8_t ChannelSearchSharing::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _cycles;
    }
}

uint8_t ChannelSearchSharing::getDataLength() {
    return CHANNEL_SEARCH_SHARING_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t ChannelSearchSharing::execute() {
    return sd_ant_active_search_sharing_cycles_set(_channel, _cycles);
}

#endif // NATIVE_API_AVAILABLE
