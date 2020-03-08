#ifdef UNIT_TEST

#include "Util/Testing.h"
#include <sys/time.h>
#include "unity.h"

Stream Serial = Stream(NULL, NULL);

unsigned long millis() {
    struct timeval time;
    gettimeofday(&time, NULL);
    return time.tv_usec/1000;
}

Stream::Stream(const uint8_t* inBuffer, const uint8_t* outBuffer) {
    _inBuffer = inBuffer;
    _outBuffer = outBuffer;
}

uint8_t Stream::available() {
    return sizeof(_inBuffer) - _read;
}

uint8_t Stream::read() {
    return _inBuffer[_read++];
}

void Stream::write(uint8_t data) {
    if (_wrote < sizeof(_outBuffer)) {
        TEST_ASSERT_EQUAL(data, _outBuffer[_wrote++]);
    }
}

void Stream::write(uint8_t *data, uint8_t len) {
    for (int i = 0; i < len; i++) {
        write(data[i]);
    }
}

#endif // UNIT_TEST
