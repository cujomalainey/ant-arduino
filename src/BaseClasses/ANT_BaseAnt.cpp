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

    unsigned long start = millis();

    while (int((millis() - start)) < timeout) {

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
