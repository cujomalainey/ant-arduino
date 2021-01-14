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
    explicit ProximitySearch(uint8_t channel);
    explicit ProximitySearch(uint8_t channel, uint8_t searchThreshold);
    void setChannel(uint8_t channel);
    void setSearchThreshold(uint8_t searchThreshold);
    uint8_t getChannel();
    uint8_t getSearchThreshold();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel = 0;
    uint8_t _searchThreshold = 0;
};

#endif // ANT_PROXIMITYSEARCH_h
