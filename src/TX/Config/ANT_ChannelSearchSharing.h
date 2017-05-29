#include <TX/ANT_AntRequest.h>

/**
 * Represents a channel search sharing message, it is used to
 * configure a channels share cycles when searching for its device.
 * Only channels with the same search priority will share the
 * radio when searching
 */
class ChannelSearchSharing : public AntRequest {
public:
    ChannelSearchSharing();
    void setChannel(uint8_t channel);
    void setSearchcycles(uint8_t cycles);
    uint8_t getChannel();
    uint8_t getSearchCycles();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
    uint8_t _cycles;
};