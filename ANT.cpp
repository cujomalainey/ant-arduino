/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of ANT-Arduino.
 *
 * ANT-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * ANT-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with ANT-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "ANT.h"

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "HardwareSerial.h"

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

uint8_t AntResponse::getFrameDataLength() {
	return _frameLength;
}

void AntResponse::setFrameLength(uint8_t frameLength) {
	_frameLength = frameLength;
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
	target.setFrameLength(getFrameDataLength());
	target.setLength(getLength());
}

ZBTxStatusResponse::ZBTxStatusResponse() : FrameIdResponse() {

}

uint16_t ZBTxStatusResponse::getRemoteAddress() {
	return  (getFrameData()[1] << 8) + getFrameData()[2];
}

uint8_t ZBTxStatusResponse::getTxRetryCount() {
	return getFrameData()[3];
}

uint8_t ZBTxStatusResponse::getDeliveryStatus() {
	return getFrameData()[4];
}

uint8_t ZBTxStatusResponse::getDiscoveryStatus() {
	return getFrameData()[5];
}

bool ZBTxStatusResponse::isSuccess() {
	return getDeliveryStatus() == SUCCESS;
}

void ANTResponse::getZBTxStatusResponse(ANTResponse &zbANTResponse) {

	// way off?
	ZBTxStatusResponse* zb = static_cast<ZBTxStatusResponse*>(&zbANTResponse);
	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(zbANTResponse);
}

ZBRxResponse::ZBRxResponse(): RxDataResponse() {
	_remoteAddress64 = ANTAddress64();
}

uint16_t ZBRxResponse::getRemoteAddress16() {
	return 	(getFrameData()[8] << 8) + getFrameData()[9];
}

uint8_t ZBRxResponse::getOption() {
	return getFrameData()[10];
}

// markers to read data from packet array.  this is the index, so the 12th item in the array
uint8_t ZBRxResponse::getDataOffset() {
	return 11;
}

uint8_t ZBRxResponse::getDataLength() {
	return getPacketLength() - getDataOffset() - 1;
}

ANTAddress64& ZBRxResponse::getRemoteAddress64() {
	return _remoteAddress64;
}

void ANTResponse::getZBRxResponse(ANTResponse &rxResponse) {

	ZBRxResponse* zb = static_cast<ZBRxResponse*>(&rxResponse);

	//TODO verify response api id matches this api for this response

	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(rxResponse);

	zb->getRemoteAddress64().setMsb((uint32_t(getFrameData()[0]) << 24) + (uint32_t(getFrameData()[1]) << 16) + (uint16_t(getFrameData()[2]) << 8) + getFrameData()[3]);
	zb->getRemoteAddress64().setLsb((uint32_t(getFrameData()[4]) << 24) + (uint32_t(getFrameData()[5]) << 16) + (uint16_t(getFrameData()[6]) << 8) + (getFrameData()[7]));
}

ZBExplicitRxResponse::ZBExplicitRxResponse(): ZBRxResponse() {
}

uint8_t ZBExplicitRxResponse::getSrcEndpoint() {
	return getFrameData()[10];
}

uint8_t ZBExplicitRxResponse::getDstEndpoint() {
	return getFrameData()[11];
}

uint16_t ZBExplicitRxResponse::getClusterId() {
	return (uint16_t)(getFrameData()[12]) << 8 | getFrameData()[13];
}

uint16_t ZBExplicitRxResponse::getProfileId() {
	return (uint16_t)(getFrameData()[14]) << 8 | getFrameData()[15];
}

uint8_t ZBExplicitRxResponse::getOption() {
	return getFrameData()[16];
}

// markers to read data from packet array.
uint8_t ZBExplicitRxResponse::getDataOffset() {
	return 17;
}

uint8_t ZBExplicitRxResponse::getDataLength() {
	return getPacketLength() - getDataOffset() - 1;
}

void ANTResponse::getZBExplicitRxResponse(ANTResponse &rxResponse) {
	// Nothing to add to that
	getZBRxResponse(rxResponse);
}


ZBRxIoSampleResponse::ZBRxIoSampleResponse() : ZBRxResponse() {

}

// 64 + 16 addresses, sample size, option = 12 (index 11), so this starts at 12
uint8_t ZBRxIoSampleResponse::getDigitalMaskMsb() {
	return getFrameData()[12] & 0x1c;
}

uint8_t ZBRxIoSampleResponse::getDigitalMaskLsb() {
	return getFrameData()[13];
}

uint8_t ZBRxIoSampleResponse::getAnalogMask() {
	return getFrameData()[14] & 0x8f;
}

bool ZBRxIoSampleResponse::containsAnalog() {
	return getAnalogMask() > 0;
}

bool ZBRxIoSampleResponse::containsDigital() {
	return getDigitalMaskMsb() > 0 || getDigitalMaskLsb() > 0;
}

