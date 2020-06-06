#ifndef ANT_ENCRYPTIONMODEPARAMETERS_h
#define ANT_ENCRYPTIONMODEPARAMETERS_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Channel Id Response Message
 */
class EncryptionModeParameters : public AntResponse {
public:
    EncryptionModeParameters();

    uint8_t getRequestedModeParameter();
    /**
     * Only call if getRequestedModeParameter == 0
     */
    uint8_t getMaxSupportedEncryptionMode();
    /**
     * Only call if getRequestedModeParameter == 1
     */
    uint32_t getUniqueIdentifier();
    /**
     * Only call if getRequestedModeParameter == 2
     */
    char* getUserInformationString();

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t subId, ANT_MESSAGE &buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = ENCRYPTION_MODE_PARAMETERS;
};

#endif // ANT_ENCRYPTIONMODEPARAMETERS_h
