#include <RX/Status/ANT_AntVersion.h>

AntVersion::AntVersion() : AntResponse() {}

// cppcheck-suppress unusedFunction
uint8_t AntVersion::getVersionByte(uint8_t pos) {
    return getFrameData()[pos];
}

#ifdef NATIVE_API_AVAILABLE

uint32_t AntVersion::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_ucSize = MESG_VERSION_SIZE;
    return sd_ant_version_get(buf.ANT_MESSAGE_aucMesgData);
}

#endif // NATIVE_API_AVAILABLE
