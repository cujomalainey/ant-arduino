#include <BaseClasses/ANT_BaseNativeAnt.h>
#include <ANT_private_defines.h>
#include <RX/ANT_messages.h>

#ifdef NATIVE_API_AVAILABLE

/**
 * Static buffer sizes
 *
 * These can be overriden using compiler flags
 */

//  ANT_EVENT_QUEUE_SIZE - Event queue size.
#ifndef ANT_EVENT_QUEUE_SIZE
#define ANT_EVENT_QUEUE_SIZE 32
#endif // ANT_EVENT_QUEUE_SIZE

//  ANT_BURST_QUEUE_SIZE - ANT burst queue size.
#ifndef ANT_BURST_QUEUE_SIZE
#define ANT_BURST_QUEUE_SIZE 128
#endif // ANT_BURST_QUEUE_SIZE

BaseNativeAnt::BaseNativeAnt() : BaseAnt() {
    getResponse().setFrameData((uint8_t*)_responseFrameData.ANT_MESSAGE_aucMesgData);
}

uint8_t BaseNativeAnt::begin(uint8_t total_chan, uint8_t encrypted_chan) {
    uint8_t ret;
    uint16_t buf_size = ANT_ENABLE_GET_REQUIRED_SPACE(
            total_chan,
            encrypted_chan,
            ANT_BURST_QUEUE_SIZE,
            ANT_EVENT_QUEUE_SIZE);

    // SD must be started externally
    sd_softdevice_is_enabled(&ret);
    if (ret != 1)
      return 1;

    if (_sd_buffer)
        free(_sd_buffer);

    _sd_buffer = (uint8_t*)malloc(buf_size);

    if (!_sd_buffer)
        return 1;

    ANT_ENABLE ant_enable_cfg =
    {
        .ucTotalNumberOfChannels = total_chan,
        .ucNumberOfEncryptedChannels = encrypted_chan,
        .usNumberOfEvents = ANT_EVENT_QUEUE_SIZE,
        .pucMemoryBlockStartLocation = _sd_buffer,
        .usMemoryBlockByteSize = buf_size,
    };

    ret = sd_ant_enable(&ant_enable_cfg);

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
        memcpy(_responseFrameData.ANT_MESSAGE_aucMessage, _returnFillBuffer, sizeof(_responseFrameData));
        return;
    }

    if (_backFillReady) {
        _backFillReady = false;
        getResponse().setAvailable(true);
        memcpy(_responseFrameData.ANT_MESSAGE_aucMessage, _backFillBuffer, sizeof(_responseFrameData));
        return;
    }

    // TODO set offsets correctly
    if (!sd_ant_event_get(&channel, &msgId, _responseFrameData.ANT_MESSAGE_aucMessage)) {
        getResponse().setMsgId(_responseFrameData.ANT_MESSAGE_ucMesgID);
        getResponse().getFrameData();
        getResponse().setAvailable(true);
    }
}

uint32_t BaseNativeAnt::send(AntRequest &request) {
    // TODO Add resset case for startup case
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
