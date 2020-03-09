#include <BaseClasses/ANT_BaseNativeAnt.h>
#include <ANT_private_defines.h>
#include <RX/ANT_messages.h>

#ifdef NATIVE_API_AVAILABLE

BaseNativeAnt::BaseNativeAnt() : BaseAnt() {
    getResponse().setFrameData(_responseFrameData);

}

void BaseNativeAnt::resetResponse() {
    getResponse().reset();
}

void BaseNativeAnt::readPacket() {
    uint8_t msgId, channel;

    // reset previous response
    if (getResponse().isAvailable() || getResponse().isError()) {
        // discard previous packet and start over
        resetResponse();
    }

    if (_backFillReady) {
        _backFillReady = false;
        getResponse().setAvailable(true);
        memcpy(_responseFrameData, _backFillBuffer, sizeof(_responseFrameData));
        return;
    }

    // TODO set offsets correctly
    if (!sd_ant_event_get(&channel, &msgId, &_responseFrameData[2])) {
        getResponse().setMsgId(msgId);
        getResponse().getFrameData();
        getResponse().setAvailable(true);
    }
}

uint32_t BaseNativeAnt::send(AntRequest &request) {
    if (request.getMsgId() == REQUEST_MESSAGE) {
        return handleRequest(request);
    } else {
        return request.execute();
    }
}

uint32_t BaseNativeAnt::handleRequest(AntRequest &request) {
    uint8_t msgId = request.getData(1);
    uint32_t ret;
    switch (msgId) {
        case CHANNEL_STATUS:
            ret = ChannelStatus::backFill(request.getData(0), _backFillBuffer);
            break;
        case ANT_VERSION:
            ret = AntVersion::backFill(request.getData(0), _backFillBuffer);
            break;
        case CAPABILITIES:
            ret = Capabilities::backFill(request.getData(0), _backFillBuffer);
            break;
        case CHANNEL_ID:
            ret = ChannelIdResponse::backFill(request,getData(0), _backFillBuffer);
            break;
        case ADVANCED_BURST_CONFIGURATION: // ADVANCED_BURST_CAPABILITES
            ret = AdvancedBurstCapabilitiesConfiguration::backFill(request.getData(0), _backFillBuffer);
            break;
        case EVENT_FILTER:
            ret = EventFilter::backFill(request.getData(0), _backFillBuffer);
            break;
        case SELECTIVE_DATA_UPDATE_MASK_SETTING:
            ret = SelectiveDataUpdateMaskSetting::backFill(request.getData(0), _backFillBuffer);
            break;
        case ENCRYPTION_MODE_PARAMETERS:
            ret = EncryptionModeParameters::backFill(request.getData(0), _backFillBuffer);
            break;
        default:
            return INVALID_MESSAGE;
    }
    _backFillReady = true;
    return ret;
}

#endif // NATIVE_API_AVAILABLE
