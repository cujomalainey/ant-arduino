#ifndef ANT_UNASSIGNCHANNEL_h
#define ANT_UNASSIGNCHANNEL_h

#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

/**
 * Represents a unassign channel packet, which is used to disociate a channel
 *
 */
class UnAssignChannel : public AntRequest {
public:
    UnAssignChannel();
    explicit UnAssignChannel(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _channel = 0;
};

#endif // ANT_UNASSIGNCHANNEL_h
