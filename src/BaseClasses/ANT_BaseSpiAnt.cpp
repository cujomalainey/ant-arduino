#include <BaseClasses/ANT_BaseSpiAnt.h>
#include <ANT_private_defines.h>


template<class S, class I, class O>
BaseSpiAnt<S, I, O>::BaseSpiAnt() : BaseAnt() {
    getResponse().setFrameData(_responseFrameData);

}

template<class S, class I, class O>
void BaseSpiAnt<S, I, O>::resetResponse() {
    _pos = 0;
    _checksumTotal = 0;
    getResponse().reset();
}

template<class S, class I, class O>
void BaseSpiAnt<S, I, O>::begin(S &spi, I &hostEnable, O &hostMsgReady, O &hostSrdy) {
    setSpi(spi, hostEnable, hostMsgReady, hostSrdy);
}

template<class S, class I, class O>
void BaseSpiAnt<S, I, O>::readPacket() {
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

// TODO remove
#define SYNC_MASK 0xFE
#define SYNC_BYTE 0xA4
#define SYNC_READ_BIT 1
#define SUCCESS 0
template<class S, class I, class O>
void BaseSpiAnt<S, I, O>::send(AntRequest &request) {
    uint8_t sync, packetRead = 0;
    uint8_t write_pos = 0;
    uint8_t checksum = 0;
    uint8_t buf[ANT_MAX_MSG_DATA_SIZE];

    setHostMsgReady(0);

    // block until radio acks
    while(available()) {}

    setHostSRdy(0);

    sync = read();

    if ((sync & SYNC_MASK) != SYNC_BYTE) {
        setHostSRdy(1);
    }

    // ant synced as a write
    // read back and send write next
    if (!(sync & SYNC_READ_BIT)) {
        _pos = 1;
        // readPacket();
        setHostMsgReady(1);
        packetRead = 1;

        // block until radio acks
        while(!available()) {}

        sync = read();
    }

    // buffer initial byte
    // TODO does this need write bit set?
    checksum ^= ANT_START_BYTE;
    buf[write_pos++] = ANT_START_BYTE;

    write_pos += bufferMessage(&buf[write_pos], request, checksum);

    // TODO rewrite buffer write
    // data, offset for start byte sent by radio
    write(buf[0]);

}

template<class S, class I, class O>
// cppcheck-suppress unusedFunction
void BaseSpiAnt<S, I, O>::resetRadio() {
    setHostMsgReady(1);
    setHostSRdy(1);
    setHostSRdy(0);
    // TODO wait 1 ms
    setHostMsgReady(0);
    setHostSRdy(1);
}

#ifdef IS_MBED
template class BaseSpiAnt<SPISlave, DigitalIn, DigitalOut>;
#endif
