#include <TX/Control/ANT_RequestMessage.h>

#include <ANT_defines.h>

#define REQUEST_MESSAGE_LENGTH 0x02

/* Extended message format not currently supported */
RequestMessage::RequestMessage() : AntRequest(REQUEST_MESSAGE) {
    _subId = 0;
}

void RequestMessage::setRequestedMessage(uint8_t msgId) {
    _msgId = msgId;
}

uint8_t RequestMessage::getRequestedMessage() {
    return _msgId;
}

void RequestMessage::setSubId(uint8_t subId) {
    _subId = subId;
}

uint8_t RequestMessage::getSubId() {
    return _subId;
}

uint8_t RequestMessage::getData(uint8_t pos) {
    if (pos == 0) {
        return _subId;
    }
    else if (pos == 1) {
        return _msgId;
    }
    else {
        return INVALID_REQUEST;
    }
}

uint8_t RequestMessage::getDataLength() {
    return REQUEST_MESSAGE_LENGTH;
}