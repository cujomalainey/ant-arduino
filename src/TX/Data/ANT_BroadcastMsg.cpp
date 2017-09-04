#include <TX/Data/ANT_BroadcastMsg.h>

#include <ANT_private_defines.h>


/* Extended message format not currently supported */
BroadcastMsg::BroadcastMsg() : AntTxDataRequest(BROADCAST_DATA) {
    setDataLength(MESSAGE_SIZE);
}

BroadcastMsg::BroadcastMsg(uint8_t channel) : AntTxDataRequest(BROADCAST_DATA) {
    setDataLength(MESSAGE_SIZE);
    setChannel(channel);
}

void BroadcastMsg::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t BroadcastMsg::getChannel() {
    return _channel;
}

uint8_t BroadcastMsg::getDataLength() {
    return BROADCAST_DATA_LENGTH;
}

uint8_t BroadcastMsg::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    }
    else {
        return getDataBuffer()[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t BroadcastMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE