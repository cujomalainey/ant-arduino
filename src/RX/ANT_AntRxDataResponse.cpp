#include <RX/ANT_AntRxDataResponse.h>

#include <ANT_private_defines.h>

AntRxDataResponse::AntRxDataResponse() : AntResponse() {

}

uint8_t AntRxDataResponse::getData(uint8_t index) {
    return getFrameData()[index];
}

uint8_t* AntRxDataResponse::getData() {
    return getFrameData();
}

// cppcheck-suppress unusedFunction
uint8_t AntRxDataResponse::getDataOffset() {
    return ANT_MSG_FRONT_OVERHEAD;
}

// cppcheck-suppress unusedFunction
uint16_t AntRxDataResponse::getDeviceNumber() {
    if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
        return AntRxDataResponse::getData(EXTENDEDDATA_DEVICENUMBER_LSB_BYTE) | (AntRxDataResponse::getData(EXTENDEDDATA_DEVICENUMBER_MSB_BYTE) << EXTENDEDDATA_DEVICENUMBER_MSB_SHIFT);
    } else {
        return 0;
    }
}

// cppcheck-suppress unusedFunction
uint8_t AntRxDataResponse::getDeviceType() {
    if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
        return AntRxDataResponse::getData(EXTENDEDDATA_DEVICETYPE_BYTE);
    } else {
        return 0;
    }
}

// cppcheck-suppress unusedFunction
uint8_t AntRxDataResponse::getTransmissionType() {
    if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
        return AntRxDataResponse::getData(EXTENDEDDATA_TRANSMISSIONTYPE_BYTE);
    } else {
        return 0;
    }
}

// cppcheck-suppress unusedFunction
uint8_t AntRxDataResponse::getMeasurementType() {
    if (getFlagByte() & LIB_CONFIG_RSSI) {
        uint8_t offset = 0;
        if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
            offset += EXTENDEDDATA_CHANNELID_SIZE;
        }
        return AntRxDataResponse::getData(EXTENDEDDATA_MEASUREMENTTYPE_BYTE + offset);
    } else {
        return 0;
    }
}

// cppcheck-suppress unusedFunction
int8_t AntRxDataResponse::getRSSIValue() {
    if (getFlagByte() & LIB_CONFIG_RSSI) {
        uint8_t offset = 0;
        if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
            offset += EXTENDEDDATA_CHANNELID_SIZE;
        }
        return AntRxDataResponse::getData(EXTENDEDDATA_RSSIVALUE_BYTE + offset);
    } else {
        return 0;
    }
}

// cppcheck-suppress unusedFunction
int8_t AntRxDataResponse::getThresholdConfigurationValue() {
    if (getFlagByte() & LIB_CONFIG_RSSI) {
        uint8_t offset = 0;
        if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
            offset += EXTENDEDDATA_CHANNELID_SIZE;
        }
        return AntRxDataResponse::getData(EXTENDEDDATA_THRESHOLDCONFIGURATIONVALUE_BYTE + offset);
    } else {
        return 0;
    }
}

// cppcheck-suppress unusedFunction
uint16_t AntRxDataResponse::getRxTimestamp() {
    if (getFlagByte() & LIB_CONFIG_RX_TIMESTAMP) {
        uint8_t offset = 0;
        if (getFlagByte() & LIB_CONFIG_CHANNEL_ID) {
            offset += EXTENDEDDATA_CHANNELID_SIZE;
        }
        if (getFlagByte() & LIB_CONFIG_RSSI) {
            offset += EXTENDEDDATA_RSSIOUTPUT_SIZE;
        }
        return AntRxDataResponse::getData(EXTENDEDDATA_RXTIMESTAMP_LSB_BYTE + offset) | (AntRxDataResponse::getData(EXTENDEDDATA_DEVICENUMBER_MSB_BYTE + offset) << EXTENDEDDATA_RXTIMESTAMP_MSB_SHIFT);
    } else {
        return 0;
    }
}
