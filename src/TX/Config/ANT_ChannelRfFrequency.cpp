#include <TX/Config/ANT_ChannelRfFrequency.h>

#include <ANT_defines.h>

#define CHANNEL_RF_FREQUENCY_LENGTH  0x02

ChannelRfFrequency::ChannelRfFrequency() : AntRequest(CHANNEL_RF_FREQUENCY) {

}

void ChannelRfFrequency::setChannel(uint8_t channel) {
    _channel = channel;
}

void ChannelRfFrequency::setRfFrequency(uint8_t frequency) {
    _frequency = frequency;
}

uint8_t ChannelRfFrequency::getChannel() {
    return _channel;
}

uint8_t ChannelRfFrequency::getRfFrequency() {
    return _frequency;
}

uint8_t ChannelRfFrequency::getDataLength() {
    return CHANNEL_RF_FREQUENCY_LENGTH;
}

uint8_t ChannelRfFrequency::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _frequency;
    }
}