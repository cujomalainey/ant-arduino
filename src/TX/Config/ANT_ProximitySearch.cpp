#include <TX/Config/ANT_ProximitySearch.h>

#include <ANT_private_defines.h>

ProximitySearch::ProximitySearch() : AntRequest(PROXIMITY_SEARCH) {

}

ProximitySearch::ProximitySearch(uint8_t channel) : AntRequest(PROXIMITY_SEARCH) {
    setChannel(channel);
}

ProximitySearch::ProximitySearch(uint8_t channel, uint8_t searchThreshold) : AntRequest(PROXIMITY_SEARCH) {
    setChannel(channel);
    setSearchThreshold(searchThreshold);
}

void ProximitySearch::setChannel(uint8_t channel) {
    _channel = channel;
}

void ProximitySearch::setSearchThreshold(uint8_t searchThreshold) {
    _searchThreshold = searchThreshold;
}

uint8_t ProximitySearch::getChannel() {
    return _channel;
}

uint8_t ProximitySearch::getSearchThreshold() {
    return _searchThreshold;
}

uint8_t ProximitySearch::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else {
        return _searchThreshold;
    }
}

uint8_t ProximitySearch::getDataLength() {
    return PROXIMITY_SEARCH_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t ProximitySearch::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
