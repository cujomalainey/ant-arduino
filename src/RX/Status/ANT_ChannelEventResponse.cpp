#include <RX/Status/ANT_ChannelEventResponse.h>

ChannelEventResponse::ChannelEventResponse() : AntResponse() {

}

uint8_t ChannelEventResponse::getChannelNumber() {
    return  getFrameData()[0];
}

uint8_t ChannelEventResponse::getResponseMsgId() {
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

#ifdef NATIVE_API_AVAILABLE

uint32_t ChannelEventResponse::backFill(uint8_t chan, uint8_t event, uint8_t extCode, ANT_MESSAGE& buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
