#include <BaseClasses/ANT_BaseNativeAnt.h>
#include <ANT_private_defines.h>

#ifdef NATIVE_API_AVAILABLE

BaseNativeAnt::BaseNativeAnt() : BaseAnt() {
    getResponse().setFrameData(_responseFrameData);

}

void BaseNativeAnt::resetResponse() {
    getResponse().reset();
}

void BaseNativeAnt::readPacket() {
    // reset previous response
    if (getResponse().isAvailable() || getResponse().isError()) {
        // discard previous packet and start over
        resetResponse();
    }

    read();
}

uint32_t BaseNativeAnt::send(AntRequest &request) {
    if (request.getMsgId() == REQUEST_MESSAGE) {
        return handleRequest(request);
    } else {
        return request.execute();
    }
}

uint32_t BaseNativeAnt::handleRequest(AntRequest &request) {
    uint8_t msgId = request.getData(0);
    switch (msgId) {
        case CHANNEL_STATUS:
        case ANT_VERSION:
        case CAPABILITIES:
        case CHANNEL_ID:
        case ADVANCED_BURST_CONFIGURATION: // ADVANCED_BURST_CAPABILITES
        case EVENT_FILTER:
        case SELECTIVE_DATA_UPDATE_MASK_SETTING:
        case ENCRYPTION_MODE_PARAMETERS:
            return 0;
        default:
            return INVALID_MESSAGE;
    }
}

#endif // NATIVE_API_AVAILABLE
