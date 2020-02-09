#include <TX/Config/ANT_ChannelRfFrequency.h>

#include <ANT_private_defines.h>


ChannelRfFrequency::ChannelRfFrequency() : AntRequest(CHANNEL_RF_FREQUENCY) {

}

ChannelRfFrequency::ChannelRfFrequency(uint8_t channel, uint8_t frequency) : AntRequest(CHANNEL_RF_FREQUENCY) {
    setChannel(channel);
    setRfFrequency(frequency);
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

#ifdef NATIVE_API_AVAILABLE

uint32_t ChannelRfFrequency::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
