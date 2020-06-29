#ifndef ANT_CONFIGUREEVENTFILTER_h
#define ANT_CONFIGUREEVENTFILTER_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a configure event filter packet
 *
 */
class ConfigureEventFilter : public AntRequest {
public:
    ConfigureEventFilter();
    ConfigureEventFilter(uint16_t eventFilter);
    void setEventFilter(uint16_t eventFilter);
    uint16_t getEventFilter();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint16_t _eventFilter;
};

#endif // ANT_CONFIGUREEVENTFILTER_h
