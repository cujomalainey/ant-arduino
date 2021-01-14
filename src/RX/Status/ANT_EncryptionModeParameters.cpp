#include <RX/Status/ANT_EncryptionModeParameters.h>

EncryptionModeParameters::EncryptionModeParameters() : AntResponse() {

}

// cppcheck-suppress unusedFunction
uint8_t EncryptionModeParameters::getRequestedModeParameter() {
    return getFrameData()[0];
}

// cppcheck-suppress unusedFunction
uint8_t EncryptionModeParameters::getMaxSupportedEncryptionMode() {
    return getFrameData()[1];
}

// cppcheck-suppress unusedFunction
uint32_t EncryptionModeParameters::getUniqueIdentifier() {
    uint32_t identifier = getFrameData()[1];
    identifier |= getFrameData()[2] << BITS_IN_BYTE;
    identifier |= getFrameData()[3] << BITS_IN_SHORT;
    identifier |= getFrameData()[4] << 24;
    return identifier;
}

// cppcheck-suppress unusedFunction
char* EncryptionModeParameters::getUserInformationString() {
    return (char*)(getFrameData() + 1); // skip mode parameter
}

#ifdef NATIVE_API_AVAILABLE

uint32_t EncryptionModeParameters::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    switch (subId) {
    case ENCRYPTION_INFO_GET_SUPPORTED_MODE:
        buf.ANT_MESSAGE_ucSize = MESG_CONFIG_ENCRYPT_REQ_CAPABILITIES_SIZE;
        break;
    case ENCRYPTION_INFO_GET_CRYPTO_ID:
        buf.ANT_MESSAGE_ucSize = MESG_CONFIG_ENCRYPT_REQ_CONFIG_ID_SIZE;
        break;
    case ENCRYPTION_INFO_GET_CUSTOM_USER_DATA:
        buf.ANT_MESSAGE_ucSize = MESG_CONFIG_ENCRYPT_REQ_CONFIG_USER_DATA_SIZE;
        break;
    }
    buf.ANT_MESSAGE_aucMesgData[0] = subId;
    return sd_ant_crypto_info_get(subId, &buf.ANT_MESSAGE_aucMesgData[1]);
}

#endif // NATIVE_API_AVAILABLE
