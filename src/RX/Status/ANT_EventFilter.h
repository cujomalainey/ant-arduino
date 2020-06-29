#ifndef ANT_EVENTFILTER_h
#define ANT_EVENTFILTER_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

/**
 * Represents a Event Filter Response Message
 */
class EventFilter : public AntResponse {
public:
    EventFilter();

    uint8_t getChannelNumber();
    uint16_t getEventFilter();

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t subId, ANT_MESSAGE &buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = EVENT_FILTER;
};

#endif // ANT_EVENTFILTER_h
