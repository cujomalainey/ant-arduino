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
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    uint8_t _channel;
};