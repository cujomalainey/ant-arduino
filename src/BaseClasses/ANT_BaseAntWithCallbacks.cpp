#include <BaseClasses/ANT_BaseAntWithCallbacks.h>

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
    // TODO make this a switch
    if (id == ACKNOWLEDGED_DATA) {
        AcknowledgedData response;
        getResponse().getAcknowledgedDataMsg(response);
        called = _onAcknowledgedData.call(response);
    } else if (id == ADVANCED_BURST_DATA) {
        AdvancedBurstData response;
        getResponse().getAdvancedBurstDataMsg(response);
        called = _onAdvancedBurstData.call(response);
    } else if (id == BROADCAST_DATA) {
        BroadcastData response;
        getResponse().getBroadcastDataMsg(response);
        called = _onBroadcastData.call(response);
    } else if (id == BURST_TRANSFER_DATA) {
        BurstTransferData response;
        getResponse().getBurstTransferDataMsg(response);
        called = _onBurstTransferData.call(response);
    } else if (id == ADVANCED_BURST_CAPABILITES) { // also ADVANCED_BURST_CONFIGURATION
        AdvancedBurstCapabilitiesConfiguration response;
        getResponse().getAdvancedBurstCapabilitiesConfigurationMsg(response);
        called = _onAdvancedBurstCapabilitiesConfiguration.call(response);
    } else if (id == ANT_VERSION) {
        AntVersion response;
        getResponse().getAntVersionMsg(response);
        called = _onAntVersion.call(response);
    } else if (id == CAPABILITIES) {
        Capabilities response;
        getResponse().getCapabilitiesMsg(response);
        called = _onCapabilities.call(response);
    } else if (id == CHANNEL_EVENT) { // also CHANNEL_RESPONSE
        ChannelEventResponse response;
        getResponse().getChannelEventResponseMsg(response);
        called = _onChannelEventResponse.call(response);
    } else if (id == CHANNEL_ID) {
        ChannelIdResponse response;
        getResponse().getChannelIdResponseMsg(response);
        called = _onChannelIdResponse.call(response);
    } else if (id == CHANNEL_STATUS) {
        ChannelStatus response;
        getResponse().getChannelStatusMsg(response);
        called = _onChannelStatus.call(response);
    } else if (id == ENCRYPTION_MODE_PARAMETERS) {
        EncryptionModeParameters response;
        getResponse().getEncryptionModeParametersMsg(response);
        called = _onEncryptionModeParameters.call(response);
    } else if (id == EVENT_FILTER) {
        EventFilter response;
        getResponse().getEventFilterMsg(response);
        called = _onEventFilter.call(response);
    } else if (id == SELECTIVE_DATA_UPDATE_MASK_SETTING) {
        SelectiveDataUpdateMaskSetting response;
        getResponse().getSelectiveDataUpdateMaskSettingMsg(response);
        called = _onSelectiveDataUpdateMaskSetting.call(response);
    } else if (id == START_UP_MESSAGE) {
        StartUpMessage response;
        getResponse().getStartUpMsg(response);
        called = _onStartUpMessage.call(response);
    }

    if (!called)
        _onOtherResponse.call(getResponse());
}

// uint8_t BaseAntWithCallbacks::matchStatus(uint8_t frameId) {
//     uint8_t id = getResponse().getMsgId();
//     uint8_t *data = getResponse().getData();
//     uint8_t len = getResponse().getFrameDataLength();
//     uint8_t offset = 0;

//     // Figure out if this frame has a frameId and if so, where the
//     // status byte to return is located
//     if (id == AT_COMMAND_RESPONSE)
//         offset = 3;
//     else if (id == REMOTE_AT_COMMAND_RESPONSE)
//         offset = 13;
//     else if (id == TX_STATUS_RESPONSE)
//         offset = 1;
//     else if (id == ZB_TX_STATUS_RESPONSE)
//         offset = 4;

//     // If this is an API frame that contains a status, the frame is
//     // long enough to contain it and the frameId matches the one
//     // given, return the status byte
//     if (offset && offset < len && data[0] == frameId)
//         return data[offset];
//     return 0xff;
// }

// uint8_t BaseAntWithCallbacks::waitForInternal(uint8_t apiId, void *response, uint16_t timeout, void *func, uintptr_t data, int16_t frameId) {
//     unsigned long start = millis();
//     do {
//         // Wait for a packet of the right type
//         if (loopTop()) {
//             if (frameId >= 0) {
//                 uint8_t status = matchStatus(frameId);
//                 // If a status was found, but it was not
//                 // a zero success status, stop waiting
//                 if (status != 0xff && status != 0)
//                     return status;
//             }

