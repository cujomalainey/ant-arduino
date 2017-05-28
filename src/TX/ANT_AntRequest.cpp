#include <TX/ANT_AntRequest.h>

AntRequest::AntRequest(uint8_t msgId) {
    _msgId = msgId;
}

uint8_t AntRequest::getMsgId() {
    return _msgId;
}

void AntRequest::setMsgId(uint8_t msgId) {
    _msgId = msgId;
}