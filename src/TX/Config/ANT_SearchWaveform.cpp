#include <TX/Config/ANT_SearchWaveform.h>

#include <ANT_private_defines.h>

SearchWaveform::SearchWaveform() : AntRequest(SEARCH_WAVEFORM) {

}

SearchWaveform::SearchWaveform(uint8_t channel, uint16_t waveform) : AntRequest(SEARCH_WAVEFORM) {
    setChannel(channel);
    setWaveform(waveform);
}

void SearchWaveform::setChannel(uint8_t channel) {
    _channel = channel;
}

void SearchWaveform::setWaveform(uint16_t waveform) {
    _waveform = waveform;
}

uint8_t SearchWaveform::getChannel() {
    return _channel;
}

uint16_t SearchWaveform::getWaveform() {
    return _waveform;
}

uint8_t SearchWaveform::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t SearchWaveform::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t SearchWaveform::execute() {
    // TODO
    return 0;
}

#endif