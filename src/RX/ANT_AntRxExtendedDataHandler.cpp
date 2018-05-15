#include <RX/ANT_AntRxExtendedDataHandler.h>

AntRxExtendedDataHandler::AntRxExtendedDataHandler() : AntRxDataResponse() {
}

uint8_t AntRxExtendedDataHandler::getFlagByte() {
    if (enabled) {
        // TODO magic number
        return getData(10);
    } else {
        return 0x00;
    }
}

uint16_t AntRxExtendedDataHandler::getDeviceNumber() {
}

uint8_t AntRxExtendedDataHandler::getDeviceType() {
}

uint8_t AntRxExtendedDataHandler::getTransmissionType() {
}

uint8_t AntRxExtendedDataHandler::getMeasurementType() {
}

int8_t AntRxExtendedDataHandler::getRSSIValue() {
}

int8_t AntRxExtendedDataHandler::getThresholdConfigurationValue() {
}

uint16_t AntRxExtendedDataHandler::getRxTimestamp() {
}

void AntRxExtendedDataHandler::setExtendedDataAvailibility(bool extendedAvailable) {
}
