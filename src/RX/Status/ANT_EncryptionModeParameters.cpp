#include <RX/Status/ANT_EncryptionModeParameters.h>

EncryptionModeParameters::EncryptionModeParameters() : AntResponse() {

}

uint8_t EncryptionModeParameters::getRequestedModeParameter() {
    return getFrameData()[0];
}

uint8_t EncryptionModeParameters::getMaxSupportedEncryptionMode() {
    return getFrameData()[1];
}

uint32_t EncryptionModeParameters::getUniqueIdentifier() {
    uint32_t identifier = getFrameData()[1];
    identifier |= getFrameData()[2] << BITS_IN_BYTE;
    identifier |= getFrameData()[3] << BITS_IN_SHORT;
    identifier |= getFrameData()[4] << 24;
    return identifier;
}

char* EncryptionModeParameters::getUserInformationString() {
    return (char*)(getFrameData() + 1); // skip mode parameter
}

#ifdef NATIVE_API_AVAILABLE

uint32_t EncryptionModeParameters::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_aucMesgData[0] = subId;
    // TODO set size since its variable
    return sd_ant_crypto_info_get(subId, &buf.ANT_MESSAGE_aucMesgData[1]);
}

#endif // NATIVE_API_AVAILABLE
