#if defined(ARDUINO) || defined(UNIT_TEST)

#include <MainClasses/ANT_ArduinoSerialAnt.h>
#include <ANT_private_defines.h>

ArduinoSerialAnt::ArduinoSerialAnt() : BaseSerialAnt<Stream>() {
    // Contributed by Paul Stoffregen for Teensy support
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__)
    setSerial(Serial1);
#else
    setSerial(Serial);
#endif
}

ArduinoSerialAnt::ArduinoSerialAnt(Stream &serial) : BaseSerialAnt<Stream>(), _serial(&serial) {}

void ArduinoSerialAnt::setSerial(Stream &serial) {
    _serial = &serial;
}

uint8_t ArduinoSerialAnt::available() {
    return _serial->available();
}

uint8_t ArduinoSerialAnt::read() {
    return _serial->read();
}

void ArduinoSerialAnt::write(uint8_t *data, uint8_t len) {
    _serial->write(data, len);
}

uint32_t ArduinoSerialAnt::getMs() {
    return millis();
}

#endif // defined(ARDUINO) || defined(UNIT_TEST)
