#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel rf frequency message, it is used to
 * configure a channel period on the ANT radio
 */
class ChannelRfFrequency : public AntRequest {
public:
    ChannelRfFrequency();
    void setChannel(uint8_t channel);
    void setRfFrequency(uint8_t frequency);
    uint8_t getChannel();
    uint8_t getRfFrequency();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
    uint8_t _frequency;
};