bool ZBRxIoSampleResponse::isAnalogEnabled(uint8_t pin) {
	return ((getAnalogMask() >> pin) & 1) == 1;
}

bool ZBRxIoSampleResponse::isDigitalEnabled(uint8_t pin) {
	if (pin <= 7) {
		// added extra parens to calm avr compiler
		return ((getDigitalMaskLsb() >> pin) & 1) == 1;
	} else {
		return ((getDigitalMaskMsb() >> (pin - 8)) & 1) == 1;
	}
}

uint16_t ZBRxIoSampleResponse::getAnalog(uint8_t pin) {
	// analog starts 13 bytes after sample size, if no dio enabled
	uint8_t start = 15;

	if (containsDigital()) {
		// make room for digital i/o
		start+=2;
	}

	// start depends on how many pins before this pin are enabled
	for (int i = 0; i < pin; i++) {
		if (isAnalogEnabled(i)) {
			start+=2;
		}
	}

	return (uint16_t)((getFrameData()[start] << 8) + getFrameData()[start + 1]);
}

bool ZBRxIoSampleResponse::isDigitalOn(uint8_t pin) {
	if (pin <= 7) {
		// D0-7
		// DIO LSB is index 5
		return ((getFrameData()[16] >> pin) & 1) == 1;
	} else {
		// D10-12
		// DIO MSB is index 4
		return ((getFrameData()[15] >> (pin - 8)) & 1) == 1;
	}
}

void ANTResponse::getZBRxIoSampleResponse(ANTResponse &response) {
	ZBRxIoSampleResponse* zb = static_cast<ZBRxIoSampleResponse*>(&response);


	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(response);

	zb->getRemoteAddress64().setMsb((uint32_t(getFrameData()[0]) << 24) + (uint32_t(getFrameData()[1]) << 16) + (uint16_t(getFrameData()[2]) << 8) + getFrameData()[3]);
	zb->getRemoteAddress64().setLsb((uint32_t(getFrameData()[4]) << 24) + (uint32_t(getFrameData()[5]) << 16) + (uint16_t(getFrameData()[6]) << 8) + (getFrameData()[7]));
}

RemoteAtCommandResponse::RemoteAtCommandResponse() : AtCommandResponse() {

}

uint8_t* RemoteAtCommandResponse::getCommand() {
	return getFrameData() + 11;
}

uint8_t RemoteAtCommandResponse::getStatus() {
	return getFrameData()[13];
}

bool RemoteAtCommandResponse::isOk() {
	// weird c++ behavior.  w/o this method, it calls AtCommandResponse::isOk(), which calls the AtCommandResponse::getStatus, not this.getStatus!!!
	return getStatus() == AT_OK;
}

uint8_t RemoteAtCommandResponse::getValueLength() {
	return getFrameDataLength() - 14;
}

uint8_t* RemoteAtCommandResponse::getValue() {
	if (getValueLength() > 0) {
		// value is only included for query commands.  set commands does not return a value
		return getFrameData() + 14;
	}

	return NULL;
}

uint16_t RemoteAtCommandResponse::getRemoteAddress16() {
	return uint16_t((getFrameData()[9] << 8) + getFrameData()[10]);
}

ANTAddress64& RemoteAtCommandResponse::getRemoteAddress64() {
	return _remoteAddress64;
}

void ANTResponse::getRemoteAtCommandResponse(ANTResponse &response) {

	// TODO no real need to cast.  change arg to match expected class
	RemoteAtCommandResponse* at = static_cast<RemoteAtCommandResponse*>(&response);

	// pass pointer array to subclass
	at->setFrameData(getFrameData());
	setCommon(response);

	at->getRemoteAddress64().setMsb((uint32_t(getFrameData()[1]) << 24) + (uint32_t(getFrameData()[2]) << 16) + (uint16_t(getFrameData()[3]) << 8) + getFrameData()[4]);
	at->getRemoteAddress64().setLsb((uint32_t(getFrameData()[5]) << 24) + (uint32_t(getFrameData()[6]) << 16) + (uint16_t(getFrameData()[7]) << 8) + (getFrameData()[8]));

}

RxDataResponse::RxDataResponse() : ANTResponse() {

}

uint8_t RxDataResponse::getData(int index) {
	return getFrameData()[getDataOffset() + index];
}

uint8_t* RxDataResponse::getData() {
	return getFrameData() + getDataOffset();
}

FrameIdResponse::FrameIdResponse() {

}

uint8_t FrameIdResponse::getFrameId() {
	return getFrameData()[0];
}


ModemStatusResponse::ModemStatusResponse() {

}

uint8_t ModemStatusResponse::getStatus() {
	return getFrameData()[0];
}

void ANTResponse::getModemStatusResponse(ANTResponse &modemStatusResponse) {

	ModemStatusResponse* modem = static_cast<ModemStatusResponse*>(&modemStatusResponse);

	// pass pointer array to subclass
	modem->setFrameData(getFrameData());
	setCommon(modemStatusResponse);

}

