#ifndef ANT_SETENCRYPTIONINFO_h
#define ANT_SETENCRYPTIONINFO_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a set encryption info message
 *
 * it is used to configure the ...?
 */
class SetEncryptionInfo : public AntRequest {
public:
    SetEncryptionInfo();
    SetEncryptionInfo(uint8_t channel, uint16_t waveform);
    // TODO implement params
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
};

#endif // ANT_SETENCRYPTIONINFO_h