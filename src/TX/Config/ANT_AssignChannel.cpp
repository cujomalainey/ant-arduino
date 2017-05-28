#include <TX/Config/ANT_AssignChannel.h>

#include <ANT_defines.h>

#define ASSIGN_CHANNEL_LENGTH  0x03

AssignChannel::AssignChannel() : AntRequest(ASSIGN_CHANNEL) {

}

void AssignChannel::setChannel(uint8_t channel) {
    _channel = channel;
}

void AssignChannel::setChannelType(uint8_t channelType) {
    _channelType = channelType;
}

void AssignChannel::setChannelNetwork(uint8_t network) {
    _network = network;
}

uint8_t AssignChannel::getChannel() {
    return _channel;
}

uint8_t AssignChannel::getChannelType() {
    return _channelType;
}

uint8_t AssignChannel::getChannelNetwork() {
    return _network;
}

uint8_t AssignChannel::getDataLength() {
    return ASSIGN_CHANNEL_LENGTH;
}

uint8_t AssignChannel::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _channelType;
    } else {
        return _network;
    }
}