#ifndef ANT_TRANSMITPOWER_h
#define ANT_TRANSMITPOWER_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a transmit power message, it is used to configure
 * the radios transmission characteristics
 */
class TransmitPower : public AntRequest {
public:
    TransmitPower();
    TransmitPower(uint8_t power);
    void setTxPower(uint8_t power);
    uint8_t getTxPower();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _power;
};

#endif // ANT_TRANSMITPOWER_h