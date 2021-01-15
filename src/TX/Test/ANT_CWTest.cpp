#include <TX/Test/ANT_CWTest.h>

#include <ANT_private_defines.h>

CWTest::CWTest() : AntRequest(CW_TEST) {}

CWTest::CWTest(uint8_t power, uint8_t frequency) : AntRequest(CW_TEST), _transmitPower(power), _channelRfFrequency(frequency) {
}

void CWTest::setTransmitPower(uint8_t power) {
    _transmitPower = power;
}

// cppcheck-suppress unusedFunction
void CWTest::setChannelRfFrequency(uint8_t frequency) {
    _channelRfFrequency = frequency;
}

uint8_t CWTest::getTransmitPower() {
    return _transmitPower;
}

// cppcheck-suppress unusedFunction
uint8_t CWTest::getChannelRfFrequency() {
    return _channelRfFrequency;
}

uint8_t CWTest::getData(uint8_t pos) {
    if (pos == 0) {
        return 0;
    } else if (pos == 1) {
        return _transmitPower;
    } else {
        return _channelRfFrequency;
    }
}

uint8_t CWTest::getDataLength() {
    return CW_TEST_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t CWTest::execute() {
    return sd_ant_cw_test_mode(_channelRfFrequency, _transmitPower, 0, 0);
}

#endif // NATIVE_API_AVAILABLE
