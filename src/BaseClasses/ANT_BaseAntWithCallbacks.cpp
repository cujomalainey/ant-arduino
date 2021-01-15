#include <BaseClasses/ANT_BaseAntWithCallbacks.h>

// cppcheck-suppress unusedFunction
void BaseAntWithCallbacks::loop() {
    if (loopTop())
        loopBottom();
}

bool BaseAntWithCallbacks::loopTop() {
    readPacket();
    if (getResponse().isAvailable()) {
        _onResponse.call(getResponse());
        return true;
    } else if (getResponse().isError()) {
        _onPacketError.call(getResponse().getErrorCode());
    }
    return false;
}

void BaseAntWithCallbacks::loopBottom() {
    bool called = false;
    uint8_t id = getResponse().getMsgId();
    switch (id) {
        case ACKNOWLEDGED_DATA:
        {
            AcknowledgedData response;
            getResponse().getAcknowledgedDataMsg(response);
            called = _onAcknowledgedData.call(response);
            break;
        }
        case ADVANCED_BURST_DATA:
        {
            AdvancedBurstData response;
            getResponse().getAdvancedBurstDataMsg(response);
            called = _onAdvancedBurstData.call(response);
            break;
        }
        case BROADCAST_DATA:
        {
            BroadcastData response;
            getResponse().getBroadcastDataMsg(response);
            called = _onBroadcastData.call(response);
            break;
        }
        case BURST_TRANSFER_DATA:
        {
            BurstTransferData response;
            getResponse().getBurstTransferDataMsg(response);
            called = _onBurstTransferData.call(response);
            break;
        }
        case ADVANCED_BURST_CAPABILITES:
        {   // also ADVANCED_BURST_CONFIGURATION
            AdvancedBurstCapabilitiesConfiguration response;
            getResponse().getAdvancedBurstCapabilitiesConfigurationMsg(response);
            called = _onAdvancedBurstCapabilitiesConfiguration.call(response);
            break;
        }
        case ANT_VERSION:
        {
            AntVersion response;
            getResponse().getAntVersionMsg(response);
            called = _onAntVersion.call(response);
            break;
        }
        case CAPABILITIES:
        {
            Capabilities response;
            getResponse().getCapabilitiesMsg(response);
            called = _onCapabilities.call(response);
            break;
        }
        case CHANNEL_EVENT:
        {   // also CHANNEL_RESPONSE
            ChannelEventResponse response;
            getResponse().getChannelEventResponseMsg(response);
            called = _onChannelEventResponse.call(response);
            break;
        }
        case CHANNEL_ID:
        {
            ChannelIdResponse response;
            getResponse().getChannelIdResponseMsg(response);
            called = _onChannelIdResponse.call(response);
            break;
        }
        case CHANNEL_STATUS:
        {
            ChannelStatus response;
            getResponse().getChannelStatusMsg(response);
            called = _onChannelStatus.call(response);
            break;
        }
        case ENCRYPTION_MODE_PARAMETERS:
        {
            EncryptionModeParameters response;
            getResponse().getEncryptionModeParametersMsg(response);
            called = _onEncryptionModeParameters.call(response);
            break;
        }
        case EVENT_FILTER:
        {
            EventFilter response;
            getResponse().getEventFilterMsg(response);
            called = _onEventFilter.call(response);
            break;
        }
        case SELECTIVE_DATA_UPDATE_MASK_SETTING:
        {
            SelectiveDataUpdateMaskSetting response;
            getResponse().getSelectiveDataUpdateMaskSettingMsg(response);
            called = _onSelectiveDataUpdateMaskSetting.call(response);
            break;
        }
        case START_UP_MESSAGE:
        {
            StartUpMessage response;
            getResponse().getStartUpMsg(response);
            called = _onStartUpMessage.call(response);
            break;
        }
    }

    if (!called)
        _onOtherResponse.call(getResponse());
}

uint8_t BaseAntWithCallbacks::matchStatus(uint8_t msgId) {
    ChannelEventResponse msg;

    if (getResponse().getMsgId() == CHANNEL_RESPONSE)
    {
        getResponse().getChannelEventResponseMsg(msg);
        if (msg.getResponseMsgId() == msgId) {
            return msg.getCode();
        }
    }
    return 0xff;
}

