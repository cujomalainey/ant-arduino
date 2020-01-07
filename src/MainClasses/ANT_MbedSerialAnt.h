#ifndef ANT_MBEDSERIALANT_h
#define ANT_MBEDSERIALANT_h

#ifdef __MBED__

#include <BaseClasses/ANT_BaseSerialAnt.h>

class MbedSerialAnt : public BaseSerialAnt<UARTSerial> {
public:
    MbedSerialAnt();
    void setSerial(UARTSerial &serial) override;
protected:
    uint8_t available() override;
    uint8_t read() override;
    void write(uint8_t val) override;
    uint32_t getMs() override;
    UARTSerial* _serial;
};

#endif // __MBED__

#endif // ANT_MBEDSERIALANT_h
