#include <RX/Status/ANT_AntVersion.h>

AntVersion::AntVersion() : AntResponse() {

}

uint8_t AntVersion::getVersionByte(uint8_t pos) {
    return getFrameData()[pos];
}