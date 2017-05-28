#include <TX/ANT_AntRequest.h>

/**
 * Represents a search timeout message, it is used
 * to configure a channel timeout on the ANT radio
 */
class SearchTimeout : public AntRequest {
public:
    SearchTimeout();
    void setChannel(uint8_t channel);
    void setTimeout(uint8_t timeout);
    uint8_t getChannel();
    uint8_t getTimeout();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
    uint8_t _timeout;
};