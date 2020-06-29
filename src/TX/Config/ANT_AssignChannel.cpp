#include <TX/Config/ANT_AssignChannel.h>

#include <ANT_private_defines.h>


AssignChannel::AssignChannel() : AntRequest(ASSIGN_CHANNEL) {

}

AssignChannel::AssignChannel(uint8_t channel, uint8_t channelType, uint8_t network) : AntRequest(ASSIGN_CHANNEL) {
    setChannel(channel);
    setChannelType(channelType);
    setChannelNetwork(network);
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

void AssignChannel::setExtendedAssignment(uint8_t extended) {
    _extended = extended;
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

uint8_t AssignChannel::getExtendedAssignment() {
    return _extended;
}

uint8_t AssignChannel::getDataLength() {
    return _extended == 0 ? ASSIGN_CHANNEL_LENGTH : ASSIGN_CHANNEL_LENGTH + 1;
}

uint8_t AssignChannel::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _channelType;
    } else if (pos == 2) {
        return _network;
    } else {
        return _extended;
    }
}

#ifdef NATIVE_API_AVAILABLE

uint32_t AssignChannel::execute() {
    return sd_ant_channel_assign(_channel, _channelType, _network, _extended);
}

#endif // NATIVE_API_AVAILABLE
