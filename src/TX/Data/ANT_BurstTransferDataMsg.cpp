#include <TX/Data/ANT_BurstTransferDataMsg.h>

#include <ANT_private_defines.h>

BurstTransferDataMsg::BurstTransferDataMsg() : AntTxDataRequest(BURST_TRANSFER_DATA) {

}

BurstTransferDataMsg::BurstTransferDataMsg(uint8_t channel) : AntTxDataRequest(BURST_TRANSFER_DATA) {
    setChannelSequence(channel);
}

void BurstTransferDataMsg::setChannelSequence(uint8_t channel) {
    _channel = channel;
}

uint8_t BurstTransferDataMsg::getChannelSequence() {
    return _channel;
}

uint8_t BurstTransferDataMsg::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t BurstTransferDataMsg::getDataLength() {
    // TODO
    return 0;
}

void BurstTransferDataMsg::setDataLength(uint8_t length) {
    AntTxDataRequest::setDataLength(length);
}

#ifdef NATIVE_API_AVAILABLE

uint8_t BurstTransferDataMsg::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE