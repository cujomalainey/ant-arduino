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
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _waveform & 0xFF;
    } else {
        return _waveform >> 8;
    }
}

uint8_t SearchWaveform::getDataLength() {
    return SEARCH_WAVEFORM_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t SearchWaveform::execute() {
    // TODO
    return 0;
}

#endif
