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
    void setChannel(uint8_t channel);
    void setWaveform(uint16_t waveform);
    uint8_t getChannel();
    uint16_t getWaveform();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif
private:
    uint8_t _channel;
    uint16_t _waveform;
};

#endif // ANT_SEARCHWAVEFORM_h