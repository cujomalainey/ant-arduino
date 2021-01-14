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
    CWTest(uint8_t power, uint8_t frequency);
    void setTransmitPower(uint8_t power);
    void setChannelRfFrequency(uint8_t frequency);
    uint8_t getTransmitPower();
    uint8_t getChannelRfFrequency();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _transmitPower = 0;
    uint8_t _channelRfFrequency = 0;
};

#endif // ANT_CWTEST_h
