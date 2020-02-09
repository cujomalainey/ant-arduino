#ifndef ANT_ANTREQUEST_h
#define ANT_ANTREQUEST_h
#include <inttypes.h>
#include <ANT_defines.h>

/**
 * Super class of all Ant requests (TX packets)
 * It is recommended to reuse subclasses of the class to conserve memory
 */
class AntRequest {
public:
    /**
     * Constructor
     */
    AntRequest(uint8_t msgId);
    /**
     * Returns the Msg id
     */
    uint8_t getMsgId();
    /**
     * Starting after the frame id (pos = 0) and up to but not including the checksum
     * Note: Unlike Dynastream's definition of the frame data, this does not start with the MSG ID.
     * The reason for this is the MSG ID and Frame ID are common to all requests, whereas my definition of
     * frame data is only the MSG specific data.
     */
    virtual uint8_t getData(uint8_t pos) = 0;
    /**
     * Returns the size of the msg frame (not including frame id or msg id or checksum).
     */
    virtual uint8_t getDataLength() = 0;

#ifdef NATIVE_API_AVAILABLE
    /**
     * Call to native API by NativeAnt when sent
     */
    virtual uint32_t execute() = 0;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _msgId;
};

#endif //ANT_ANTREQUEST_h
