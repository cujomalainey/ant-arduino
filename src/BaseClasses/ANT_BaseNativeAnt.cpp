#include <BaseClasses/ANT_BaseNativeAnt.h>
#include <ANT_private_defines.h>
#include <RX/ANT_messages.h>

#ifdef NATIVE_API_AVAILABLE

// <o> NRF_SDH_ANT_EVENT_QUEUE_SIZE - Event queue size.
#define NRF_SDH_ANT_EVENT_QUEUE_SIZE 32
// <o> NRF_SDH_ANT_BURST_QUEUE_SIZE - ANT burst queue size.
#define NRF_SDH_ANT_BURST_QUEUE_SIZE 128

BaseNativeAnt::BaseNativeAnt() : BaseAnt() {
    getResponse().setFrameData(_responseFrameData);

}

uint8_t BaseNativeAnt::begin(uint8_t total_chan, uint8_t encrypted_chan) {
    uint8_t ret;
    uint16_t buf_size = ANT_ENABLE_GET_REQUIRED_SPACE(
            total_chan,
            encrypted_chan,
            NRF_SDH_ANT_BURST_QUEUE_SIZE,
            NRF_SDH_ANT_EVENT_QUEUE_SIZE);

    if (_sd_buffer)
        free(_sd_buffer);

    _sd_buffer = malloc(buf_size);

    if (!_sd_buffer)
        return 1;

#ifdef USE_TINYUSB
    usb_softdevice_pre_enable();
#endif

    ANT_ENABLE ant_enable_cfg =
    {
        .ucTotalNumberOfChannels = total_chan,
        .ucNumberOfEncryptedChannels = encrypted_chan,
        .usNumberOfEvents = NRF_SDH_ANT_EVENT_QUEUE_SIZE,
        .pucMemoryBlockStartLocation = _sd_buffer,
        .usMemoryBlockByteSize = buf_size,
    };

    ret = sd_ant_enable(&ant_enable_cfg);

#ifdef USE_TINYUSB
    usb_softdevice_post_enable();
#endif

    return ret;
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

    if (_returnFillReady) {
        _returnFillReady = false;
        getResponse().setAvailable(true);
        memcpy(_responseFrameData, _returnFillBuffer, sizeof(_responseFrameData));
        return;
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
            ret = ChannelIdResponse::backFill(request.getData(0), _backFillBuffer);
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
    _returnFillReady = true;

    return ret;
}

#endif // NATIVE_API_AVAILABLE
