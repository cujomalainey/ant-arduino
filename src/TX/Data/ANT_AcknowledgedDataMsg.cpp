#include <TX/Data/ANT_AcknowledgedDataMsg.h>

#include <ANT_private_defines.h>


/* Extended message format not currently supported */
AcknowledgedDataMsg::AcknowledgedDataMsg() : AntTxDataRequest(ACKNOWLEDGED_DATA) {
    setDataLength(MESSAGE_SIZE);
}

AcknowledgedDataMsg::AcknowledgedDataMsg(uint8_t channel) : AntTxDataRequest(ACKNOWLEDGED_DATA) {
    setDataLength(MESSAGE_SIZE);
    setChannel(channel);
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

uint32_t AcknowledgedDataMsg::execute() {
    return sd_ant_acknowledge_message_tx(_channel, 8, getDataBuffer());
}

#endif // NATIVE_API_AVAILABLE
