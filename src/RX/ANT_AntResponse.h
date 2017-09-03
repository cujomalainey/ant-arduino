#ifndef ANT_ANTRESPONSE_h
#define ANT_ANTRESPONSE_h
#include <inttypes.h>

/**
 * The super class of all Ant responses (RX packets)
 * Users should never attempt to create an instance of this class; instead
 * create an instance of a subclass
 * It is recommend to reuse subclasses to conserve memory
 */
class AntResponse {
public:
    //static const int MODEM_STATUS = 0x8a;
    /**
     * Default constructor
     */
    AntResponse();
    /**
     * Returns msg Id of the response
     */
    uint8_t getMsgId();
    void setMsgId(uint8_t msgId);
    /**
     * Returns the MSB length of the packet
     */
    uint8_t getLength();
    void setLength(uint8_t length);
    /**
     * Returns the packet checksum
     */
    uint8_t getChecksum();
    void setChecksum(uint8_t checksum);
    void setFrameData(uint8_t* frameDataPtr);
    /**
     * Returns the buffer that contains the response.
     * Starts with byte that follows MSG ID and includes all bytes prior to the checksum
     * Length is specified by getFrameDataLength()
     * Note: Unlike Dynasteam's definition of the frame data, this does not start with the MSG ID..
     * The reason for this is all responses include an MSG ID, whereas my frame data
     * includes only the MSG specific data.
     */
    uint8_t* getFrameData();

    void setFrameLength(uint8_t frameLength);
    /**
     * Returns the length of the packet
     */
    uint8_t getPacketLength();
    /**
     * Resets the response to default values
     */
    void reset();
    /**
     * Initializes the response
     */
    void init();
    /**
     * Call with instance of StartUpMessage class only if getMsgId() == START_UP_MESSAGE
     * to populate response
     */
    void getStartUpMsg(AntResponse &response);
    /**
     * Call with instance of BroadcastData class only if getMsgId() == BROADCAST_DATA
     * to populate response
     */
    void getBroadcastDataMsg(AntResponse &response);
    /**
     * Call with instance of AcknowledgedData class only if getMsgId() == ACKNOWLEDGED_DATA
     * to populate response
     */
    void getAcknowledgedDataMsg(AntResponse &response);
    /**
     * Call with instance of BurstTransferData class only if getMsgId() == BURST_TRANSFER_DATA
     * to populate response
     */
    void getBurstTransferDataMsg(AntResponse &response);
    /**
     * Call with instance of AdvancedBurstData only if getMsgId() == ADVANCED_BURST_DATA
     */
    void getAdvancedBurstDataMsg(AntResponse &responses);
    /**
     * Call with instance of ChannelEvent only if getMsgId() == CHANNEL_EVENT or getMsgId() == CHANNEL_RESPONSE
     */
    void getChannelEventResponseMsg(AntResponse &response);
    /**
     * Call with instance of ChannelIdResponse only if getMsgId() == CHANNEL_ID
     */
    void getChannelIdResponseMsg(AntResponse &response);
    /**
     * Call with instance of ChannelStatus only if getMsgId() == CHANNEL_STATUS
     */
    void getChannelStatusMsg(AntResponse &response);
    /**
     * Call with instance of AntVersion only if getMsgId() == ANT_VERSION
     */
    void getAntVersionMsg(AntResponse &response);
    /**
     * Call with instance of Capabilities only if getMsgId() == CAPABILITIES
     */
    void getCapabilitiesMsg(AntResponse &response);
    /**
     * Call with instance of AdvancedBurstCapabilities only if getMsgId() == ADVANCED_BURST_CAPABILITES
     */
    void getAdvancedBurstCapabilitiesConfigurationMsg(AntResponse &response);
    /**
     * Call with instance of SerialNumber only if getMsgId() == SERIAL_NUMBER
     */
    void getSerialNumberMsg(AntResponse &response);
    /**
     * Returns true if the response has been successfully parsed and is complete and ready for use
     */
    bool isAvailable();
    void setAvailable(bool complete);
    /**
     * Returns true if the response contains errors
     */
    bool isError();
    /**
     * Returns an error code, or zero, if successful.
     * Error codes include: CHECKSUM_FAILURE, PACKET_EXCEEDS_BYTE_ARRAY_LENGTH, UNEXPECTED_START_BYTE
     */
    uint8_t getErrorCode();
    void setErrorCode(uint8_t errorCode);
protected:
    // pointer to frameData
    uint8_t* _frameDataPtr;
private:
    void setCommon(AntResponse &target);
    uint8_t _msgId;
    uint8_t _length;
    uint8_t _checksum;
    bool _complete;
    uint8_t _errorCode;
};
#endif // ANT_ANTRESPONSE_h