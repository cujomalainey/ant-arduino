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
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
};