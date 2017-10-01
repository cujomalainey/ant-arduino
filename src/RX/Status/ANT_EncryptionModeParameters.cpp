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
    identifier |= getFrameData()[2] << 8;
    identifier |= getFrameData()[3] << 16;
    identifier |= getFrameData()[4] << 24;
    return identifier;
}

char* EncryptionModeParameters::getUserInformationString() {
    return (char*)(getFrameData() + 1); // skip mode parameter
}
