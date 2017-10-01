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
    SetChannelTransmitPower(uint8_t channel, uint8_t transmitPower);
    void setChannel(uint8_t channel);
    void setTransmitPower(uint8_t transmitPower);
    uint8_t getChannel();
    uint16_t getTransmitPower();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _channel;
    uint16_t _transmitPower;
};

#endif // ANT_SETCHANNELTRANSMITPOWER_h