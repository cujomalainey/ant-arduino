#ifndef ANT_REQUESTMESSAGE_h
#define ANT_REQUESTMESSAGE_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a request message, it is used to request a message from the ANT radio
 */
class RequestMessage : public AntRequest {
public:
    RequestMessage();
    explicit RequestMessage(uint8_t msgId);
    explicit RequestMessage(uint8_t msgId, uint8_t subId);
    void setRequestedMessage(uint8_t msgId);
    void setSubId(uint8_t subId);
    uint8_t getRequestedMessage();
    uint8_t getSubId();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif
private:
    uint8_t _msgId = 0;
    uint8_t _subId = 0;
};

#endif // ANT_REQUESTMESSAGE_h
