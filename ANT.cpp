/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 *
 * This file is part of Ant-Arduino.
 *
 * Ant-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ant-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRAntY; without even the implied warranty of
 * MERCHAntABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ant-Arduino.  If not, see <http://www.gnu.org/licenses/>.
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

void AntResponse::getZBTxStatusResponse(AntResponse &zbAntResponse) {

	// way off?
	ZBTxStatusResponse* zb = static_cast<ZBTxStatusResponse*>(&zbAntResponse);
	// pass pointer array to subclass
	zb->setFrameData(getFrameData());
	setCommon(zbAntResponse);
}

ZBRxResponse::ZBRxResponse(): RxDataResponse() {
	_remoteAddress64 = AntAddress64();
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

AntAddress64& ZBRxResponse::getRemoteAddress64() {
	return _remoteAddress64;
}

void AntResponse::getZBRxResponse(AntResponse &rxResponse) {

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

void AntResponse::getZBExplicitRxResponse(AntResponse &rxResponse) {
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

void AntResponse::getZBRxIoSampleResponse(AntResponse &response) {
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

AntAddress64& RemoteAtCommandResponse::getRemoteAddress64() {
	return _remoteAddress64;
}

void AntResponse::getRemoteAtCommandResponse(AntResponse &response) {

	// TODO no real need to cast.  change arg to match expected class
	RemoteAtCommandResponse* at = static_cast<RemoteAtCommandResponse*>(&response);

	// pass pointer array to subclass
	at->setFrameData(getFrameData());
	setCommon(response);

	at->getRemoteAddress64().setMsb((uint32_t(getFrameData()[1]) << 24) + (uint32_t(getFrameData()[2]) << 16) + (uint16_t(getFrameData()[3]) << 8) + getFrameData()[4]);
	at->getRemoteAddress64().setLsb((uint32_t(getFrameData()[5]) << 24) + (uint32_t(getFrameData()[6]) << 16) + (uint16_t(getFrameData()[7]) << 8) + (getFrameData()[8]));

}

RxDataResponse::RxDataResponse() : AntResponse() {

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

void AntResponse::getModemStatusResponse(AntResponse &modemStatusResponse) {

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

void AntResponse::getAtCommandResponse(AntResponse &atCommandResponse) {

	AtCommandResponse* at = static_cast<AtCommandResponse*>(&atCommandResponse);

	// pass pointer array to subclass
	at->setFrameData(getFrameData());
	setCommon(atCommandResponse);
}

uint16_t AntResponse::getPacketLength() {
	return _length & 0xff;
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
	_frameLength = 0;

	_errorCode = NO_ERROR;
}

void Ant::resetResponse() {
	_pos = 0;
	_escape = false;
	_checksumTotal = 0;
	_response.reset();
}

Ant::Ant(): _response(AntResponse()) {
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

uint8_t Ant::getNextFrameId() {

	_nextFrameId++;

	if (_nextFrameId == 0) {
		// can't send 0 because that disables status response
		_nextFrameId = 1;
	}

	return _nextFrameId;
}

// Support for SoftwareSerial. Contributed by Paul Stoffregen
void Ant::begin(Stream &serial) {
	_serial = &serial;
}

void Ant::setSerial(Stream &serial) {
	_serial = &serial;
}

bool Ant::available() {
	return _serial->available();
}

uint8_t Ant::read() {
	return _serial->read();
}

void Ant::write(uint8_t val) {
	_serial->write(val);
}

AntResponse& Ant::getResponse() {
	return _response;
}

// TODO how to convert response to proper subclass?
void Ant::getResponse(AntResponse &response) {

	response.setLength(_response.getLength());
	response.setMsgId(_response.getMsgId());
	response.setFrameLength(_response.getFrameDataLength());

	response.setFrameData(_response.getFrameData());
}

void Ant::readPacketUntilAvailable() {
	while (!(getResponse().isAvailable() || getResponse().isError())) {
		// read some more
		readPacket();
	}
}

bool Ant::readPacket(int timeout) {

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

void Ant::readPacket() {
	// reset previous response
	if (_response.isAvailable() || _response.isError()) {
		// discard previous packet and start over
		resetResponse();
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

AntRequest::AntRequest(uint8_t msgId, uint8_t frameId) {
	_msgId = msgId;
	_frameId = frameId;
}

void AntRequest::setFrameId(uint8_t frameId) {
	_frameId = frameId;
}

uint8_t AntRequest::getFrameId() {
	return _frameId;
}

uint8_t AntRequest::getMsgId() {
	return _msgId;
}

void AntRequest::setMsgId(uint8_t msgId) {
	_msgId = msgId;
}

//void AntRequest::reset() {
//	_frameId = DEFAULT_FRAME_ID;
//}

//uint8_t AntRequest::getPayloadOffset() {
//	return _payloadOffset;
//}
//
//uint8_t AntRequest::setPayloadOffset(uint8_t payloadOffset) {
//	_payloadOffset = payloadOffset;
//}


PayloadRequest::PayloadRequest(uint8_t apiId, uint8_t frameId, uint8_t *payload, uint8_t payloadLength) : AntRequest(apiId, frameId) {
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

ZBTxRequest::ZBTxRequest(const AntAddress64 &addr64, uint16_t addr16, uint8_t broadcastRadius, uint8_t option, uint8_t *data, uint8_t dataLength, uint8_t frameId): PayloadRequest(ZB_TX_REQUEST, frameId, data, dataLength) {
	_addr64 = addr64;
	_addr16 = addr16;
	_broadcastRadius = broadcastRadius;
	_option = option;
}

ZBTxRequest::ZBTxRequest(const AntAddress64 &addr64, uint8_t *data, uint8_t dataLength): PayloadRequest(ZB_TX_REQUEST, DEFAULT_FRAME_ID, data, dataLength) {
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

AntAddress64& ZBTxRequest::getAddress64() {
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

void ZBTxRequest::setAddress64(const AntAddress64& addr64) {
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
	setMsgId(ZB_EXPLICIT_TX_REQUEST);
}

ZBExplicitTxRequest::ZBExplicitTxRequest(AntAddress64 &addr64, uint16_t addr16, uint8_t broadcastRadius, uint8_t option, uint8_t *payload, uint8_t payloadLength, uint8_t frameId, uint8_t srcEndpoint, uint8_t dstEndpoint, uint16_t clusterId, uint16_t profileId)
: ZBTxRequest(addr64, addr16, broadcastRadius, option, payload, payloadLength, frameId) {
	_srcEndpoint = srcEndpoint;
	_dstEndpoint = dstEndpoint;
	_profileId = profileId;
	_clusterId = clusterId;
	setMsgId(ZB_EXPLICIT_TX_REQUEST);
}

ZBExplicitTxRequest::ZBExplicitTxRequest(AntAddress64 &addr64, uint8_t *payload, uint8_t payloadLength)
: ZBTxRequest(addr64, payload, payloadLength) {
	_srcEndpoint = DEFAULT_ENDPOINT;
	_dstEndpoint = DEFAULT_ENDPOINT;
	_profileId = DEFAULT_PROFILE_ID;
	_clusterId = DEFAULT_CLUSTER_ID;
	setMsgId(ZB_EXPLICIT_TX_REQUEST);
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

AtCommandRequest::AtCommandRequest() : AntRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = NULL;
	clearCommandValue();
}

AtCommandRequest::AtCommandRequest(uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AntRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
	_command = command;
	_commandValue = commandValue;
	_commandValueLength = commandValueLength;
}

AtCommandRequest::AtCommandRequest(uint8_t *command) : AntRequest(AT_COMMAND_REQUEST, DEFAULT_FRAME_ID) {
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
//	 AntRequest::reset();
//}

uint8_t AtCommandRequest::getFrameDataLength() {
	// command is 2 byte + length of value
	return AT_COMMAND_API_LENGTH + _commandValueLength;
}

AntAddress64 RemoteAtCommandRequest::broadcastAddress64 = AntAddress64(0x0, BROADCAST_ADDRESS);

RemoteAtCommandRequest::RemoteAtCommandRequest() : AtCommandRequest(NULL, NULL, 0) {
	_remoteAddress16 = 0;
	_applyChanges = false;
	setMsgId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AtCommandRequest(command, commandValue, commandValueLength) {
	_remoteAddress64 = broadcastAddress64;
	_remoteAddress16 = remoteAddress16;
	_applyChanges = true;
	setMsgId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(uint16_t remoteAddress16, uint8_t *command) : AtCommandRequest(command, NULL, 0) {
	_remoteAddress64 = broadcastAddress64;
	_remoteAddress16 = remoteAddress16;
	_applyChanges = false;
	setMsgId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(AntAddress64 &remoteAddress64, uint8_t *command, uint8_t *commandValue, uint8_t commandValueLength) : AtCommandRequest(command, commandValue, commandValueLength) {
	_remoteAddress64 = remoteAddress64;
	// don't worry.. works for series 1 too!
	_remoteAddress16 = ZB_BROADCAST_ADDRESS;
	_applyChanges = true;
	setMsgId(REMOTE_AT_REQUEST);
}

RemoteAtCommandRequest::RemoteAtCommandRequest(AntAddress64 &remoteAddress64, uint8_t *command) : AtCommandRequest(command, NULL, 0) {
	_remoteAddress64 = remoteAddress64;
	_remoteAddress16 = ZB_BROADCAST_ADDRESS;
	_applyChanges = false;
	setMsgId(REMOTE_AT_REQUEST);
}

uint16_t RemoteAtCommandRequest::getRemoteAddress16() {
	return _remoteAddress16;
}

void RemoteAtCommandRequest::setRemoteAddress16(uint16_t remoteAddress16) {
	_remoteAddress16 = remoteAddress16;
}

AntAddress64& RemoteAtCommandRequest::getRemoteAddress64() {
	return _remoteAddress64;
}

void RemoteAtCommandRequest::setRemoteAddress64(AntAddress64 &remoteAddress64) {
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
//GenericRequest::GenericRequest(uint8_t* frame, uint8_t len, uint8_t apiId): AntRequest(apiId, *(frame), len) {
//	_frame = frame;
//}

void Ant::send(AntRequest &request) {
	// the new new deal

	sendByte(START_BYTE, false);

	// send length
	uint8_t msbLen = ((request.getFrameDataLength() + 2) >> 8) & 0xff;
	uint8_t lsbLen = (request.getFrameDataLength() + 2) & 0xff;

	sendByte(msbLen, true);
	sendByte(lsbLen, true);

	// api id
	sendByte(request.getMsgId(), true);
	sendByte(request.getFrameId(), true);

	uint8_t checksum = 0;

	// compute checksum, start at api id
	checksum+= request.getMsgId();
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

void Ant::sendByte(uint8_t b, bool escape) {

	if (escape && (b == START_BYTE || b == ESCAPE || b == XON || b == XOFF)) {
		write(ESCAPE);
		write(b ^ 0x20);
	} else {
		write(b);
	}
}
