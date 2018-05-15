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
    if (enabled) {
        // TODO magic number
        return getData(10);
    } else {
        return 0x00;
    }
}

uint16_t AntRxDataResponse::getDeviceNumber() {
}

uint8_t AntRxDataResponse::getDeviceType() {
}

uint8_t AntRxDataResponse::getTransmissionType() {
}

uint8_t AntRxDataResponse::getMeasurementType() {
}

int8_t AntRxDataResponse::getRSSIValue() {
}

int8_t AntRxDataResponse::getThresholdConfigurationValue() {
}

uint16_t AntRxDataResponse::getRxTimestamp() {
}

void AntRxDataResponse::setExtendedDataAvailibility(bool extendedAvailable) {
}
