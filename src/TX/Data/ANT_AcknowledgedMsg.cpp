#include <TX/Data/ANT_AcknowledgedMsg.h>

#include <ANT_private_defines.h>


/* Extended message format not currently supported */
AcknowledgedMsg::AcknowledgedMsg() : AntTxDataRequest(ACKNOWLEDGED_DATA) {
    setDataLength(MESSAGE_SIZE);
}

AcknowledgedMsg::AcknowledgedMsg(uint8_t channel) : AntTxDataRequest(ACKNOWLEDGED_DATA) {
    setDataLength(MESSAGE_SIZE);
    setChannel(channel);
}

void AcknowledgedMsg::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t AcknowledgedMsg::getChannel() {
    return _channel;
}

uint8_t AcknowledgedMsg::getDataLength() {
    return ACKNOWLEDGED_DATA_LENGTH;
}

uint8_t AcknowledgedMsg::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    }
    else {
        return getDataBuffer()[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t AcknowledgedMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE