#include <RX/Status/ANT_StartUpMessage.h>

StartUpMessage::StartUpMessage() : AntResponse() {

}

// cppcheck-suppress unusedFunction
uint8_t StartUpMessage::getMessage() {
    return  getFrameData()[0];
}

#ifdef NATIVE_API_AVAILABLE

uint32_t StartUpMessage::backFill(uint8_t cause, ANT_MESSAGE &buf) {
    // TODO magic numbers
    buf.ANT_MESSAGE_ucSize = 1;
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_ucSubID = cause;
    return NO_RESPONSE_MESSAGE;
}

#endif // NATIVE_API_AVAILABLE