AtCommandResponse::AtCommandResponse() {

}

uint8_t* AtCommandResponse::getCommand() {
	return getFrameData() + 1;
}

uint8_t AtCommandResponse::getStatus() {
	return getFrameData()[3];
}

uint8_t AtCommandResponse::getValueLength() {
	return getFrameDataLength() - 4;
}

uint8_t* AtCommandResponse::getValue() {
	if (getValueLength() > 0) {
		// value is only included for query commands.  set commands does not return a value
		return getFrameData() + 4;
	}

	return NULL;
}

bool AtCommandResponse::isOk() {
	return getStatus() == AT_OK;
}

void ANTResponse::getAtCommandResponse(ANTResponse &atCommandResponse) {

	AtCommandResponse* at = static_cast<AtCommandResponse*>(&atCommandResponse);

	// pass pointer array to subclass
	at->setFrameData(getFrameData());
	setCommon(atCommandResponse);
}

uint16_t ANTResponse::getPacketLength() {
	return ((_msbLength << 8) & 0xff) + (_lsbLength & 0xff);
}

uint8_t* ANTResponse::getFrameData() {
	return _frameDataPtr;
}

void ANTResponse::setFrameData(uint8_t* frameDataPtr) {
	_frameDataPtr = frameDataPtr;
}

void ANTResponse::init() {
	_complete = false;
	_errorCode = NO_ERROR;
	_checksum = 0;
}

void ANTResponse::reset() {
	init();
	_apiId = 0;
	_msbLength = 0;
	_lsbLength = 0;
	_checksum = 0;
	_frameLength = 0;

	_errorCode = NO_ERROR;
}

void ANT::resetResponse() {
	_pos = 0;
	_escape = false;
	_checksumTotal = 0;
	_response.reset();
}

ANT::ANT(): _response(ANTResponse()) {
        _pos = 0;
        _escape = false;
        _checksumTotal = 0;
        _nextFrameId = 0;

        _response.init();
        _response.setFrameData(_responseFrameData);
		// Contributed by Paul Stoffregen for Teensy support
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__)
        _serial = &Serial1;
#else
        _serial = &Serial;
#endif
}

uint8_t ANT::getNextFrameId() {

	_nextFrameId++;

	if (_nextFrameId == 0) {
		// can't send 0 because that disables status response
		_nextFrameId = 1;
	}

	return _nextFrameId;
}

// Support for SoftwareSerial. Contributed by Paul Stoffregen
void ANT::begin(Stream &serial) {
	_serial = &serial;
}

void ANT::setSerial(Stream &serial) {
	_serial = &serial;
}

bool ANT::available() {
	return _serial->available();
}

uint8_t ANT::read() {
	return _serial->read();
}

void ANT::write(uint8_t val) {
	_serial->write(val);
}

ANTResponse& ANT::getResponse() {
	return _response;
}

// TODO how to convert response to proper subclass?
void ANT::getResponse(ANTResponse &response) {

	response.setMsbLength(_response.getMsbLength());
	response.setLsbLength(_response.getLsbLength());
	response.setApiId(_response.getApiId());
	response.setFrameLength(_response.getFrameDataLength());

	response.setFrameData(_response.getFrameData());
}

void ANT::readPacketUntilAvailable() {
	while (!(getResponse().isAvailable() || getResponse().isError())) {
		// read some more
		readPacket();
	}
}

