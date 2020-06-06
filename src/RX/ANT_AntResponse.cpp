#include <RX/ANT_AntResponse.h>
#include <RX/ANT_messages.h>

#include <ANT_private_defines.h>


AntResponse::AntResponse() {

}

uint8_t AntResponse::getMsgId() {
    return _msgId;
}

void AntResponse::setMsgId(uint8_t msgId) {
    _msgId = msgId;
}

uint8_t AntResponse::getLength() {
    return _length;
}

void AntResponse::setLength(uint8_t length) {
    _length = length;
}

uint8_t AntResponse::getChecksum() {
    return _checksum;
}

void AntResponse::setChecksum(uint8_t checksum) {
    _checksum = checksum;
}

uint8_t AntResponse::getPacketLength() {
    return _length - ANT_MSG_OVERHEAD_LENGTH;
}

bool AntResponse::isAvailable() {
    return _complete;
}

void AntResponse::setAvailable(bool complete) {
    _complete = complete;
}

bool AntResponse::isError() {
    return _errorCode > 0;
}

uint8_t AntResponse::getErrorCode() {
    return _errorCode;
}

void AntResponse::setErrorCode(uint8_t errorCode) {
    _errorCode = errorCode;
}

// copy common fields from xbee response to target response
void AntResponse::setCommon(AntResponse &target) {
    target.setMsgId(getMsgId());
    target.setAvailable(isAvailable());
    target.setChecksum(getChecksum());
    target.setErrorCode(getErrorCode());
    target.setLength(getLength());
}

void AntResponse::getStartUpMsg(AntResponse &response) {
    StartUpMessage* startUpMsg = static_cast<StartUpMessage*>(&response);
    // pass pointer array to subclass
    startUpMsg->setFrameData(getFrameData());
    setCommon(response);
}

void AntResponse::getBroadcastDataMsg(AntResponse &rxResponse) {
    BroadcastData* bdm = static_cast<BroadcastData*>(&rxResponse);

    // pass pointer array to subclass
    bdm->setFrameData(getFrameData());
    setCommon(rxResponse);
}

void AntResponse::getAntVersionMsg(AntResponse &response) {
    AntVersion* av = static_cast<AntVersion*>(&response);

    // pass pointer array to subclass
    av->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getCapabilitiesMsg(AntResponse &response) {
    Capabilities* cap = static_cast<Capabilities*>(&response);

    // pass pointer array to subclass
    cap->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getAdvancedBurstDataMsg(AntResponse &response) {
    AdvancedBurstData* abd = static_cast<AdvancedBurstData*>(&response);

    // pass pointer array to subclass
    abd->setFrameData(getFrameData());
    setCommon(response);
}

void AntResponse::getAdvancedBurstCapabilitiesConfigurationMsg(AntResponse &response) {
    AdvancedBurstCapabilitiesConfiguration* abc = static_cast<AdvancedBurstCapabilitiesConfiguration*>(&response);

    // pass pointer array to subclass
    abc->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getChannelEventResponseMsg(AntResponse &response) {
    ChannelEventResponse* cer = static_cast<ChannelEventResponse*>(&response);

    // pass pointer array to subclass
    cer->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getChannelIdResponseMsg(AntResponse &response) {
    ChannelIdResponse* cid = static_cast<ChannelIdResponse*>(&response);

    // pass pointer array to subclass
    cid->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getChannelStatusMsg(AntResponse &response) {
    ChannelStatus* csm = static_cast<ChannelStatus*>(&response);

    // pass pointer array to subclass
    csm->setFrameData(getFrameData());
    setCommon(response);
}

void AntResponse::getAcknowledgedDataMsg(AntResponse &response) {
    AcknowledgedData* ackData = static_cast<AcknowledgedData*>(&response);

    // pass pointer array to subclass
    ackData->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getSelectiveDataUpdateMaskSettingMsg(AntResponse &response) {
    SelectiveDataUpdateMaskSetting* sdums = static_cast<SelectiveDataUpdateMaskSetting*>(&response);

    // pass pointer array to subclass
    sdums->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getEncryptionModeParametersMsg(AntResponse &response) {
    EncryptionModeParameters* emp = static_cast<EncryptionModeParameters*>(&response);

    // pass pointer array to subclass
    emp->setFrameData(getFrameData());
    setCommon(response);
}

void AntResponse::getEventFilterMsg(AntResponse &response) {
    EventFilter* evm = static_cast<EventFilter*>(&response);

    // pass pointer array to subclass
    evm->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getBurstTransferDataMsg(AntResponse &burstDataResponse) {
    BurstTransferData* burstData = static_cast<BurstTransferData*>(&burstDataResponse);

    // pass pointer array to subclass
    burstData->setFrameData(getFrameData());
    setCommon(burstDataResponse);
}

uint8_t* AntResponse::getFrameData() {
    return _frameDataPtr;
}

void AntResponse::setFrameData(uint8_t* frameDataPtr) {
    _frameDataPtr = frameDataPtr;
}

void AntResponse::init() {
    _complete = false;
    _errorCode = NO_ERROR;
    _checksum = 0;
}

void AntResponse::reset() {
    init();
    _msgId = 0;
    _length = 0;
    _checksum = 0;

    _errorCode = NO_ERROR;
}
