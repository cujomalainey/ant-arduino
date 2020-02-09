#ifndef ANT_CHANNELSEARCHSHARING_h
#define ANT_CHANNELSEARCHSHARING_h

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
    ChannelSearchSharing(uint8_t channel, uint8_t cycles);
    void setChannel(uint8_t channel);
    void setSearchcycles(uint8_t cycles);
    uint8_t getChannel();
    uint8_t getSearchCycles();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint8_t _cycles;
};

#endif // ANT_CHANNELSEARCHSHARING_h
