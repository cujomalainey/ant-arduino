/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 * Update and maintained by Curtis Malainey
 *
 * This file is part of Ant-Arduino.
 *
 * Ant-Arduino is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Ant-Arduino is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
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

#define ANT_START_BYTE 0xA4

// start/length/msg/checksum bytes
#define ANT_MSG_OVERHEAD_LENGTH 4
// msg is always the third byte in packet
#define ANT_MSG_ID_INDEX 3
#define ANT_MSG_FRONT_OVERHEAD 3

/**
 * Message Length Defines
 */
#define UNASSIGN_CHANNEL_LENGTH              0x01
#define ASSIGN_CHANNEL_LENGTH                0x03
#define CHANNEL_ID_LENGTH                    0x05
#define CHANNEL_PERIOD_LENGTH                0x03
#define CHANNEL_RF_FREQUENCY_LENGTH          0x02
#define SET_NETWORK_KEY_LENGTH               0x09
#define RESET_SYSTEM_LENGTH                  0x01
#define OPEN_CHANNEL_LENGTH                  0x01
#define CLOSE_CHANNEL_LENGTH                 0x01
#define BROADCAST_DATA_LENGTH                0x09
#define ACKNOWLEDGE_DATA_LENGTH              0x09

/**
 * Channel Status BitField Defines
 */
#define CHANNEL_STATUS_STATE_MASK            0x03
#define CHANNEL_STATUS_NETWORK_NUMBER_SHIFT  0x02
#define CHANNEL_STATUS_NETWORK_NUMBER_MASK   0x03
#define CHANNEL_STATUS_CHANNEL_TYPE_SHIFT    0x04

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

ChannelStatus::ChannelStatus() : AntResponse() {

}

uint8_t ChannelStatus::getChannelNumber() {
	return getFrameData()[0];
}

uint8_t ChannelStatus::getChannelState() {
	return getFrameData()[1] & CHANNEL_STATUS_STATE_MASK;
}

uint8_t ChannelStatus::getNetworkNumber() {
	return ( getFrameData()[1] >> CHANNEL_STATUS_NETWORK_NUMBER_SHIFT ) & CHANNEL_STATUS_NETWORK_NUMBER_MASK;
}

uint8_t ChannelStatus::getChannelType() {
	return getFrameData()[1] >> CHANNEL_STATUS_CHANNEL_TYPE_SHIFT;
}

AntVersion::AntVersion() : AntResponse() {

}

uint8_t AntVersion::getVersionByte(uint8_t pos) {
	return getFrameData()[pos];
}

StartUpMessage::StartUpMessage() : AntResponse() {

}

uint8_t StartUpMessage::getMessage() {
	return  getFrameData()[0];
}

BroadcastData::BroadcastData() : AntRxDataResponse() {

}

uint8_t BroadcastData::getChannelNumber() {
	return AntRxDataResponse::getData(0);
}

uint8_t BroadcastData::getData(uint8_t index) {
	// skip channel byte
	return AntRxDataResponse::getData(index + 1);
}

uint8_t BroadcastData::getExtendedDataLength() {
	// not inplemented
	return INVALID_REQUEST;
}

uint8_t BroadcastData::getExtendedData(uint8_t index) {
	// not inplemented
	return INVALID_REQUEST;
}

uint8_t BroadcastData::getDataLength() {
	return BROADCAST_DATA_LENGTH;
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
	return getFrameData()[index];
}

uint8_t* AntRxDataResponse::getData() {
	return getFrameData();
}

