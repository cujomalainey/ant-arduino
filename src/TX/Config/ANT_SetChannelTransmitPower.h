#ifndef ANT_SETCHANNELTRANSMITPOWER_h
#define ANT_SETCHANNELTRANSMITPOWER_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a set channel transmit power message
 *
 * configures the Tx power of the specified channel
 */
class SetChannelTransmitPower : public AntRequest {
public:
    SetChannelTransmitPower();
    explicit SetChannelTransmitPower(uint8_t channel);
    explicit SetChannelTransmitPower(uint8_t channel, uint8_t transmitPower);
    void setChannel(uint8_t channel);
    void setTransmitPower(uint8_t transmitPower);
    uint8_t getChannel();
    uint16_t getTransmitPower();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel = 0;
    uint16_t _transmitPower = 0;
};

#endif // ANT_SETCHANNELTRANSMITPOWER_h
