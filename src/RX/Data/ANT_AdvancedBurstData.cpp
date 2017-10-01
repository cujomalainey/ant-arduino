#include <RX/Data/ANT_AdvancedBurstData.h>

#include <ANT_private_defines.h>

AdvancedBurstData::AdvancedBurstData() : AntRxDataResponse() {

}

uint8_t AdvancedBurstData::getChannelNumber() {
    return AntRxDataResponse::getData(0) & ADVANCED_BURST_DATA_CHANNEL_MASK;
}

uint8_t AdvancedBurstData::getSequenceNumber() {
    return (AntRxDataResponse::getData(0) & ~ADVANCED_BURST_DATA_CHANNEL_MASK) >> ADVANCED_BURST_DATA_SEQUENCENUMBER_SHIFT;
}


uint8_t AdvancedBurstData::getData(uint8_t index) {
    // skip channel byte
    return AntRxDataResponse::getData(index + 1);
}

// uint8_t* AcknowledgedData::getData() {
//     // TODO UNVERIFIED
//     // skip channel byte
//     return AntRxDataResponse::getData() + 1;
// }

uint8_t AdvancedBurstData::getDataLength() {
    // TODO this is actually variable
    return ADVANCED_BURST_DATA_LENGTH;
}