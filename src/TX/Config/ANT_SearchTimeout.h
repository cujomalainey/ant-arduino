#ifndef ANT_SEARCHTIMEOUT_h
#define ANT_SEARCHTIMEOUT_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a search timeout message, it is used
 * to configure a channel timeout on the ANT radio
 */
class SearchTimeout : public AntRequest {
public:
    SearchTimeout();
    SearchTimeout(uint8_t channel, uint8_t timeout);
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
    uint8_t _channel;
    uint8_t _timeout;
};

#endif // ANT_SEARCHTIMEOUT_h
