#include <TX/ANT_AntRequest.h>

/**
 * Represents a transmit power message, it is used to configure
 * the radios transmission characteristics
 */
class TransmitPower : public AntRequest {
public:
    TransmitPower();
    void setTxPower(uint8_t power);
    uint8_t getTxPower();
private:
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
    uint8_t _power;
};