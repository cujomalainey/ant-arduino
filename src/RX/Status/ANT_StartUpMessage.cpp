#include <RX/Status/ANT_StartUpMessage.h>

StartUpMessage::StartUpMessage() : AntResponse() {

}

uint8_t StartUpMessage::getMessage() {
    return  getFrameData()[0];
}