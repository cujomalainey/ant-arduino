#include <RX/Status/ANT_EventFilter.h>

EventFilter::EventFilter() : AntResponse() {

}

uint8_t EventFilter::getChannelNumber() {
    return getFrameData()[0];
}

// cppcheck-suppress unusedFunction
uint16_t EventFilter::getEventFilter() {
    uint16_t filter = getFrameData()[1];
    filter |= getFrameData()[2] << 8;
    return filter;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t EventFilter::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    uint16_t filter;
    uint32_t ret;
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_ucSize = MESG_EVENT_FILTER_CONFIG_REQ_SIZE;
    ret = sd_ant_event_filtering_get(&filter);
    buf.ANT_MESSAGE_aucMesgData[0] = (uint8_t)filter;
    buf.ANT_MESSAGE_aucMesgData[1] = (uint8_t)(filter >> BITS_IN_BYTE);
    return ret;
}

#endif // NATIVE_API_AVAILABLE
