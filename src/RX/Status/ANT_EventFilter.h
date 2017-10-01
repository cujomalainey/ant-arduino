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

    static const uint8_t MSG_ID = EVENT_FILTER;
};

#endif // ANT_EVENTFILTER_h