uint8_t AntRxDataResponse::getDataOffset() {
	return ANT_MSG_FRONT_OVERHEAD;
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

void Ant::resetResponse() {
	_pos = 0;
	_checksumTotal = 0;
	_response.reset();
}

Ant::Ant(): _response(AntResponse()) {
        _pos = 0;
        _checksumTotal = 0;

        _response.init();
        _response.setFrameData(_responseFrameData);
		// Contributed by Paul Stoffregen for Teensy support
#if defined(__AVR_ATmega32U4__) || defined(__MK20DX128__)
        _serial = &Serial1;
#else
        _serial = &Serial;
#endif
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
		_checksumTotal ^= b;

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
					// if the last byte is the checksum
					// then XOR it with itself should be 0

					if (_checksumTotal == 0) {
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
					_response.getFrameData()[_pos - ANT_MSG_FRONT_OVERHEAD] = b;
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

UnAssignChannel::UnAssignChannel() : AntRequest(UNASSIGN_CHANNEL) {

}

void UnAssignChannel::setChannel(uint8_t channel) {
	_channel = channel;
}

uint8_t UnAssignChannel::getChannel() {
	return _channel;
}

uint8_t UnAssignChannel::getDataLength() {
	return UNASSIGN_CHANNEL_LENGTH;
}

uint8_t UnAssignChannel::getData(uint8_t pos) {
	return _channel;
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

ChannelId::ChannelId() : AntRequest(CHANNEL_ID) {

}

void ChannelId::setChannel(uint8_t channel) {
	_channel = channel;
}

void ChannelId::setDeviceNumber(uint16_t deviceNumber) {
	_deviceNumber = deviceNumber;
}

void ChannelId::setDeviceType(uint8_t deviceType) {
	_deviceType = deviceType;
}

void ChannelId::setTransmissionType(uint8_t transmissionType) {
	_transmissionType = transmissionType;
}

uint8_t ChannelId::getChannel() {
	return _channel;
}

uint16_t ChannelId::getDeviceNumber() {
	return _deviceNumber;
}

uint8_t ChannelId::getDeviceType() {
	return _deviceType;
}

uint8_t ChannelId::getTransmissionType() {
	return _transmissionType;
}

uint8_t ChannelId::getDataLength() {
	return CHANNEL_ID_LENGTH;
}

uint8_t ChannelId::getData(uint8_t pos) {
	if (pos == 0) {
		return _channel;
	} else if (pos == 1) {
		return (uint8_t)_deviceNumber;
	} else if (pos == 2) {
		return (uint8_t)(_deviceNumber >> BITS_IN_BYTE);
	} else if (pos == 3) {
		return _pairingBit ? ( _deviceType | 0x80 ) : ( _deviceType & 0x7F );
	} else {
		return _transmissionType;
	}
}

ChannelPeriod::ChannelPeriod() : AntRequest(CHANNEL_PERIOD) {

}

void ChannelPeriod::setChannel(uint8_t channel) {
	_channel = channel;
}

void ChannelPeriod::setPeriod(uint16_t period) {
	_period = period;
}

uint8_t ChannelPeriod::getChannel() {
	return _channel;
}

uint16_t ChannelPeriod::getPeriod() {
	return _period;
}

uint8_t ChannelPeriod::getDataLength() {
	return CHANNEL_PERIOD_LENGTH;
}

uint8_t ChannelPeriod::getData(uint8_t pos) {
	if (pos == 0) {
		return _channel;
	} else if (pos == 1) {
		return (uint8_t)_period;
	} else {
		return (uint8_t)(_period >> BITS_IN_BYTE);
	}
}

ChannelRfFrequency::ChannelRfFrequency() : AntRequest(CHANNEL_RF_FREQUENCY) {

}

void ChannelRfFrequency::setChannel(uint8_t channel) {
	_channel = channel;
}

void ChannelRfFrequency::setRfFrequency(uint8_t frequency) {
	_frequency = frequency;
}

uint8_t ChannelRfFrequency::getChannel() {
	return _channel;
}

uint8_t ChannelRfFrequency::getRfFrequency() {
	return _frequency;
}

uint8_t ChannelRfFrequency::getDataLength() {
	return CHANNEL_RF_FREQUENCY_LENGTH;
}

uint8_t ChannelRfFrequency::getData(uint8_t pos) {
	if (pos == 0) {
		return _channel;
	} else {
		return _frequency;
	}
}

SetNetworkKey::SetNetworkKey() : AntRequest(SET_NETWORK_KEY) {
	memset(_key, 0, NETWORK_KEY_SIZE);
}

void SetNetworkKey::setNetwork(uint8_t network) {
	_network = network;
}

void SetNetworkKey::setKey(uint8_t* key) {
	memcpy(_key, key, NETWORK_KEY_SIZE);
}

void SetNetworkKey::setKeyByte(uint8_t byte, uint8_t pos) {
	_key[pos] = byte;
}

uint8_t SetNetworkKey::getNetwork() {
	return _network;
}

void SetNetworkKey::getKey(uint8_t* arr) {
	memcpy(arr, _key, NETWORK_KEY_SIZE);
}

uint8_t SetNetworkKey::getKeyByte(uint8_t pos) {
	return _key[pos];
}

uint8_t SetNetworkKey::getDataLength() {
	return SET_NETWORK_KEY_LENGTH;
}

uint8_t SetNetworkKey::getData(uint8_t pos) {
	if (pos == 0) {
		return _network;
	} else {
		return _key[pos - 1];
	}
}

ResetSystem::ResetSystem() : AntRequest(RESET_SYSTEM) {

}

uint8_t ResetSystem::getDataLength() {
	return RESET_SYSTEM_LENGTH;
}

uint8_t ResetSystem::getData(uint8_t pos) {
	return 0;
}

OpenChannel::OpenChannel() : AntRequest(OPEN_CHANNEL) {

}

OpenChannel::OpenChannel(uint8_t channel) : AntRequest(OPEN_CHANNEL) {
	_channel = channel;
}

void OpenChannel::setChannel(uint8_t channel) {
	_channel = channel;
}

uint8_t OpenChannel::getChannel() {
	return _channel;
}

uint8_t OpenChannel::getDataLength() {
	return OPEN_CHANNEL_LENGTH;
}

uint8_t OpenChannel::getData(uint8_t pos) {
	return _channel;
}

CloseChannel::CloseChannel() : AntRequest(CLOSE_CHANNEL) {

}

CloseChannel::CloseChannel(uint8_t channel) : AntRequest(CLOSE_CHANNEL) {
	_channel = channel;
}

void CloseChannel::setChannel(uint8_t channel) {
	_channel = channel;
}

uint8_t CloseChannel::getChannel() {
	return _channel;
}

uint8_t CloseChannel::getDataLength() {
	return CLOSE_CHANNEL_LENGTH;
}

uint8_t CloseChannel::getData(uint8_t pos) {
	return _channel;
}

/* Extended message format not currently supported */
BroadcastMsg::BroadcastMsg() : AntRequest(BROADCAST_DATA) {

}

void BroadcastMsg::setData(uint8_t* data) {
	memcpy(_data, data, MESSAGE_SIZE);
}

void BroadcastMsg::getData(uint8_t* data) {
	memcpy(data, _data, MESSAGE_SIZE);
}

void BroadcastMsg::setByte(uint8_t index, uint8_t data) {
	_data[index] = data;
}

uint8_t BroadcastMsg::getByte(uint8_t index) {
	return _data[index];
}

void BroadcastMsg::setChannel(uint8_t channel) {
	_channel = channel;
}

uint8_t BroadcastMsg::getChannel() {
	return _channel;
}

uint8_t BroadcastMsg::getDataLength() {
	return BROADCAST_DATA_LENGTH;
}

uint8_t BroadcastMsg::getData(uint8_t pos) {
	if (pos == 0) {
		return _channel;
	}
	else {
		return _data[pos - 1];
	}
}

/* Extended message format not currently supported */
AcknowledgedMsg::AcknowledgedMsg() : AntRequest(ACKNOWLEDGED_DATA) {

}

void AcknowledgedMsg::setData(uint8_t* data) {
	memcpy(_data, data, MESSAGE_SIZE);
}

void AcknowledgedMsg::getData(uint8_t* data) {
	memcpy(data, _data, MESSAGE_SIZE);
}

void AcknowledgedMsg::setByte(uint8_t index, uint8_t data) {
	_data[index] = data;
}

uint8_t AcknowledgedMsg::getByte(uint8_t index) {
	return _data[index];
}

void AcknowledgedMsg::setChannel(uint8_t channel) {
	_channel = channel;
}

uint8_t AcknowledgedMsg::getChannel() {
	return _channel;
}

uint8_t AcknowledgedMsg::getDataLength() {
	return ACKNOWLEDGE_DATA_LENGTH;
}

uint8_t AcknowledgedMsg::getData(uint8_t pos) {
	if (pos == 0) {
		return _channel;
	}
	else {
		return _data[pos - 1];
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
