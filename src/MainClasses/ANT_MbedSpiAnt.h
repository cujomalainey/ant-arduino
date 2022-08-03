#ifndef ANT_MBEDSPIANT_h
#define ANT_MBEDSPIANT_h

#if IS_MBED

#include <BaseClasses/ANT_BaseSpiAnt.h>

class MbedSpiAnt : public BaseSpiAnt<SPISlave, DigitalIn, DigitalOut> {
public:
    MbedSpiAnt();
    void setSpi(SPISlave &spi, DigitalIn &hostEnable, DigitalOut &hostMsgReady, DigitalOut &hostSrdy) override;
protected:
    void setHostMsgReady(uint8_t value) override;
    void setHostSRdy(uint8_t value) override;
    uint8_t available() override;
    uint8_t read() override;
    void write(uint8_t val) override;
    uint32_t getMs() override;
private:
    SPISlave* _spi;
    DigitalOut* _hostMsgReady;
    DigitalOut* _hostSrdy;
    DigitalIn* _hostEnable;
};

#endif // IS_MBED

#endif // ANT_MBEDSPIANT_h
