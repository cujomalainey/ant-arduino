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
    explicit TransmitPower(uint8_t power);
    void setTxPower(uint8_t power);
    uint8_t getTxPower();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _power = 0;
};

#endif // ANT_TRANSMITPOWER_h
