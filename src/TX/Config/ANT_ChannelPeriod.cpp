#include <TX/Config/ANT_ChannelPeriod.h>

#include <ANT_private_defines.h>


ChannelPeriod::ChannelPeriod() : AntRequest(CHANNEL_PERIOD) {

}

ChannelPeriod::ChannelPeriod(uint8_t channel, uint16_t period) : AntRequest(CHANNEL_PERIOD) {
    setChannel(channel);
    setPeriod(period);
}

void ChannelPeriod::setChannel(uint8_t channel) {
    _channel = channel;
}

void ChannelPeriod::setPeriod(uint16_t period) {
    _period = period;
}

uint8_t ChannelPeriod::getChannel() {
    return _channel;
}

uint16_t ChannelPeriod::getPeriod() {
    return _period;
}

uint8_t ChannelPeriod::getDataLength() {
    return CHANNEL_PERIOD_LENGTH;
}

uint8_t ChannelPeriod::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return (uint8_t)_period;
    } else {
        return (uint8_t)(_period >> BITS_IN_BYTE);
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ChannelPeriod::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE