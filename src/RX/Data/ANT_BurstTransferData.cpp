#include <RX/Data/ANT_BurstTransferData.h>

#include <ANT_private_defines.h>

BurstTransferData::BurstTransferData() : AntRxDataResponse() {

}

uint8_t BurstTransferData::getChannelNumber() {
    return AntRxDataResponse::getData(0);
}

uint8_t BurstTransferData::getData(uint8_t index) {
    // skip channel byte
    return AntRxDataResponse::getData(index + 1);
}

uint8_t* BurstTransferData::getData() {
    // skip channel byte
    return AntRxDataResponse::getData() + 1;
}

// uint8_t BurstTransferData::getExtendedDataLength() {
//     // TODO not inplemented
//     return INVALID_REQUEST;
// }

// uint8_t BurstTransferData::getExtendedData(uint8_t index) {
//     // TODO not inplemented
//     return INVALID_REQUEST;
// }

uint8_t BurstTransferData::getDataLength() {
    return BURST_DATA_TRANSFER_LENGTH;
}