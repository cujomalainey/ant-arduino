#ifndef ANT_SEARCHWAVEFORM_h
#define ANT_SEARCHWAVEFORM_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a search waveform message, it is used to configure
 * the ...?
 */
class SearchWaveform : public AntRequest {
public:
    SearchWaveform();
    SearchWaveform(uint8_t channel, uint16_t waveform);
    void setChannel(uint8_t channel);
    void setWaveform(uint16_t waveform);
    uint8_t getChannel();
    uint16_t getWaveform();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel = 0;
    uint16_t _waveform = 0;
};

#endif // ANT_SEARCHWAVEFORM_h
