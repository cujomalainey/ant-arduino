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
    // TODO
    static const uint8_t MSG_ID = ENCRYPTION_MODE_PARAMETERS;
};

#endif // ANT_ENCRYPTIONMODEPARAMETERS_h