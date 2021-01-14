#include <TX/Control/ANT_RequestMessage.h>

#include <ANT_private_defines.h>


/* Extended message format not currently supported */
RequestMessage::RequestMessage() : AntRequest(REQUEST_MESSAGE) {}

RequestMessage::RequestMessage(uint8_t msgId) : AntRequest(REQUEST_MESSAGE) {
    setRequestedMessage(msgId);
}

RequestMessage::RequestMessage(uint8_t msgId, uint8_t subId) : AntRequest(REQUEST_MESSAGE) {
    setRequestedMessage(msgId);
    setSubId(subId);
}

void RequestMessage::setRequestedMessage(uint8_t msgId) {
    _msgId = msgId;
}

// cppcheck-suppress unusedFunction
uint8_t RequestMessage::getRequestedMessage() {
    return _msgId;
}

void RequestMessage::setSubId(uint8_t subId) {
    _subId = subId;
}

// cppcheck-suppress unusedFunction
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

#ifdef NATIVE_API_AVAILABLE

uint32_t RequestMessage::execute() {
    return 0;
}

#endif // NATIVE_API_AVAILABLE
