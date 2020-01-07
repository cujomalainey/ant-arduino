#ifdef __MBED__

#include <MainClasses/ANT_MbedSerialAnt.h>
#include <ANT_private_defines.h>

MbedSerialAnt::MbedSerialAnt() : BaseSerialAnt<UARTSerial>() {}


void MbedSerialAnt::setSerial(UARTSerial &serial) {
    _serial = &serial;
}

uint8_t MbedSerialAnt::available() {
    return _serial->readable();
}

uint8_t MbedSerialAnt::read() {
    uint8_t buf;
    _serial->read(&buf, 1);
    return buf;
}

void MbedSerialAnt::write(uint8_t val) {
    _serial->write(&val, 1);
}

uint32_t MbedSerialAnt::getMs() {
    // TODO
    return 0;
}


#endif // __MBED__
