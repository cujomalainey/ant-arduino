#include <BaseClasses/ANT_BaseSerialAnt.h>
#include <ANT_private_defines.h>

template<class T>
BaseSerialAnt<T>::BaseSerialAnt() : BaseAnt() {
    _pos = 0;
    _checksumTotal = 0;
    getResponse().setFrameData(_responseFrameData);

}

template<class T>
void BaseSerialAnt<T>::resetResponse() {
    _pos = 0;
    _checksumTotal = 0;
    getResponse().reset();
}

template<class T>
void BaseSerialAnt<T>::begin(T &serial) {
    setSerial(serial);
}

template<class T>
void BaseSerialAnt<T>::readPacket() {
    // reset previous response
    if (getResponse().isAvailable() || getResponse().isError()) {
        // discard previous packet and start over
        resetResponse();
    }

    while (available()) {

        b = read();

        // checksum includes all bytes including the sync
        _checksumTotal ^= b;

        switch(_pos) {
            case 0:
                if (b == ANT_START_BYTE) {
                    _pos++;
                }
                // TODO should we be reseting the checksum here if we fail to match the start byte?

                break;
            case 1:
                // length msb
                getResponse().setLength(b);
                _pos++;

                break;
            case 2:
                getResponse().setMsgId(b);
                _pos++;

                break;
            default:
                // starts at fourth byte

                if (_pos > ANT_MAX_MSG_DATA_SIZE) {
                    // exceed max size.  should never occur
                    getResponse().setErrorCode(PACKET_EXCEEDS_BYTE_ARRAY_LENGTH);
                    return;
                }

                // check if we're at the end of the packet
                if (_pos == (getResponse().getLength() + 3)) {
                    // verify checksum
                    // if the last byte is the checksum
                    // then XOR it with itself should be 0

                    if (_checksumTotal == 0) {
                        getResponse().setChecksum(b);
                        getResponse().setAvailable(true);

                        getResponse().setErrorCode(NO_ERROR);
                    } else {
                        // checksum failed
                        getResponse().setErrorCode(CHECKSUM_FAILURE);
                    }

                    // reset state vars
                    _pos = 0;

                    return;
                } else {
                    // add to packet array, starting with the fourth byte of the msgId
                    getResponse().getFrameData()[_pos - ANT_MSG_FRONT_OVERHEAD] = b;
                    _pos++;
                }
        }
    }
}

template<class T>
void BaseSerialAnt<T>::send(AntRequest &request) {
    // checksum is XOR of all bytes
    uint8_t checksum = 0;
    uint8_t write_pos = 0;
    uint8_t buf[ANT_MAX_MSG_DATA_SIZE];

    checksum ^= ANT_START_BYTE;
    buf[write_pos++] = ANT_START_BYTE;

    write_pos += bufferMessage(&buf[write_pos], request, checksum);

    write(buf, write_pos);
}

#if defined(ARDUINO) || defined(UNIT_TEST)
template class BaseSerialAnt<Stream>;
#elif IS_MBED
template class BaseSerialAnt<UARTSerial>;
#endif
