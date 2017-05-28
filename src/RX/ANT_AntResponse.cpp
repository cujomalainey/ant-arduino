#include <RX/ANT_AntResponse.h>

#include <ANT_private_defines.h>

#include <RX/Data/ANT_AcknowledgedData.h>
#include <RX/Data/ANT_BroadcastData.h>
#include <RX/Data/ANT_BurstTransferData.h>
#include <RX/Status/ANT_AdvancedBurstCapabilitiesConfiguration.h>
#include <RX/Status/ANT_AntVersion.h>
#include <RX/Status/ANT_Capabilities.h>
#include <RX/Status/ANT_ChannelEventResponse.h>
#include <RX/Status/ANT_StartUpMessage.h>

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

    // way off?
    StartUpMessage* startUpMsg = static_cast<StartUpMessage*>(&response);
    // pass pointer array to subclass
    startUpMsg->setFrameData(getFrameData());
    setCommon(response);
}

void AntResponse::getBroadcastDataMsg(AntResponse &rxResponse) {

    BroadcastData* ant = static_cast<BroadcastData*>(&rxResponse);

    //TODO verify response msg id matches this msg for this response

    // pass pointer array to subclass
    ant->setFrameData(getFrameData());
    setCommon(rxResponse);
}

void AntResponse::getAntVersionMsg(AntResponse &response) {

    // TODO no real need to cast.  change arg to match expected class
    AntVersion* av = static_cast<AntVersion*>(&response);

    // pass pointer array to subclass
    av->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getCapabilitiesMsg(AntResponse &response) {

    // TODO no real need to cast.  change arg to match expected class
    Capabilities* cap = static_cast<Capabilities*>(&response);

    // pass pointer array to subclass
    cap->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getAdvancedBurstCapabilitiesConfigurationMsg(AntResponse &response) {

    // TODO no real need to cast.  change arg to match expected class
    AdvancedBurstCapabilitiesConfiguration* abc = static_cast<AdvancedBurstCapabilitiesConfiguration*>(&response);

    // pass pointer array to subclass
    abc->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getChannelEventResponseMsg(AntResponse &response) {

    // TODO no real need to cast.  change arg to match expected class
    ChannelEventResponse* cer = static_cast<ChannelEventResponse*>(&response);

    // pass pointer array to subclass
    cer->setFrameData(getFrameData());
    setCommon(response);

}

void AntResponse::getAcknowledgedDataMsg(AntResponse &ackDataResponse) {

    AcknowledgedData* ackData = static_cast<AcknowledgedData*>(&ackDataResponse);

    // pass pointer array to subclass
    ackData->setFrameData(getFrameData());
    setCommon(ackDataResponse);

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