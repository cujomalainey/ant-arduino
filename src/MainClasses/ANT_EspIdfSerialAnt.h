#ifndef ANT_ESPIDFSERIALANT_h
#define ANT_ESPIDFSERIALANT_h

#if defined(ESP_PLATFORM)

#include <BaseClasses/ANT_BaseSerialAnt.h>

class EspIdfSerialAnt : virtual public BaseSerialAnt<uart_port_t> {
public:
    EspIdfSerialAnt();
    EspIdfSerialAnt(uart_port_t &serial);
    /**
     * Specify the serial port.  Only relevant for Arduinos that support multiple serial ports (e.g. Mega)
     */
    void setSerial(uart_port_t &num) override;
protected:
    uint8_t available() override;
    uint8_t read() override;
    void write(uint8_t* data, uint8_t len) override;
    uint32_t getMs() override;
    uart_port_t _serial;
};

#endif // defined(ESP_PLATFORM)

#endif // ANT_ESPIDFSERIALANT_h
