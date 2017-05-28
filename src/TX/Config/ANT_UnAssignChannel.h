#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

/**
 * Represents a unassign channel packet, which is used to disociate a channel
 *
 */
class UnAssignChannel : public AntRequest {
public:
    UnAssignChannel();
    UnAssignChannel(uint8_t channel);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _channel;
};