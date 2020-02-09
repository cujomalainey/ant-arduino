#include <TX/Config/ANT_SetChannelTransmitPower.h>

#include <ANT_private_defines.h>

SetChannelTransmitPower::SetChannelTransmitPower() : AntRequest(SET_CHANNEL_TRANSMIT_POWER) {

}

SetChannelTransmitPower::SetChannelTransmitPower(uint8_t channel) : AntRequest(SET_CHANNEL_TRANSMIT_POWER) {
    setChannel(channel);
}

SetChannelTransmitPower::SetChannelTransmitPower(uint8_t channel, uint8_t transmitPower) : AntRequest(SET_CHANNEL_TRANSMIT_POWER) {
    setChannel(channel);
    setTransmitPower(transmitPower);
}

void SetChannelTransmitPower::setChannel(uint8_t channel) {
    _channel = channel;
}

void SetChannelTransmitPower::setTransmitPower(uint8_t transmitPower) {
    _transmitPower = transmitPower;
}

uint8_t SetChannelTransmitPower::getChannel() {
    return _channel;
}

uint16_t SetChannelTransmitPower::getTransmitPower() {
    return _transmitPower;
}

uint8_t SetChannelTransmitPower::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _transmitPower;
    }
}

uint8_t SetChannelTransmitPower::getDataLength() {
    return SET_CHANNEL_TRANSMIT_POWER_LENGTH;
}


#ifdef NATIVE_API_AVAILABLE

uint32_t SetChannelTransmitPower::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
