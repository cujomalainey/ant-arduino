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
    LowPrioritySearchTimeout(uint8_t channel);
    LowPrioritySearchTimeout(uint8_t channel, uint8_t timeout);
    void setChannel(uint8_t channel);
    void setTimeout(uint8_t timeout);
    uint8_t getChannel();
    uint8_t getTimeout();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _timeout;
};

#endif // ANT_LOWPRIORITYSEARCHTIMEOUT_h