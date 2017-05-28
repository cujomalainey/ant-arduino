#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

/**
 * Represents a Acknowledged Tx message, it is used to send a message from the ANT radio
 */
class AcknowledgedMsg : public AntRequest {
public:
    AcknowledgedMsg();
    void setData(uint8_t* data);
    void getData(uint8_t* data);
    void setByte(uint8_t index, uint8_t data);
    uint8_t getByte(uint8_t index);
    void setChannel(uint8_t channel);
    uint8_t getChannel();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _data[MESSAGE_SIZE];
    uint8_t _channel;
};