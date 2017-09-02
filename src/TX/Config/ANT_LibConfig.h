#include <TX/ANT_AntRequest.h>

/**
 * Represents a Lib Config message, it is used to
 * configure a extended responses from the radio
 */
class LibConfig : public AntRequest {
public:
    LibConfig();
    void setConfig(uint8_t config);
    uint8_t getConfig();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _config;
};