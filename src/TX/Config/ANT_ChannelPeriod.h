#ifndef ANT_CHANNELPERIOD_h
#define ANT_CHANNELPERIOD_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel period message, it is used to
 * configure a channel period on the ANT radio
 */
class ChannelPeriod : public AntRequest {
public:
    ChannelPeriod();
    ChannelPeriod(uint8_t channel, uint16_t period);
    void setChannel(uint8_t channel);
    void setPeriod(uint16_t period);
    uint8_t getChannel();
    uint16_t getPeriod();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _channel = 0;
    uint16_t _period = 0;
};

#endif // ANT_CHANNELPERIOD_h
