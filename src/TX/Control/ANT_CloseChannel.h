#include <TX/ANT_AntRequest.h>

/**
 * Represents a close channel message, it is used to close a open channel the ANT radio
 */
class CloseChannel : public AntRequest {
public:
    CloseChannel();
    CloseChannel(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    uint8_t _channel;
};