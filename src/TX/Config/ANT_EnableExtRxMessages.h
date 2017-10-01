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
    EnableExtRxMessages(uint8_t enable);
    void setEnable(uint8_t enable);
    uint8_t getEnable();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _enable;
};

#endif // ANT_ENABLEEXTRXMESSAGES_h