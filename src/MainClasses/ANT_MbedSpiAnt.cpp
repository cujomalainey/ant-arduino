#ifdef __MBED__

#include <MainClasses/ANT_MbedSpiAnt.h>
#include <ANT_private_defines.h>

MbedSpiAnt::MbedSpiAnt() : BaseSpiAnt<SPISlave, DigitalIn, DigitalOut>() {}


void MbedSpiAnt::setSpi(SPISlave &spi, DigitalIn &hostEnable, DigitalOut &hostMsgReady, DigitalOut &hostSrdy) {
    _spi = &spi;
    _hostEnable = &hostEnable;
    _hostMsgReady = &hostMsgReady;
    _hostSrdy = &hostSrdy;
    _hostMsgReady->write(1);
    _hostSrdy->write(1);
}

uint8_t MbedSpiAnt::available() {
    return _hostEnable->read();
}

uint8_t MbedSpiAnt::read() {
    return _spi->read();
}

void MbedSpiAnt::write(uint8_t val) {
    _spi->reply(val);
}

void MbedSpiAnt::setHostMsgReady(uint8_t value) {
    // _hostMsgReady->write(value);
}

void MbedSpiAnt::setHostSRdy(uint8_t value) {
    _hostSrdy->write(value);
}

uint32_t MbedSpiAnt::getMs() {
    // TODO
    return 0;
}


#endif // __MBED__
