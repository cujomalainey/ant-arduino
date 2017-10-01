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

    static const uint8_t MSG_ID = ENCRYPTION_MODE_PARAMETERS;
};

#endif // ANT_ENCRYPTIONMODEPARAMETERS_h