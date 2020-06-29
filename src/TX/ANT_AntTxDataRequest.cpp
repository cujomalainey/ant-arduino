#include <TX/ANT_AntTxDataRequest.h>

AntTxDataRequest::AntTxDataRequest(uint8_t msgId) : AntRequest(msgId) {

}

void AntTxDataRequest::setDataBuffer(uint8_t* dataPtr) {
    _data = dataPtr;
}

uint8_t* AntTxDataRequest::getDataBuffer() {
    return _data;
}

void AntTxDataRequest::setDataLength(uint8_t length) {
    _dataLength = length;
}

uint8_t AntTxDataRequest::getDataBufferLength() {
    return _dataLength;
}
