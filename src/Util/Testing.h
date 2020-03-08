#ifdef UNIT_TEST
#ifndef ANT_TESTING_h
#define ANT_TESTING_h
#include <string.h>
#include <inttypes.h>

unsigned long millis();

class Stream {
public:
    Stream(const uint8_t* inBuffer, const uint8_t* outBuffer);
    uint8_t available();
    uint8_t read();
    void write(uint8_t data);
    void write(uint8_t *data, uint8_t len);
private:
    const uint8_t* _inBuffer;
    const uint8_t* _outBuffer;
    uint8_t _read = 0;
    uint8_t _wrote = 0;
};

extern Stream Serial;
#endif // ANT_TESTING_h
#endif // UNIT_TEST
