#include <TX/Config/ANT_SearchTimeout.h>

#include <ANT_private_defines.h>

SearchTimeout::SearchTimeout() : AntRequest(SEARCH_TIMEOUT) {

}

SearchTimeout::SearchTimeout(uint8_t channel, uint8_t timeout) : AntRequest(SEARCH_TIMEOUT) {
    setChannel(channel);
    setTimeout(timeout);
}

void SearchTimeout::setChannel(uint8_t channel) {
    _channel = channel;
}

void SearchTimeout::setTimeout(uint8_t timeout) {
    _timeout = timeout;
}

uint8_t SearchTimeout::getChannel() {
    return _channel;
}

uint8_t SearchTimeout::getTimeout() {
    return _timeout;
}

uint8_t SearchTimeout::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t SearchTimeout::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t SearchTimeout::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE