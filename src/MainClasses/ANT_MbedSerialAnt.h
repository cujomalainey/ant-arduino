#ifndef ANT_MBEDSERIALANT_h
#define ANT_MBEDSERIALANT_h

#include <BaseClasses/ANT_BaseFramework.h>

#if IS_MBED

#include <BaseClasses/ANT_BaseSerialAnt.h>

class MbedSerialAnt : public BaseSerialAnt<UARTSerial> {
public:
    MbedSerialAnt();
    void setSerial(UARTSerial &serial) override;
protected:
    uint8_t available() override;
    uint8_t read() override;
    void write(uint8_t *buf, uint8_t len) override;
    uint32_t getMs() override;
    UARTSerial* _serial;
};

#endif // IS_MBED

#endif // ANT_MBEDSERIALANT_h
