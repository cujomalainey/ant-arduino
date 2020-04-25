#if defined(ARDUINO) || defined(UNIT_TEST)

#include <MainClasses/ANT_ArduinoSerialAnt.h>
#include <ANT_private_defines.h>

EspIdfSerialAnt::EspIdfSerialAnt() : BaseSerialAnt<Stream>() {
    setSerial(0);
}

void EspIdfSerialAnt::setSerial(uart_port_t &serial) {
    _serial = &serial;
}

uint8_t EspIdfSerialAnt::available() {
    size_t size;
    esp_err_t err = uart_get_buffered_data_len(_serial, &size);
    if (err == ESP_OK)
        return size > UINT8_MAX : UINT8_MAX : (uint8_t)size;
    return 0;
}

uint8_t EspIdfSerialAnt::read() {
    uint8_t buf;
    uart_read_bytes(_serial, &buf, 1, 0);
    return buf;
}

void EspIdfSerialAnt::write(uint8_t *data, uint8_t len) {
    uart_write_bytes(_serial, data, len);
}

uint32_t EspIdfSerialAnt::getMs() {
    // convert to millis from micros
    return (uint32_t)(esp_timer_get_time() / 1000);
}

#endif // defined(ARDUINO) || defined(UNIT_TEST)
