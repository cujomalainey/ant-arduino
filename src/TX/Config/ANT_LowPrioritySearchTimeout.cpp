#include <TX/Config/ANT_LowPrioritySearchTimeout.h>

#include <ANT_private_defines.h>

LowPrioritySearchTimeout::LowPrioritySearchTimeout() : AntRequest(LOW_PRIORITY_SEARCH_TIMEOUT) {

}

LowPrioritySearchTimeout::LowPrioritySearchTimeout(uint8_t channel)  : AntRequest(LOW_PRIORITY_SEARCH_TIMEOUT){
    setChannel(channel);
}

LowPrioritySearchTimeout::LowPrioritySearchTimeout(uint8_t channel, uint8_t timeout)  : AntRequest(LOW_PRIORITY_SEARCH_TIMEOUT){
    setChannel(channel);
    setTimeout(timeout);
}

void LowPrioritySearchTimeout::setChannel(uint8_t channel) {
    _channel = channel;
}

void LowPrioritySearchTimeout::setTimeout(uint8_t timeout) {
    _timeout = timeout;
}

uint8_t LowPrioritySearchTimeout::getChannel() {
    return _channel;
}

uint8_t LowPrioritySearchTimeout::getTimeout() {
    return _timeout;
}

uint8_t LowPrioritySearchTimeout::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _timeout;
    }
}

uint8_t LowPrioritySearchTimeout::getDataLength() {
    return LOW_PRIORITY_SEARCH_TIMEOUT_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t LowPrioritySearchTimeout::execute() {
    return sd_ant_channel_low_priority_rx_search_timeout_set(_channel, _timeout);
}

#endif // NATIVE_API_AVAILABLE