//             if (getResponse().getApiId() == apiId) {
//                 // If the type is right, call the right
//                 // conversion function based on the
//                 // ApiId and call the match function.
//                 // Because the match function is
//                 // essentially called in the same way,
//                 // regardless of the subclass used, the
//                 // compiler can reduce most of the below
//                 // mess into a single piece of code
//                 // (though for fully optimizing, the
//                 // separate getXxxResponse() methods
//                 // must be unified as well).
//                 switch(apiId) {
//                     case ZBTxStatusResponse::API_ID: {
//                         ZBTxStatusResponse *r = (ZBTxStatusResponse*)response;
//                         bool(*f)(ZBTxStatusResponse&,uintptr_t) = (bool(*)(ZBTxStatusResponse&,uintptr_t))func;
//                         getResponse().getZBTxStatusResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case ZBRxResponse::API_ID: {
//                         ZBRxResponse *r = (ZBRxResponse*)response;
//                         bool(*f)(ZBRxResponse&,uintptr_t) = (bool(*)(ZBRxResponse&,uintptr_t))func;
//                         getResponse().getZBRxResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case ZBExplicitRxResponse::API_ID: {
//                         ZBExplicitRxResponse *r = (ZBExplicitRxResponse*)response;
//                         bool(*f)(ZBExplicitRxResponse&,uintptr_t) = (bool(*)(ZBExplicitRxResponse&,uintptr_t))func;
//                         getResponse().getZBExplicitRxResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case ZBRxIoSampleResponse::API_ID: {
//                         ZBRxIoSampleResponse *r = (ZBRxIoSampleResponse*)response;
//                         bool(*f)(ZBRxIoSampleResponse&,uintptr_t) = (bool(*)(ZBRxIoSampleResponse&,uintptr_t))func;
//                         getResponse().getZBRxIoSampleResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case TxStatusResponse::API_ID: {
//                         TxStatusResponse *r = (TxStatusResponse*)response;
//                         bool(*f)(TxStatusResponse&,uintptr_t) = (bool(*)(TxStatusResponse&,uintptr_t))func;
//                         getResponse().getTxStatusResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case Rx16Response::API_ID: {
//                         Rx16Response *r = (Rx16Response*)response;
//                         bool(*f)(Rx16Response&,uintptr_t) = (bool(*)(Rx16Response&,uintptr_t))func;
//                         getResponse().getRx16Response(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case Rx64Response::API_ID: {
//                         Rx64Response *r = (Rx64Response*)response;
//                         bool(*f)(Rx64Response&,uintptr_t) = (bool(*)(Rx64Response&,uintptr_t))func;
//                         getResponse().getRx64Response(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case Rx16IoSampleResponse::API_ID: {
//                         Rx16IoSampleResponse *r = (Rx16IoSampleResponse*)response;
//                         bool(*f)(Rx16IoSampleResponse&,uintptr_t) = (bool(*)(Rx16IoSampleResponse&,uintptr_t))func;
//                         getResponse().getRx16IoSampleResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case Rx64IoSampleResponse::API_ID: {
//                         Rx64IoSampleResponse *r = (Rx64IoSampleResponse*)response;
//                         bool(*f)(Rx64IoSampleResponse&,uintptr_t) = (bool(*)(Rx64IoSampleResponse&,uintptr_t))func;
//                         getResponse().getRx64IoSampleResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case ModemStatusResponse::API_ID: {
//                         ModemStatusResponse *r = (ModemStatusResponse*)response;
//                         bool(*f)(ModemStatusResponse&,uintptr_t) = (bool(*)(ModemStatusResponse&,uintptr_t))func;
//                         getResponse().getModemStatusResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case AtCommandResponse::API_ID: {
//                         AtCommandResponse *r = (AtCommandResponse*)response;
//                         bool(*f)(AtCommandResponse&,uintptr_t) = (bool(*)(AtCommandResponse&,uintptr_t))func;
//                         getResponse().getAtCommandResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                     case RemoteAtCommandResponse::API_ID: {
//                         RemoteAtCommandResponse *r = (RemoteAtCommandResponse*)response;
//                         bool(*f)(RemoteAtCommandResponse&,uintptr_t) = (bool(*)(RemoteAtCommandResponse&,uintptr_t))func;
//                         getResponse().getRemoteAtCommandResponse(*r);
//                         if(!f || f(*r, data))
//                             return 0;
//                         break;
//                     }
//                 }
//             }
//             // Call regular callbacks
//             loopBottom();
//         }
//     } while (millis() - start < timeout);
//     return XBEE_WAIT_TIMEOUT;
// }

// uint8_t BaseAntWithCallbacks::waitForStatus(uint8_t frameId, uint16_t timeout) {
//     unsigned long start = millis();
//     do {
//         if (loopTop()) {
//             uint8_t status = matchStatus(frameId);
//             if (status != 0xff)
//                 return status;

//             // Call regular callbacks
//             loopBottom();
//         }
//     } while (millis() - start < timeout);
//     return XBEE_WAIT_TIMEOUT ;
// }