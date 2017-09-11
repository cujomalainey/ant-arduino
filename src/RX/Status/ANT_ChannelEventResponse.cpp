#include <RX/Status/ANT_ChannelEventResponse.h>

ChannelEventResponse::ChannelEventResponse() : AntResponse() {

}

uint8_t ChannelEventResponse::getChannelNumber() {
    return  getFrameData()[0];
}

uint8_t ChannelEventResponse::getMsgId() {
    return getFrameData()[1];
}

uint8_t ChannelEventResponse::getCode() {
    return getFrameData()[2];
}

uint8_t ChannelEventResponse::getExtendedEventParameters() {
    if (getLength() > 3){
        return getFrameData()[3];
    }
    else {
        return INVALID_REQUEST;
    }
}