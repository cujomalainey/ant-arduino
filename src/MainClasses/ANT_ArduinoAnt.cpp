#ifdef ARDUINO

#include <MainClasses/ANT_ArduinoAnt.h>
#include <ANT_private_defines.h>

ArduinoAnt::ArduinoAnt() : BaseSerialAnt<Stream>() {
    // Contributed by Paul Stoffregen for Teensy support
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__)
    setSerial(Serial1);
#else
    setSerial(Serial);
#endif
}

void ArduinoAnt::setSerial(Stream &serial) {
    _serial = &serial;
}

uint8_t ArduinoAnt::available() {
    return _serial->available();
}

uint8_t ArduinoAnt::read() {
    return _serial->read();
}

void ArduinoAnt::write(uint8_t val) {
    _serial->write(val);
}

uint32_t ArduinoAnt::getMs() {
    return millis();
}

#endif // ARDUINO
