#ifndef ANT_ARDUINOSERIALANT_h
#define ANT_ARDUINOSERIALANT_h

#if defined(ARDUINO) || defined(UNIT_TEST)

#include <BaseClasses/ANT_BaseSerialAnt.h>

class ArduinoSerialAnt : virtual public BaseSerialAnt<Stream> {
public:
    ArduinoSerialAnt();
    explicit ArduinoSerialAnt(Stream &serial);
    /**
     * Specify the serial port.  Only relevant for Arduinos that support multiple serial ports (e.g. Mega)
     */
    void setSerial(Stream &serial) override;
protected:
    uint8_t available() override;
    uint8_t read() override;
    void write(uint8_t* data, uint8_t len) override;
    uint32_t getMs() override;
    Stream* _serial = NULL;
};

#endif // defined(ARDUINO) || defined(UNIT_TEST)

#endif // ANT_ARDUINOANT_h
