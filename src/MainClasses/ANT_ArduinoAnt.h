#ifndef ANT_ARDUINOANT_h
#define ANT_ARDUINOANT_h

#if defined(ARDUINO) || defined(UNIT_TEST)

#include <BaseClasses/ANT_BaseSerialAnt.h>

class ArduinoAnt : virtual public BaseSerialAnt<Stream> {
public:
    ArduinoAnt();
    ArduinoAnt(Stream &serial);
    /**
     * Specify the serial port.  Only relevant for Arduinos that support multiple serial ports (e.g. Mega)
     */
    void setSerial(Stream &serial) override;
protected:
    uint8_t available() override;
    uint8_t read() override;
    void write(uint8_t val) override;
    uint32_t getMs() override;
    Stream* _serial;
};

#endif // defined(ARDUINO) || defined(UNIT_TEST)

#endif // ANT_ARDUINOANT_h