bool ANT::readPacket(int timeout) {

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

void ANT::readPacket() {
	// reset previous response
	if (_response.isAvailable() || _response.isError()) {
		// discard previous packet and start over
		resetResponse()
	}

    while (available()) {

        b = read();

		// checksum includes all bytes including the sync
		_checksumTotal^= b;

        switch(_pos) {
			case 0:
		        if (b == START_BYTE) {
		        	_pos++;
		        }

		        break;
			case 1:
				// length msb
				_response.setLength(b);
				_pos++;

				break;
			case 2:
				_response.setMsgId(b);
				_pos++;

				break;
			default:
				// starts at fifth byte

				if (_pos > MAX_FRAME_DATA_SIZE) {
					// exceed max size.  should never occur
					_response.setErrorCode(PACKET_EXCEEDS_BYTE_ARRAY_LENGTH);
					return;
				}

				// check if we're at the end of the packet
				if (_pos == (_response.getPacketLength())) {
					// verify checksum

					if (_checksumTotal == b) {
						_response.setChecksum(b);
						_response.setAvailable(true);

						_response.setErrorCode(NO_ERROR);
					} else {
						// checksum failed
						_response.setErrorCode(CHECKSUM_FAILURE);
					}

					// minus 4 because we start after start,length,msg and up to but not including checksum
					// e.g. if frame was one byte, _pos=4 would be the byte, pos=5 is the checksum, where end stop reading
					_response.setFrameLength(_pos - 3);

					// reset state vars
					_pos = 0;

					return;
				} else {
					// add to packet array, starting with the fourth byte of the msgId
					_response.getFrameData()[_pos - 3] = b;
					_pos++;
				}
        }
    }
}

// it's peanut butter jelly time!!

ANTRequest::ANTRequest(uint8_t apiId, uint8_t frameId) {
	_apiId = apiId;
	_frameId = frameId;
}

void ANTRequest::setFrameId(uint8_t frameId) {
	_frameId = frameId;
}

uint8_t ANTRequest::getFrameId() {
	return _frameId;
}

uint8_t ANTRequest::getMsgId() {
	return _apiId;
}

void ANTRequest::setApiId(uint8_t apiId) {
	_apiId = apiId;
}

//void ANTRequest::reset() {
//	_frameId = DEFAULT_FRAME_ID;
//}

//uint8_t ANTRequest::getPayloadOffset() {
//	return _payloadOffset;
//}
//
//uint8_t ANTRequest::setPayloadOffset(uint8_t payloadOffset) {
//	_payloadOffset = payloadOffset;
//}


PayloadRequest::PayloadRequest(uint8_t apiId, uint8_t frameId, uint8_t *payload, uint8_t payloadLength) : ANTRequest(apiId, frameId) {
	_payloadPtr = payload;
	_payloadLength = payloadLength;
}

uint8_t* PayloadRequest::getPayload() {
	return _payloadPtr;
}

void PayloadRequest::setPayload(uint8_t* payload) {
	_payloadPtr = payload;
}

uint8_t PayloadRequest::getPayloadLength() {
	return _payloadLength;
}

void PayloadRequest::setPayloadLength(uint8_t payloadLength) {
	_payloadLength = payloadLength;
}

ZBTxRequest::ZBTxRequest() : PayloadRequest(ZB_TX_REQUEST, DEFAULT_FRAME_ID, NULL, 0) {
	_addr16 = ZB_BROADCAST_ADDRESS;
	_broadcastRadius = ZB_BROADCAST_RADIUS_MAX_HOPS;
	_option = ZB_TX_UNICAST;
}

ZBTxRequest::ZBTxRequest(const ANTAddress64 &addr64, uint16_t addr16, uint8_t broadcastRadius, uint8_t option, uint8_t *data, uint8_t dataLength, uint8_t frameId): PayloadRequest(ZB_TX_REQUEST, frameId, data, dataLength) {
	_addr64 = addr64;
	_addr16 = addr16;
	_broadcastRadius = broadcastRadius;
	_option = option;
}

ZBTxRequest::ZBTxRequest(const ANTAddress64 &addr64, uint8_t *data, uint8_t dataLength): PayloadRequest(ZB_TX_REQUEST, DEFAULT_FRAME_ID, data, dataLength) {
	_addr64 = addr64;
	_addr16 = ZB_BROADCAST_ADDRESS;
	_broadcastRadius = ZB_BROADCAST_RADIUS_MAX_HOPS;
	_option = ZB_TX_UNICAST;
}

uint8_t ZBTxRequest::getFrameData(uint8_t pos) {
	if (pos == 0) {
		return (_addr64.getMsb() >> 24) & 0xff;
	} else if (pos == 1) {
		return (_addr64.getMsb() >> 16) & 0xff;
	} else if (pos == 2) {
		return (_addr64.getMsb() >> 8) & 0xff;
	} else if (pos == 3) {
		return _addr64.getMsb() & 0xff;
	} else if (pos == 4) {
		return (_addr64.getLsb() >> 24) & 0xff;
	} else if (pos == 5) {
		return  (_addr64.getLsb() >> 16) & 0xff;
	} else if (pos == 6) {
		return (_addr64.getLsb() >> 8) & 0xff;
	} else if (pos == 7) {
		return _addr64.getLsb() & 0xff;
	} else if (pos == 8) {
		return (_addr16 >> 8) & 0xff;
	} else if (pos == 9) {
		return _addr16 & 0xff;
	} else if (pos == 10) {
		return _broadcastRadius;
	} else if (pos == 11) {
		return _option;
	} else {
		return getPayload()[pos - ZB_TX_API_LENGTH];
	}
}

uint8_t ZBTxRequest::getFrameDataLength() {
	return ZB_TX_API_LENGTH + getPayloadLength();
}

ANTAddress64& ZBTxRequest::getAddress64() {
	return _addr64;
}

uint16_t ZBTxRequest::getAddress16() {
	return _addr16;
}

uint8_t ZBTxRequest::getBroadcastRadius() {
	return _broadcastRadius;
}

uint8_t ZBTxRequest::getOption() {
	return _option;
}

void ZBTxRequest::setAddress64(const ANTAddress64& addr64) {
	_addr64 = addr64;
}

void ZBTxRequest::setAddress16(uint16_t addr16) {
	_addr16 = addr16;
}

void ZBTxRequest::setBroadcastRadius(uint8_t broadcastRadius) {
	_broadcastRadius = broadcastRadius;
}

void ZBTxRequest::setOption(uint8_t option) {
	_option = option;
}



ZBExplicitTxRequest::ZBExplicitTxRequest() : ZBTxRequest() {
	_srcEndpoint = DEFAULT_ENDPOINT;
	_dstEndpoint = DEFAULT_ENDPOINT;
	_profileId = DEFAULT_PROFILE_ID;
	_clusterId = DEFAULT_CLUSTER_ID;
	setApiId(ZB_EXPLICIT_TX_REQUEST);
}

ZBExplicitTxRequest::ZBExplicitTxRequest(ANTAddress64 &addr64, uint16_t addr16, uint8_t broadcastRadius, uint8_t option, uint8_t *payload, uint8_t payloadLength, uint8_t frameId, uint8_t srcEndpoint, uint8_t dstEndpoint, uint16_t clusterId, uint16_t profileId)
: ZBTxRequest(addr64, addr16, broadcastRadius, option, payload, payloadLength, frameId) {
	_srcEndpoint = srcEndpoint;
	_dstEndpoint = dstEndpoint;
	_profileId = profileId;
	_clusterId = clusterId;
	setApiId(ZB_EXPLICIT_TX_REQUEST);
}

ZBExplicitTxRequest::ZBExplicitTxRequest(ANTAddress64 &addr64, uint8_t *payload, uint8_t payloadLength)
: ZBTxRequest(addr64, payload, payloadLength) {
	_srcEndpoint = DEFAULT_ENDPOINT;
	_dstEndpoint = DEFAULT_ENDPOINT;
	_profileId = DEFAULT_PROFILE_ID;
	_clusterId = DEFAULT_CLUSTER_ID;
	setApiId(ZB_EXPLICIT_TX_REQUEST);
}

uint8_t ZBExplicitTxRequest::getFrameData(uint8_t pos) {
	if (pos < 10) {
		return ZBTxRequest::getFrameData(pos);
	} else if (pos == 10) {
		return _srcEndpoint;
	} else if (pos == 11) {
		return _dstEndpoint;
	} else if (pos == 12) {
		return (_clusterId >> 8) & 0xff;
	} else if (pos == 13) {
		return _clusterId & 0xff;
	} else if (pos == 14) {
		return (_profileId >> 8) & 0xff;
	} else if (pos == 15) {
		return _profileId & 0xff;
	} else if (pos == 16) {
		return _broadcastRadius;
	} else if (pos == 17) {
		return _option;
	} else {
		return getPayload()[pos - ZB_EXPLICIT_TX_API_LENGTH];
	}
}

uint8_t ZBExplicitTxRequest::getFrameDataLength() {
	return ZB_EXPLICIT_TX_API_LENGTH + getPayloadLength();
}

uint8_t ZBExplicitTxRequest::getSrcEndpoint() {
	return _srcEndpoint;
}

uint8_t ZBExplicitTxRequest::getDstEndpoint() {
	return _dstEndpoint;
}

uint16_t ZBExplicitTxRequest::getClusterId() {
	return _clusterId;
}

uint16_t ZBExplicitTxRequest::getProfileId() {
	return _profileId;
}

void ZBExplicitTxRequest::setSrcEndpoint(uint8_t endpoint) {
	_srcEndpoint = endpoint;
}

void ZBExplicitTxRequest::setDstEndpoint(uint8_t endpoint) {
	_dstEndpoint = endpoint;
}

void ZBExplicitTxRequest::setClusterId(uint16_t clusterId) {
	_clusterId = clusterId;
}

void ZBExplicitTxRequest::setProfileId(uint16_t profileId) {
	_profileId = profileId;
}

AtCommandRequest::AtCommandRequest() : ANTRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = NULL;
	clearCommandValue();
}

