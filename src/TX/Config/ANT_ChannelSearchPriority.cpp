#include <TX/Config/ANT_ChannelSearchPriority.h>

#include <ANT_private_defines.h>

ChannelSearchPriority::ChannelSearchPriority() : AntRequest(CHANNEL_SEARCH_PRIORITY) {

}

ChannelSearchPriority::ChannelSearchPriority(uint8_t channel, uint8_t priority) : AntRequest(CHANNEL_SEARCH_PRIORITY) {
    setChannel(channel);
    setPriority(priority);
}

void ChannelSearchPriority::setChannel(uint8_t channel) {
    _channel = channel;
}

void ChannelSearchPriority::setPriority(uint8_t priority) {
    _priority = priority;
}

uint8_t ChannelSearchPriority::getChannel() {
    return _channel;
}

// cppcheck-suppress unusedFunction
uint8_t ChannelSearchPriority::getPriority() {
    return _priority;
}

uint8_t ChannelSearchPriority::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _priority;
    }
}

uint8_t ChannelSearchPriority::getDataLength() {
    return CHANNEL_SEARCH_PRIORITY_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t ChannelSearchPriority::execute() {
    return sd_ant_search_channel_priority_set(_channel, _priority);
}

#endif // NATIVE_API_AVAILABLE
