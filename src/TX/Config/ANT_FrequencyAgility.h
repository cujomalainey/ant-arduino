#ifndef ANT_FREQUENCYAGILITY_h
#define ANT_FREQUENCYAGILITY_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a configure event filter packet
 *
 */
class FrequencyAgility : public AntRequest {
public:
    FrequencyAgility();
    FrequencyAgility(uint8_t channel);
    FrequencyAgility(uint8_t channel, uint8_t freq1, uint8_t freq2, uint8_t freq3);
    void setChannel(uint8_t channel);
    void setFrequency(uint8_t index, uint8_t freq);
    void setFrequency1(uint8_t freq);
    void setFrequency2(uint8_t freq);
    void setFrequency3(uint8_t freq);
    uint8_t getChannel();
    uint8_t getFrequency(uint8_t index);
    uint8_t getFrequency1();
    uint8_t getFrequency2();
    uint8_t getFrequency3();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
protected:
    uint8_t _channel;
    uint8_t _freq1;
    uint8_t _freq2;
    uint8_t _freq3;
};

#endif // ANT_FREQUENCYAGILITY_h