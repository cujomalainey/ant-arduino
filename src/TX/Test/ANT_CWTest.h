#ifndef ANT_CWTEST_h
#define ANT_CWTEST_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a cw test packet
 *
 */
class CWTest : public AntRequest {
public:
    CWTest();
    void setTransmitPower(uint8_t power);
    void setChannelRfFrequency(uint8_t frequency);
    uint8_t getTransmitPower();
    uint8_t getChannelRfFrequency();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _transmitPower;
    uint8_t _channelRfFrequency;
};

#endif // ANT_CWTEST_h
