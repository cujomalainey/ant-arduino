#include <TX/Data/ANT_BroadcastDataMsg.h>

#include <ANT_private_defines.h>


/* Extended message format not currently supported */
BroadcastDataMsg::BroadcastDataMsg() : AntTxDataRequest(BROADCAST_DATA) {
    setDataLength(MESSAGE_SIZE);
}

BroadcastDataMsg::BroadcastDataMsg(uint8_t channel) : AntTxDataRequest(BROADCAST_DATA) {
    setDataLength(MESSAGE_SIZE);
    setChannel(channel);
}

void BroadcastDataMsg::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t BroadcastDataMsg::getChannel() {
    return _channel;
}

uint8_t BroadcastDataMsg::getDataLength() {
    return BROADCAST_DATA_LENGTH;
}

uint8_t BroadcastDataMsg::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    }
    else {
        return getDataBuffer()[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint32_t BroadcastDataMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
