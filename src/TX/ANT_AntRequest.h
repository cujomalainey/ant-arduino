#ifndef ANT_ANTREQUEST_h
#define ANT_ANTREQUEST_h
#include <inttypes.h>

/**
 * Super class of all Ant requests (TX packets)
 * Users should never create an instance of this class; instead use an subclass of this class
 * It is recommended to reuse Subclasses of the class to conserve memory
 * <p/>
 * This class allocates a buffer to
 */
class AntRequest {
public:
    /**
     * Constructor
     * TODO make protected
     */
    AntRequest(uint8_t msgId);
    /**
     * Returns the Msg id
     */
    uint8_t getMsgId();
    // setting = 0 makes this a pure virtual function, meaning the subclass must implement, like abstract in java
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
    //void reset();
protected:
    void setMsgId(uint8_t msgId);
private:
    uint8_t _msgId;
};

#endif //ANT_ANTREQUEST_h