AtCommandRequest::AtCommandRequest(uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : ANTRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = command;
	_commandValue = commandValue;
	_commandValueLength = commandValueLength;
}

AtCommandRequest::AtCommandRequest(uint8_t *command) : ANTRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = command;
	clearCommandValue();
}

uint8_t* AtCommandRequest::getCommand() {
	return _command;
}

uint8_t* AtCommandRequest::getCommandValue() {
	return _commandValue;
}

uint8_t AtCommandRequest::getCommandValueLength() {
	return _commandValueLength;
}

void AtCommandRequest::setCommand(uint8_t* command) {
	_command = command;
}

void AtCommandRequest::setCommandValue(uint8_t* value) {
	_commandValue = value;
}

void AtCommandRequest::setCommandValueLength(uint8_t length) {
	_commandValueLength = length;
}

uint8_t AtCommandRequest::getFrameData(uint8_t pos) {

	if (pos == 0) {
		return _command[0];
	} else if (pos == 1) {
		return _command[1];
	} else {
		return _commandValue[pos - AT_COMMAND_API_LENGTH];
	}
}

void AtCommandRequest::clearCommandValue() {
	_commandValue = NULL;
	_commandValueLength = 0;
}

//void AtCommandRequest::reset() {
//	 ANTRequest::reset();
//}

