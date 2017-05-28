#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel period message, it is used to
 * configure a channel period on the ANT radio
 */
class ChannelPeriod : public AntRequest {
public:
    ChannelPeriod();
    void setChannel(uint8_t channel);
    void setPeriod(uint16_t period);
    uint8_t getChannel();
    uint16_t getPeriod();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
    uint16_t _period;
};