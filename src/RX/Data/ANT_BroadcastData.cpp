#include <RX/Data/ANT_BroadcastData.h>
#include <RX/ANT_AntRxDataResponse.h>
#include <ANT_private_defines.h>

BroadcastData::BroadcastData() : AntRxDataResponse() {

}

uint8_t BroadcastData::getChannelNumber() {
    return AntRxDataResponse::getData(0);
}

uint8_t BroadcastData::getData(uint8_t index) {
    // skip channel byte
    return AntRxDataResponse::getData(index + 1);
}

uint8_t* BroadcastData::getData() {
    // skip channel byte
    return AntRxDataResponse::getData() + 1;
}

uint8_t BroadcastData::getExtendedDataLength() {
    // not inplemented
    return INVALID_REQUEST;
}

uint8_t BroadcastData::getExtendedData(uint8_t index) {
    // not inplemented
    return INVALID_REQUEST;
}

uint8_t BroadcastData::getDataLength() {
    return BROADCAST_DATA_LENGTH;
}