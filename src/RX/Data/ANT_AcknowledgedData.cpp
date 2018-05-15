#include <RX/Data/ANT_AcknowledgedData.h>

#include <ANT_private_defines.h>

AcknowledgedData::AcknowledgedData() : AntRxDataResponse() {

}

uint8_t AcknowledgedData::getChannelNumber() {
    return AntRxDataResponse::getData(0);
}

uint8_t AcknowledgedData::getData(uint8_t index) {
    // skip channel byte
    return AntRxDataResponse::getData(index + 1);
}

uint8_t* AcknowledgedData::getData() {
    // skip channel byte
    return AntRxDataResponse::getData() + 1;
}

uint8_t AcknowledgedData::getDataLength() {
    return ACKNOWLEDGED_DATA_LENGTH;
}
