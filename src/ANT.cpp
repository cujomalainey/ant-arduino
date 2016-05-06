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

ChannelEventResponse::ChannelEventResponse() : AntResponse() {

}

uint8_t ChannelEventResponse::getChannelNumber() {
	return  getFrameData()[0];
}

uint8_t ChannelEventResponse::getMsgId() {
	return getFrameData()[1];
}

uint8_t ChannelEventResponse::getCode() {
	return getFrameData()[2];
}

uint8_t ChannelEventResponse::getExtendedEventParameters() {
	if (getLength() > 3){
		return getFrameData()[3];
	}
	else {
		return INVALID_REQUEST;
	}
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

	//TODO verify response api id matches this api for this response

	// pass pointer array to subclass
	ant->setFrameData(getFrameData());
	setCommon(rxResponse);
}

void AntResponse::getChannelEventResponseMsg(AntResponse &response) {

	// TODO no real need to cast.  change arg to match expected class
	ChannelEventResponse* cer = static_cast<ChannelEventResponse*>(&response);

	// pass pointer array to subclass
	cer->setFrameData(getFrameData());
	setCommon(response);

}

AntRxDataResponse::AntRxDataResponse() : AntResponse() {

}

uint8_t AntRxDataResponse::getData(int index) {
	return getFrameData()[getDataOffset() + index];
}

uint8_t* AntRxDataResponse::getData() {
	return getFrameData() + getDataOffset();
}

void AntResponse::getAcknowledgedDataMsg(AntResponse &ackDataResponse) {

	AcknowledgedData* ackData = static_cast<AcknowledgedData*>(&ackDataResponse);

	// pass pointer array to subclass
	ackData->setFrameData(getFrameData());
	setCommon(ackDataResponse);

}

void AntResponse::getBurstDataTransferMsg(AntResponse &burstDataResponse) {

	BurstDataTransfer* burstData = static_cast<BurstDataTransfer*>(&burstDataResponse);

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
	uint8_t val = _serial->read();
	Serial.print("UART Rx: ");
	Serial.println(val);
	return val;
}

void Ant::write(uint8_t val) {
	_serial->write(val);
	Serial.print("UART Tx: ");
	Serial.println(val);
}

AntResponse& Ant::getResponse() {
	return _response;
}

// TODO how to convert response to proper subclass?
void Ant::getResponse(AntResponse &response) {

	response.setLength(_response.getLength());
	response.setMsgId(_response.getMsgId());
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
		        if (b == ANT_START_BYTE) {
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
				// starts at fourth byte

				if (_pos > ANT_MAX_MSG_DATA_SIZE) {
					// exceed max size.  should never occur
					_response.setErrorCode(PACKET_EXCEEDS_BYTE_ARRAY_LENGTH);
					return;
				}

				// check if we're at the end of the packet
				if (_pos == (_response.getLength() + 3)) {
					// verify checksum

					if (_checksumTotal == b) {
						_response.setChecksum(b);
						_response.setAvailable(true);

						_response.setErrorCode(NO_ERROR);
					} else {
						// checksum failed
						_response.setErrorCode(CHECKSUM_FAILURE);
					}

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

AntRequest::AntRequest(uint8_t msgId) {
	_msgId = msgId;
}

uint8_t AntRequest::getMsgId() {
	return _msgId;
}

void AntRequest::setMsgId(uint8_t msgId) {
	_msgId = msgId;
}



AssignChannel::AssignChannel() : AntRequest(ASSIGN_CHANNEL) {

}

void AssignChannel::setChannel(uint8_t channel) {
	_channel = channel;
}

void AssignChannel::setChannelType(uint8_t channelType) {
	_channelType = channelType;
}

void AssignChannel::setChannelNetwork(uint8_t network) {
	_network = network;
}

uint8_t AssignChannel::getChannel() {
	return _channel;
}

uint8_t AssignChannel::getChannelType() {
	return _channelType;
}

uint8_t AssignChannel::getChannelNetwork() {
	return _network;
}

uint8_t AssignChannel::getDataLength() {
	return ASSIGN_CHANNEL_LENGTH;
}

uint8_t AssignChannel::getData(uint8_t pos) {
	if (pos == 0) {
		return _channel;
	} else if (pos == 1) {
		return _channelType;
	} else {
		return _network;
	}
}

void Ant::send(AntRequest &request) {
	// checksum is XOR of all bytes
	uint8_t checksum = 0;
	
	// the new new deal
	checksum ^= ANT_START_BYTE;
	write(ANT_START_BYTE);

	// send length
	uint8_t len = (request.getDataLength());
	checksum ^= len;
	write(len);

	// Msg id
	write(request.getMsgId());
	checksum ^= request.getMsgId();

	for (int i = 0; i < request.getDataLength(); i++) {
		write(request.getData(i));
		checksum ^= request.getData(i);
	}

	// send checksum
	write(checksum);
}
