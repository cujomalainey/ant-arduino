#include <TX/Data/ANT_AcknowledgedMsg.h>

#include <ANT_defines.h>

#define ACKNOWLEDGE_DATA_LENGTH 0x09

/* Extended message format not currently supported */
AcknowledgedMsg::AcknowledgedMsg() : AntRequest(ACKNOWLEDGED_DATA) {

}

void AcknowledgedMsg::setChannel(uint8_t channel) {
    _channel = channel;
}

uint8_t AcknowledgedMsg::getChannel() {
    return _channel;
}

uint8_t AcknowledgedMsg::getDataLength() {
    return ACKNOWLEDGE_DATA_LENGTH;
}

uint8_t AcknowledgedMsg::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    }
    else {
        return _data[pos - 1];
    }
}

#ifdef NATIVE_API_AVAILABLE

uint8_t AcknowledgedMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE