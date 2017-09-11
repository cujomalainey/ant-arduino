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