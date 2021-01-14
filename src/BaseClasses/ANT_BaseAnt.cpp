#include <BaseClasses/ANT_BaseAnt.h>

BaseAnt::BaseAnt(): _response(AntResponse()) {
    _response.init();
}

AntResponse& BaseAnt::getResponse() {
    return _response;
}

void BaseAnt::getResponse(AntResponse &response) {

    response.setLength(_response.getLength());
    response.setMsgId(_response.getMsgId());
    response.setFrameData(_response.getFrameData());
}

// cppcheck-suppress unusedFunction
void BaseAnt::readPacketUntilAvailable() {
    while (!(getResponse().isAvailable() || getResponse().isError())) {
        // read some more
        readPacket();
    }
}

bool BaseAnt::readPacket(int timeout) {

    if (timeout < 0) {
        return false;
    }

    unsigned long start = getMs();

    while (int((getMs() - start)) < timeout) {

        readPacket();

        if (getResponse().isAvailable()) {
            return true;
        } else if (getResponse().isError()) {
            return false;
        }
    }

    // timed out
    return false;
}

uint8_t BaseAnt::bufferMessage(uint8_t *buf, AntRequest &request, uint8_t checksum) {
    uint8_t write_pos = 0;

    // write length
    checksum ^= request.getDataLength();
    buf[write_pos++] = request.getDataLength();

    // write msg id
    buf[write_pos++] = request.getMsgId();
    checksum ^= request.getMsgId();

    for (int i = 0; i < request.getDataLength(); i++) {
        buf[write_pos++] = request.getData(i);
        checksum ^= request.getData(i);
    }

    // write checksum
    buf[write_pos++] = checksum;

    return write_pos;
}
