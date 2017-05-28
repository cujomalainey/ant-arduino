/**
 * Represents a Advanced Burst Data Tx message, it is used to send a message from the ANT radio
 */
class AdvancedBurstDataMsg : public AntTxDataRequest {
public:
    AdvancedBurstDataMsg();
    void setData(uint8_t* data);
    void getData(uint8_t* data);
    void setByte(uint8_t index, uint8_t data);
    uint8_t getByte(uint8_t index);
    void setChannelSequence(uint8_t channel);
    uint8_t getChannelSequence();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _data[MESSAGE_SIZE];
    uint8_t _channel;
};