uint8_t AtCommandRequest::getFrameDataLength() {
	// command is 2 byte + length of value
	return AT_COMMAND_API_LENGTH + _commandValueLength;
}

ANTAddress64 RemoteAtCommandRequest::broadcastAddress64 = ANTAddress64(0x0, BROADCAST_ADDRESS);

RemoteAtCommandRequest::RemoteAtCommandRequest() : AtCommandRequest(NULL, NULL, 0) {
	_remoteAddress16 = 0;
	_applyChanges = false;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AtCommandRequest(command, commandValue, commandValueLength) {
	_remoteAddress64 = broadcastAddress64;
	_remoteAddress16 = remoteAddress16;
	_applyChanges = true;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command) : AtCommandRequest(command, NULL, 0) {
	_remoteAddress64 = broadcastAddress64;
	_remoteAddress16 = remoteAddress16;
	_applyChanges = false;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(ANTAddress64 &remoteAddress64, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AtCommandRequest(command, commandValue, commandValueLength) {
	_remoteAddress64 = remoteAddress64;
	// don't worry.. works for series 1 too!
	_remoteAddress16 = ZB_BROADCAST_ADDRESS;
	_applyChanges = true;
	setApiId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(ANTAddress64 &remoteAddress64, uint8_t *command) : AtCommandRequest(command, NULL, 0) {
	_remoteAddress64 = remoteAddress64;
	_remoteAddress16 = ZB_BROADCAST_ADDRESS;
	_applyChanges = false;
	setApiId(REMOTE_AT_REQUEST);
}

uint16_t RemoteAtCommandRequest::getRemoteAddress16() {
	return _remoteAddress16;
}

void RemoteAtCommandRequest::setRemoteAddress16(uint16_t remoteAddress16) {
	_remoteAddress16 = remoteAddress16;
}

ANTAddress64& RemoteAtCommandRequest::getRemoteAddress64() {
	return _remoteAddress64;
}

void RemoteAtCommandRequest::setRemoteAddress64(ANTAddress64 &remoteAddress64) {
	_remoteAddress64 = remoteAddress64;
}

bool RemoteAtCommandRequest::getApplyChanges() {
	return _applyChanges;
}

void RemoteAtCommandRequest::setApplyChanges(bool applyChanges) {
	_applyChanges = applyChanges;
}


uint8_t RemoteAtCommandRequest::getFrameData(uint8_t pos) {
	if (pos == 0) {
		return (_remoteAddress64.getMsb() >> 24) & 0xff;
	} else if (pos == 1) {
		return (_remoteAddress64.getMsb() >> 16) & 0xff;
	} else if (pos == 2) {
		return (_remoteAddress64.getMsb() >> 8) & 0xff;
	} else if (pos == 3) {
		return _remoteAddress64.getMsb() & 0xff;
	} else if (pos == 4) {
		return (_remoteAddress64.getLsb() >> 24) & 0xff;
	} else if (pos == 5) {
		return (_remoteAddress64.getLsb() >> 16) & 0xff;
	} else if (pos == 6) {
		return(_remoteAddress64.getLsb() >> 8) & 0xff;
	} else if (pos == 7) {
		return _remoteAddress64.getLsb() & 0xff;
	} else if (pos == 8) {
		return (_remoteAddress16 >> 8) & 0xff;
	} else if (pos == 9) {
		return _remoteAddress16 & 0xff;
	} else if (pos == 10) {
		return _applyChanges ? 2: 0;
	} else if (pos == 11) {
		return getCommand()[0];
	} else if (pos == 12) {
		return getCommand()[1];
	} else {
		return getCommandValue()[pos - REMOTE_AT_COMMAND_API_LENGTH];
	}
}

uint8_t RemoteAtCommandRequest::getFrameDataLength() {
	return REMOTE_AT_COMMAND_API_LENGTH + getCommandValueLength();
}


// TODO
//GenericRequest::GenericRequest(uint8_t* frame, uint8_t len, uint8_t apiId): ANTRequest(apiId, *(frame), len) {
//	_frame = frame;
//}

void ANT::send(ANTRequest &request) {
	// the new new deal

	sendByte(START_BYTE, false);

	// send length
	uint8_t msbLen = ((request.getFrameDataLength() + 2) >> 8) & 0xff;
	uint8_t lsbLen = (request.getFrameDataLength() + 2) & 0xff;

	sendByte(msbLen, true);
	sendByte(lsbLen, true);

	// api id
	sendByte(request.getApiId(), true);
	sendByte(request.getFrameId(), true);

	uint8_t checksum = 0;

	// compute checksum, start at api id
	checksum+= request.getApiId();
	checksum+= request.getFrameId();

	for (int i = 0; i < request.getFrameDataLength(); i++) {
		sendByte(request.getFrameData(i), true);
		checksum+= request.getFrameData(i);
	}

	// perform 2s complement
	checksum = 0xff - checksum;

	// send checksum
	sendByte(checksum, true);
}

void ANT::sendByte(uint8_t b, bool escape) {

	if (escape && (b == START_BYTE || b == ESCAPE || b == XON || b == XOFF)) {
		write(ESCAPE);
		write(b ^ 0x20);
	} else {
		write(b);
	}
}


void ANTWithCallbacks::loop() {
	if (loopTop())
		loopBottom();
}

bool ANTWithCallbacks::loopTop() {
	readPacket();
	if (getResponse().isAvailable()) {
		_onResponse.call(getResponse());
		return true;
	} else if (getResponse().isError()) {
		_onPacketError.call(getResponse().getErrorCode());
	}
	return false;
}

void ANTWithCallbacks::loopBottom() {
	bool called = false;
	uint8_t id = getResponse().getApiId();

	if (id == ZB_TX_STATUS_RESPONSE) {
		ZBTxStatusResponse response;
		getResponse().getZBTxStatusResponse(response);
		called = _onZBTxStatusResponse.call(response);
	} else if (id == ZB_RX_RESPONSE) {
		ZBRxResponse response;
		getResponse().getZBRxResponse(response);
		called = _onZBRxResponse.call(response);
	} else if (id == ZB_EXPLICIT_RX_RESPONSE) {
		ZBExplicitRxResponse response;
		getResponse().getZBExplicitRxResponse(response);
		called = _onZBExplicitRxResponse.call(response);
	} else if (id == ZB_IO_SAMPLE_RESPONSE) {
		ZBRxIoSampleResponse response;
		getResponse().getZBRxIoSampleResponse(response);
		called = _onZBRxIoSampleResponse.call(response);
	} else if (id == TX_STATUS_RESPONSE) {
		TxStatusResponse response;
		getResponse().getTxStatusResponse(response);
		called = _onTxStatusResponse.call(response);
	} else if (id == RX_16_RESPONSE) {
		Rx16Response response;
		getResponse().getRx16Response(response);
		called = _onRx16Response.call(response);
	} else if (id == RX_64_RESPONSE) {
		Rx64Response response;
		getResponse().getRx64Response(response);
		called = _onRx64Response.call(response);
	} else if (id == RX_16_IO_RESPONSE) {
		Rx16IoSampleResponse response;
		getResponse().getRx16IoSampleResponse(response);
		called = _onRx16IoSampleResponse.call(response);
	} else if (id == RX_64_IO_RESPONSE) {
		Rx64IoSampleResponse response;
		getResponse().getRx64IoSampleResponse(response);
		called = _onRx64IoSampleResponse.call(response);
	} else if (id == MODEM_STATUS_RESPONSE) {
		ModemStatusResponse response;
		getResponse().getModemStatusResponse(response);
		called = _onModemStatusResponse.call(response);
	} else if (id == AT_COMMAND_RESPONSE) {
		AtCommandResponse response;
		getResponse().getAtCommandResponse(response);
		called = _onAtCommandResponse.call(response);
	} else if (id == REMOTE_AT_COMMAND_RESPONSE) {
		RemoteAtCommandResponse response;
		getResponse().getRemoteAtCommandResponse(response);
		called = _onRemoteAtCommandResponse.call(response);
	}

	if (!called)
		_onOtherResponse.call(getResponse());
}

uint8_t ANTWithCallbacks::matchStatus(uint8_t frameId) {
	uint8_t id = getResponse().getApiId();
	uint8_t *data = getResponse().getFrameData();
	uint8_t len = getResponse().getFrameDataLength();
	uint8_t offset = 0;

	// Figure out if this frame has a frameId and if so, where the
	// status byte to return is located
	if (id == AT_COMMAND_RESPONSE)
		offset = 3;
	else if (id == REMOTE_AT_COMMAND_RESPONSE)
		offset = 13;
	else if (id == TX_STATUS_RESPONSE)
		offset = 1;
	else if (id == ZB_TX_STATUS_RESPONSE)
		offset = 4;

	// If this is an API frame that contains a status, the frame is
	// long enough to contain it and the frameId matches the one
	// given, return the status byte
	if (offset && offset < len && data[0] == frameId)
		return data[offset];
	return 0xff;
}

uint8_t ANTWithCallbacks::waitForInternal(uint8_t apiId, void *response, uint16_t timeout, void *func, uintptr_t data, int16_t frameId) {
	unsigned long start = millis();
	do {
		// Wait for a packet of the right type
		if (loopTop()) {
			if (frameId >= 0) {
				uint8_t status = matchStatus(frameId);
				// If a status was found, but it was not
				// a zero success status, stop waiting
				if (status != 0xff && status != 0)
					return status;
			}

			if (getResponse().getApiId() == apiId) {
				// If the type is right, call the right
				// conversion function based on the
				// ApiId and call the match function.
				// Because the match function is
				// essentially called in the same way,
				// regardless of the subclass used, the
				// compiler can reduce most of the below
				// mess into a single piece of code
				// (though for fully optimizing, the
				// separate getXxxResponse() methods
				// must be unified as well).
				switch(apiId) {
					case ZBTxStatusResponse::API_ID: {
						ZBTxStatusResponse *r = (ZBTxStatusResponse*)response;
						bool(*f)(ZBTxStatusResponse&,uintptr_t) = (bool(*)(ZBTxStatusResponse&,uintptr_t))func;
						getResponse().getZBTxStatusResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case ZBRxResponse::API_ID: {
						ZBRxResponse *r = (ZBRxResponse*)response;
						bool(*f)(ZBRxResponse&,uintptr_t) = (bool(*)(ZBRxResponse&,uintptr_t))func;
						getResponse().getZBRxResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case ZBExplicitRxResponse::API_ID: {
						ZBExplicitRxResponse *r = (ZBExplicitRxResponse*)response;
						bool(*f)(ZBExplicitRxResponse&,uintptr_t) = (bool(*)(ZBExplicitRxResponse&,uintptr_t))func;
						getResponse().getZBExplicitRxResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case ZBRxIoSampleResponse::API_ID: {
						ZBRxIoSampleResponse *r = (ZBRxIoSampleResponse*)response;
						bool(*f)(ZBRxIoSampleResponse&,uintptr_t) = (bool(*)(ZBRxIoSampleResponse&,uintptr_t))func;
						getResponse().getZBRxIoSampleResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case TxStatusResponse::API_ID: {
						TxStatusResponse *r = (TxStatusResponse*)response;
						bool(*f)(TxStatusResponse&,uintptr_t) = (bool(*)(TxStatusResponse&,uintptr_t))func;
						getResponse().getTxStatusResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case Rx16Response::API_ID: {
						Rx16Response *r = (Rx16Response*)response;
						bool(*f)(Rx16Response&,uintptr_t) = (bool(*)(Rx16Response&,uintptr_t))func;
						getResponse().getRx16Response(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case Rx64Response::API_ID: {
						Rx64Response *r = (Rx64Response*)response;
						bool(*f)(Rx64Response&,uintptr_t) = (bool(*)(Rx64Response&,uintptr_t))func;
						getResponse().getRx64Response(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case Rx16IoSampleResponse::API_ID: {
						Rx16IoSampleResponse *r = (Rx16IoSampleResponse*)response;
						bool(*f)(Rx16IoSampleResponse&,uintptr_t) = (bool(*)(Rx16IoSampleResponse&,uintptr_t))func;
						getResponse().getRx16IoSampleResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case Rx64IoSampleResponse::API_ID: {
						Rx64IoSampleResponse *r = (Rx64IoSampleResponse*)response;
						bool(*f)(Rx64IoSampleResponse&,uintptr_t) = (bool(*)(Rx64IoSampleResponse&,uintptr_t))func;
						getResponse().getRx64IoSampleResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case ModemStatusResponse::API_ID: {
						ModemStatusResponse *r = (ModemStatusResponse*)response;
						bool(*f)(ModemStatusResponse&,uintptr_t) = (bool(*)(ModemStatusResponse&,uintptr_t))func;
						getResponse().getModemStatusResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case AtCommandResponse::API_ID: {
						AtCommandResponse *r = (AtCommandResponse*)response;
						bool(*f)(AtCommandResponse&,uintptr_t) = (bool(*)(AtCommandResponse&,uintptr_t))func;
						getResponse().getAtCommandResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
					case RemoteAtCommandResponse::API_ID: {
						RemoteAtCommandResponse *r = (RemoteAtCommandResponse*)response;
						bool(*f)(RemoteAtCommandResponse&,uintptr_t) = (bool(*)(RemoteAtCommandResponse&,uintptr_t))func;
						getResponse().getRemoteAtCommandResponse(*r);
						if(!f || f(*r, data))
							return 0;
						break;
					}
				}
			}
			// Call regular callbacks
			loopBottom();
		}
	} while (millis() - start < timeout);
	return XBEE_WAIT_TIMEOUT;
}

uint8_t ANTWithCallbacks::waitForStatus(uint8_t frameId, uint16_t timeout) {
	unsigned long start = millis();
	do {
		if (loopTop()) {
			uint8_t status = matchStatus(frameId);
			if (status != 0xff)
				return status;

			// Call regular callbacks
			loopBottom();
		}
	} while (millis() - start < timeout);
	return XBEE_WAIT_TIMEOUT ;
}

