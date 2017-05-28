#include <TX/ANT_AntRequest.h>

/**
 * Represents a open channel message, it is used to open a configured channel the ANT radio
 */
class OpenChannel : public AntRequest {
public:
    OpenChannel();
    OpenChannel(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
};