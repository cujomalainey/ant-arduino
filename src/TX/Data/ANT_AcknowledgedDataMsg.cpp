#include <TX/Data/ANT_AcknowledgedDataMsg.h>

#include <ANT_private_defines.h>


/* Extended message format not currently supported */
AcknowledgedDataMsg::AcknowledgedDataMsg() : AntTxDataRequest(ACKNOWLEDGED_DATA) {
    setDataLength(MESSAGE_SIZE);
}

AcknowledgedDataMsg::AcknowledgedDataMsg(uint8_t channel) : AntTxDataRequest(ACKNOWLEDGED_DATA) {
    setDataLength(MESSAGE_SIZE);
    setChannelNumber(channel);
}

void AcknowledgedDataMsg::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t AcknowledgedDataMsg::getChannel() {
    return _channel;
}

uint8_t AcknowledgedDataMsg::getDataLength() {
    return ACKNOWLEDGED_DATA_LENGTH;
}

uint8_t AcknowledgedDataMsg::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    }
    else {
        return getDataBuffer()[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t AcknowledgedDataMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
