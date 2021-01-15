#include <TX/Config/ANT_FrequencyAgility.h>

#include <ANT_private_defines.h>

FrequencyAgility::FrequencyAgility() : AntRequest(FREQUENCY_AGILITY) {}

FrequencyAgility::FrequencyAgility(uint8_t channel) : AntRequest(FREQUENCY_AGILITY) {
    setChannel(channel);
}

FrequencyAgility::FrequencyAgility(uint8_t channel, uint8_t freq1, uint8_t freq2, uint8_t freq3) : AntRequest(FREQUENCY_AGILITY) {
    setChannel(channel);
    setFrequency1(freq1);
    setFrequency2(freq2);
    setFrequency3(freq3);
}

void FrequencyAgility::setChannel(uint8_t channel) {
    _channel = channel;
}

// cppcheck-suppress unusedFunction
void FrequencyAgility::setFrequency(uint8_t index, uint8_t freq) {
    if (index == 1) {
        setFrequency1(freq);
    } else if (index == 2) {
        setFrequency2(freq);
    } else {
        setFrequency3(freq);
    }
}

void FrequencyAgility::setFrequency1(uint8_t freq) {
    _freq1 = freq;
}

void FrequencyAgility::setFrequency2(uint8_t freq) {
    _freq2 = freq;
}

void FrequencyAgility::setFrequency3(uint8_t freq) {
    _freq3 = freq;
}

uint8_t FrequencyAgility::getChannel() {
    return _channel;
}

// cppcheck-suppress unusedFunction
uint8_t FrequencyAgility::getFrequency(uint8_t index) {
    if (index == 1) {
        return getFrequency1();
    } else if (index == 2) {
        return getFrequency2();
    } else {
        return getFrequency3();
    }
}

uint8_t FrequencyAgility::getFrequency1() {
    return _freq1;
}

uint8_t FrequencyAgility::getFrequency2() {
    return _freq2;
}

uint8_t FrequencyAgility::getFrequency3() {
    return _freq3;
}

uint8_t FrequencyAgility::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _freq1;
    } else if (pos == 2) {
        return _freq2;
    } else {
        return _freq3;
    }
}

uint8_t FrequencyAgility::getDataLength() {
    return FREQUENCY_AGILITY_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t FrequencyAgility::execute() {
    return sd_ant_auto_freq_hop_table_set(_channel, _freq1, _freq2, _freq3);
}

#endif // NATIVE_API_AVAILABLE
