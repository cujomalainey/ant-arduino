#ifndef ANT_ENABLEEXTRXMESSAGES_h
#define ANT_ENABLEEXTRXMESSAGES_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a enable Ext rx messages
 *
 * used to enable extended fields on data messages
 */
class EnableExtRxMessages : public AntRequest {
public:
    EnableExtRxMessages();
    explicit EnableExtRxMessages(uint8_t enable);
    void setEnable(uint8_t enable);
    uint8_t getEnable();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _enable = 0;
};

#endif // ANT_ENABLEEXTRXMESSAGES_h
