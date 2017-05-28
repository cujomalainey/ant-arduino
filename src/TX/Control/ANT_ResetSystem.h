#include <TX/ANT_AntRequest.h>

/**
 * Represents a reset system message, it is used to reset the ANT radio
 */
class ResetSystem : public AntRequest {
public:
    ResetSystem();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
};