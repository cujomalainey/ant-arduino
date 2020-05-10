#include <RX/Status/ANT_AntVersion.h>

AntVersion::AntVersion() : AntResponse() {

}

uint8_t AntVersion::getVersionByte(uint8_t pos) {
    return getFrameData()[pos];
}

#ifdef NATIVE_API_AVAILABLE

uint32_t AntVersion::backFill(uint8_t subId, uint8_t *buf) {
    return sd_ant_version_get(buf);
}

#endif // NATIVE_API_AVAILABLE