uint8_t BaseAntWithCallbacks::waitForInternal(uint8_t msgId, void *response, uint16_t timeout, void *func, uintptr_t data) {
    unsigned long start = getMs();
    do {
        // Wait for a packet of the right type
        if (loopTop() && getResponse().getMsgId() == msgId) {
            // If the type is right, call the right
            // conversion function based on the
            // MsgId and call the match function.
            // Because the match function is
            // essentially called in the same way,
            // regardless of the subclass used, the
            // compiler can reduce most of the below
            // mess into a single piece of code
            // (though for fully optimizing, the
            // separate getXxxResponse() methods
            // must be unified as well).
            switch(msgId) {
                case AcknowledgedData::MSG_ID: {
                    AcknowledgedData *r = static_cast<AcknowledgedData*>(response);
                    bool(*f)(AcknowledgedData&,uintptr_t) = (bool(*)(AcknowledgedData&,uintptr_t))func;
                    getResponse().getAcknowledgedDataMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case AdvancedBurstData::MSG_ID: {
                    AdvancedBurstData *r = static_cast<AdvancedBurstData*>(response);
                    bool(*f)(AdvancedBurstData&,uintptr_t) = (bool(*)(AdvancedBurstData&,uintptr_t))func;
                    getResponse().getAdvancedBurstDataMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case BroadcastData::MSG_ID: {
                    BroadcastData *r = static_cast<BroadcastData*>(response);
                    bool(*f)(BroadcastData&,uintptr_t) = (bool(*)(BroadcastData&,uintptr_t))func;
                    getResponse().getBroadcastDataMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case BurstTransferData::MSG_ID: {
                    BurstTransferData *r = static_cast<BurstTransferData*>(response);
                    bool(*f)(BurstTransferData&,uintptr_t) = (bool(*)(BurstTransferData&,uintptr_t))func;
                    getResponse().getBurstTransferDataMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case AdvancedBurstCapabilitiesConfiguration::MSG_ID: {
                    AdvancedBurstCapabilitiesConfiguration *r = static_cast<AdvancedBurstCapabilitiesConfiguration*>(response);
                    bool(*f)(AdvancedBurstCapabilitiesConfiguration&,uintptr_t) = (bool(*)(AdvancedBurstCapabilitiesConfiguration&,uintptr_t))func;
                    getResponse().getAdvancedBurstDataMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case AntVersion::MSG_ID: {
                    AntVersion *r = static_cast<AntVersion*>(response);
                    bool(*f)(AntVersion&,uintptr_t) = (bool(*)(AntVersion&,uintptr_t))func;
                    getResponse().getAntVersionMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case Capabilities::MSG_ID: {
                    Capabilities *r = static_cast<Capabilities*>(response);
                    bool(*f)(Capabilities&,uintptr_t) = (bool(*)(Capabilities&,uintptr_t))func;
                    getResponse().getCapabilitiesMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case ChannelEventResponse::MSG_ID: {
                    ChannelEventResponse *r = static_cast<ChannelEventResponse*>(response);
                    bool(*f)(ChannelEventResponse&,uintptr_t) = (bool(*)(ChannelEventResponse&,uintptr_t))func;
                    getResponse().getChannelEventResponseMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case ChannelIdResponse::MSG_ID: {
                    ChannelIdResponse *r = static_cast<ChannelIdResponse*>(response);
                    bool(*f)(ChannelIdResponse&,uintptr_t) = (bool(*)(ChannelIdResponse&,uintptr_t))func;
                    getResponse().getChannelIdResponseMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case ChannelStatus::MSG_ID: {
                    ChannelStatus *r = static_cast<ChannelStatus*>(response);
                    bool(*f)(ChannelStatus&,uintptr_t) = (bool(*)(ChannelStatus&,uintptr_t))func;
                    getResponse().getChannelStatusMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case EncryptionModeParameters::MSG_ID: {
                    EncryptionModeParameters *r = static_cast<EncryptionModeParameters*>(response);
                    bool(*f)(EncryptionModeParameters&,uintptr_t) = (bool(*)(EncryptionModeParameters&,uintptr_t))func;
                    getResponse().getEncryptionModeParametersMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case EventFilter::MSG_ID: {
                    EventFilter *r = static_cast<EventFilter*>(response);
                    bool(*f)(EventFilter&,uintptr_t) = (bool(*)(EventFilter&,uintptr_t))func;
                    getResponse().getEventFilterMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case SelectiveDataUpdateMaskSetting::MSG_ID: {
                    SelectiveDataUpdateMaskSetting *r = static_cast<SelectiveDataUpdateMaskSetting*>(response);
                    bool(*f)(SelectiveDataUpdateMaskSetting&,uintptr_t) = (bool(*)(SelectiveDataUpdateMaskSetting&,uintptr_t))func;
                    getResponse().getSelectiveDataUpdateMaskSettingMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
                case StartUpMessage::MSG_ID: {
                    StartUpMessage *r = static_cast<StartUpMessage*>(response);
                    bool(*f)(StartUpMessage&,uintptr_t) = (bool(*)(StartUpMessage&,uintptr_t))func;
                    getResponse().getStartUpMsg(*r);
                    if(!f || f(*r, data))
                        return 0;
                    break;
                }
            }
            // Call regular callbacks
            loopBottom();
        }
    } while (getMs() - start < timeout);
    return ANT_WAIT_TIMEOUT;
}

uint8_t BaseAntWithCallbacks::waitForStatus(uint8_t msgId, uint16_t timeout) {
    unsigned long start = getMs();
    do {
        if (loopTop()) {
            uint8_t status = matchStatus(msgId);
            if (status != 0xff)
                return status;

            // Call regular callbacks
            loopBottom();
        }
    } while (getMs() - start < timeout);
    return ANT_WAIT_TIMEOUT;
}
