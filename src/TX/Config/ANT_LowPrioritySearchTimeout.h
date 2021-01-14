#ifndef ANT_LOWPRIORITYSEARCHTIMEOUT_h
#define ANT_LOWPRIORITYSEARCHTIMEOUT_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Lib Config message, it is used to
 * configure extended responses from the radio
 */
class LowPrioritySearchTimeout : public AntRequest {
public:
    LowPrioritySearchTimeout();
    explicit LowPrioritySearchTimeout(uint8_t channel);
    explicit LowPrioritySearchTimeout(uint8_t channel, uint8_t timeout);
    void setChannel(uint8_t channel);
    void setTimeout(uint8_t timeout);
    uint8_t getChannel();
    uint8_t getTimeout();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel = 0;
    uint8_t _timeout = 0;
};

#endif // ANT_LOWPRIORITYSEARCHTIMEOUT_h
