#include <RX/Data/ANT_AdvancedBurstData.h>

#include <ANT_private_defines.h>

AdvancedBurstData::AdvancedBurstData() : AntRxDataResponse() {

}

uint8_t AdvancedBurstData::getChannelNumber() {
    // TODO UNVERIFIED
    return AntRxDataResponse::getData(0);
}

uint8_t AdvancedBurstData::getData(uint8_t index) {
    // TODO UNVERIFIED
    // skip channel byte
    return AntRxDataResponse::getData(index + 1);
}

// uint8_t* AcknowledgedData::getData() {
//     // TODO UNVERIFIED
//     // skip channel byte
//     return AntRxDataResponse::getData() + 1;
// }

// uint8_t AdvancedBurstData::getExtendedDataLength() {
//     // TODO not inplemented
//     return INVALID_REQUEST;
// }

// uint8_t AdvancedBurstData::getExtendedData(uint8_t index) {
//     // TODO not inplemented
//     return INVALID_REQUEST;
// }

uint8_t AdvancedBurstData::getDataLength() {
    // TODO this is actually variable
    return ADVANCED_BURST_DATA_LENGTH;
}