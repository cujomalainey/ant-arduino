#include <RX/Status/ANT_EventFilter.h>

EventFilter::EventFilter() : AntResponse() {

}

uint8_t EventFilter::getChannelNumber() {
    return getFrameData()[0];
}

uint16_t EventFilter::getEventFilter() {
    uint16_t filter = getFrameData()[1];
    filter |= getFrameData()[2] << 8;
    return filter;
}
