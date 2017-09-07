#ifndef ANT_PROXIMITYSEARCH_h
#define ANT_PROXIMITYSEARCH_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a set proximity search packet
 *
 */
class ProximitySearch : public AntRequest {
public:
    ProximitySearch();
    ProximitySearch(uint8_t channel);
    ProximitySearch(uint8_t channel, uint8_t searchThreshold);
    void setChannel(uint8_t channel);
    void setSearchThreshold(uint8_t searchThreshold);
    uint8_t getChannel();
    uint8_t getSearchThreshold();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
protected:
    uint8_t _channel;
    uint8_t _searchThreshold;
};

#endif // ANT_PROXIMITYSEARCH_h