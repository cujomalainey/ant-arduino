#include <RX/ANT_AntRxDataResponse.h>

#include <ANT_private_defines.h>

AntRxDataResponse::AntRxDataResponse() : AntResponse() {

}

uint8_t AntRxDataResponse::getData(int index) {
    return getFrameData()[index];
}

uint8_t* AntRxDataResponse::getData() {
    return getFrameData();
}

uint8_t AntRxDataResponse::getDataOffset() {
    return ANT_MSG_FRONT_OVERHEAD;
}

uint8_t AntRxDataResponse::getFlagByte() {
    // TODO magic number
    return getData(10);
}

uint16_t AntRxDataResponse::getDeviceNumber() {
    // TODO
    return 0;
}

uint8_t AntRxDataResponse::getDeviceType() {
    // TODO
    return 0;
}

uint8_t AntRxDataResponse::getTransmissionType() {
    // TODO
    return 0;
}

uint8_t AntRxDataResponse::getMeasurementType() {
    // TODO
    return 0;
}

int8_t AntRxDataResponse::getRSSIValue() {
    // TODO
    return 0;
}

int8_t AntRxDataResponse::getThresholdConfigurationValue() {
    // TODO
    return 0;
}

uint16_t AntRxDataResponse::getRxTimestamp() {
    // TODO
    return 0;
}

void AntRxDataResponse::setExtendedDataAvailibility(bool extendedAvailable) {
    // TODO
}
