/**
 * Copyright (c) 2009 Andrew Rapp. All rights reserved.
 * Updated and maintained by Curtis Malainey
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Ant-Arduino.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ANT_h
#define ANT_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include <inttypes.h>

// This value is determined by the largest message size available
#define ANT_MAX_MSG_DATA_SIZE 20

// not everything is implemented!
// commented out IDs are not supported by the NRF51 platform
// and will only added if they are supported by the NRF52
/**
 * Msg Id constants
 */
// Config Messages
#define UNASSIGN_CHANNEL                    0x41
#define ASSIGN_CHANNEL                      0x42
#define CHANNEL_ID                          0x51
#define CHANNEL_PERIOD                      0x43
#define SEARCH_TIMEOUT                      0x44
#define CHANNEL_RF_FREQUENCY                0x45
#define SET_NETWORK_KEY                     0x46
#define TRANSMIT_POWER                      0x47
#define SEARCH_WAVEFORM                     0x49
#define ADD_CHANNEL_ID_TO_LIST              0x59
#define ADD_ENCRYPTION_ID_TO_LIST           0x59
#define CONFIG_ID_LIST                      0x5A
#define CONFIG_ENCRYPTION_ID_LIST           0x5A
#define SET_CHANNEL_TRANSMIT_POWER          0x60
#define LOW_PRIORITY_SEARCH_TIMEOUT         0x63
#define SERIAL_NUMBER_SET_CHANNEL_ID        0x65
#define ENABLE_EXT_RX_MESSAGES              0x66
// #define ENABLE_LED                          0x68
// #define CRYSTAL_ENABLE                      0x6D
#define LIB_CONFIG                          0x6E
#define FREQUENCY_AGILITY                   0x70
#define PROXIMITY_SEARCH                    0x71
// #define CONFIGURE_BUFFER_EVENT              0x74
#define CHANNEL_SEARCH_PRIORITY             0x75
// #define SET_128BIT_NETWORK_KEY              0x76
// #define HIGH_DUTY_SEARCH                    0x77
#define CONFIGURE_ADVANCED_BURST            0x78
#define CONFIGURE_EVENT_FILTER              0x79
#define CONFIGURE_SELECTIVE_DATA_UPDATES    0x7A
#define SET_SELECTIVE_DATA_UPDATE_MASK      0x7B
// #define CONFIGURE_USER_NVM                  0x7C
#define ENABLE_SINGLE_CHANNEL_ENCRYPTION    0x7D
#define SET_ENCRYPTION_KEY                  0x7E
#define SET_ENCRYPTION_INFO                 0x7F
#define CHANNEL_SEARCH_SHARING              0x81
// #define LOAD_STORE_ENCRYPTION_KEY           0x83
// #define SET_USB_DESCRIPTOR_STRING           0xC7
// Notification Messages
#define START_UP_MESSAGE                    0x6F
// #define SERIAL_ERROR_MESSAGE                0xAE
// Control Messages
#define RESET_SYSTEM                        0x4A
#define OPEN_CHANNEL                        0x4B
#define CLOSE_CHANNEL                       0x4C
#define REQUEST_MESSAGE                     0x4D
#define OPEN_RX_SCAN_MODE                   0x5B
// #define SLEEP_MESSAGE                       0xC5
// Data Messages
#define BROADCAST_DATA                      0x4E
#define ACKNOWLEDGED_DATA                   0x4F
#define BURST_TRANSFER_DATA                 0x50
#define ADVANCED_BURST_DATA                 0x72
// Channel Messages
#define CHANNEL_EVENT                       0x40
#define CHANNEL_RESPONSE                    0x40
// Requested Response Messages
#define CHANNEL_STATUS                      0x52
#define CHANNEL_ID                          0x51
#define ANT_VERSION                         0x3E
#define CAPABILITIES                        0x54
// #define SERIAL_NUMBER                       0x61
// #define EVENT_BUFFER_CONFIGURATION          0x74
#define ADVANCED_BURST_CAPABILITES          0x78
#define ADVANCED_BURST_CONFIGURATION        0x78
#define EVENT_FILTER                        0x79
#define SELECTIVE_DATA_UPDATE_MASK_SETTING  0x7B
// #define USER_NVM                            0x7C
#define ENCRYPTION_MODE_PARAMETERS          0x7D
// Test Mode Messages
#define CW_INIT                             0x53
#define CW_TEST                             0x48
// Extended Data Messages (Legacy)
// #define EXTENDED_BROADCAST_DATA             0x5D
// #define EXTENDED_ACKNOWLEDGED_DATA          0x5E
// #define EXTENDED_BURST_DATA                 0x5F

/**
 * Channel Type Codes
 */
#define CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE    0x00
#define CHANNEL_TYPE_BIDIRECTIONAL_TRANSMIT   0x10
#define CHANNEL_TYPE_UNIDIRECTIONAL_RECEIVE   0x50
#define CHANNEL_TYPE_UNIDIRECTIONAL_TRANSMIT  0x40
#define CHANNEL_TYPE_SHARED_RECEIVE           0x20
#define CHANNEL_TYPE_SHARED_TRANSMIT          0x30

/**
 * Channel Response Message Codes
 */
#define	RESPONSE_NO_ERROR               0x00
#define EVENT_RX_SEARCH_TIMEOUT         0x01
#define EVENT_RX_FAIL                   0x02
#define EVENT_TX                        0x03
#define EVENT_TRANSFER_RX_FAILED        0x04
#define EVENT_TRANSFER_TX_COMPLETED     0x05
#define EVENT_TRANSFER_TX_FAILED        0x06
#define EVENT_CHANNEL_CLOSED            0x07
#define EVENT_RX_FAIL_GO_TO_SEARCH      0x08
#define EVENT_CHANNEL_COLLISION         0x09
#define EVENT_TRANSFER_TX_START         0x0A
#define EVENT_TRANSFER_NEXT_DATA_BLOCK  0x11
#define CHANNEL_IN_WRONG_STATE          0x15
#define CHANNEL_NOT_OPENED              0x16
#define CHANNEL_ID_NOT_SET              0x18
#define CLOSE_ALL_CHANNELS              0x19
#define TRANSFER_IN_PROGRESS            0x1F
#define TRANSFER_SEQUENCE_NUMBER_ERROR  0x20
#define TRANSFER_IN_ERROR               0x21
#define MESSAGE_SIZE_EXCEEDS_LIMIT      0x27
#define INVALID_MESSAGE                 0x28
#define INVALID_NETWORK_NUMBER          0x29
#define INVALID_LIST_ID                 0x30
#define INVALID_SCAN_TX_CHANNEL         0x31
#define INVALID_PARAMETER_PROVIDED      0x33
#define EVENT_SERIAL_QUE_OVERFLOW       0x34
#define EVENT_QUE_OVERFLOW              0x35
#define ENCRYPT_NEGOTIATION_SUCCESS     0x38
#define ENCRYPT_NEGOTIATION_FAIL        0x39
#define NVM_FULL_ERROR                  0x40
#define NVM_WRITE_ERROR                 0x41
#define USB_STRING_WRITE_FAIL           0x70
#define MESG_SERIAL_ERROR_ID            0xAE

/**
 * Start Up Message Codes
 */
#define POWER_ON_RESET       0x00
#define HARDWARE_RESET_LINE  ( 1 << 0 )
#define WATCH_DOG_RESET      ( 1 << 1 )
#define COMMAND_RESET        ( 1 << 5 )
#define SYNCHRONOUS_RESET    ( 1 << 6 )
#define SUSPEND_RESET        ( 1 << 7 )

/**
 * Channel Status Codes
 */
#define UNASSIGNED                      0
#define ASSIGNED                        1
#define SEARCHING                       2
#define TRACKING                        3

/**
 * Capabilities Defines
 */
// Standard Options
#define CAPABILITIES_NO_RECEIVE_CHANNELS             ( 1 << 0 )
#define CAPABILITIES_NO_TRANSMIT_CHANNELS            ( 1 << 1 )
#define CAPABILITIES_NO_RECEIVE_MESSAGES             ( 1 << 2 )
#define CAPABILITIES_NO_TRANSMIT_MESSAGES            ( 1 << 3 )
#define CAPABILITIES_NO_ACKD_MESSAGES                ( 1 << 4 )
#define CAPABILITIES_NO_BURST_MESSAGES               ( 1 << 5 )
// Advanced Options
#define CAPABILITIES_NETWORK_ENABLED                 ( 1 << 1 )
#define CAPABILITIES_SERIAL_NUMBER_ENABLED           ( 1 << 3 )
#define CAPABILITIES_PER_CHANNEL_TX_POWER_ENABLED    ( 1 << 4 )
#define CAPABILITIES_LOW_PRIORITY_SEARCH_ENABLED     ( 1 << 5 )
#define CAPABILITIES_SCRIPT_ENABLED                  ( 1 << 6 )
#define CAPABILITIES_SEARCH_LIST_ENABLED             ( 1 << 7 )
// Advanced Options 2
#define CAPABILITIES_LED_ENABLED                     ( 1 << 0 )
#define CAPABILITIES_EXT_MESSAGE_ENABLED             ( 1 << 1 )
#define CAPABILITIES_SCAN_MODE_ENABLED               ( 1 << 2 )
#define CAPABILITIES_PROX_SEARCH_ENABLED             ( 1 << 4 )
#define CAPABILITIES_EXT_ASSIGN_ENABLED              ( 1 << 5 )
#define CAPABILITIES_FS_ANTFS_ENABLED                ( 1 << 6 )
#define CAPABILITIES_FIT1_ENABLED                    ( 1 << 7 )
// Advanced Options 3
#define CAPABILITIES_ADVANCED_BURST_ENABLED          ( 1 << 0 )
#define CAPABILITIES_EVENT_BUFFERING_ENABLED         ( 1 << 1 )
#define CAPABILITIES_EVENT_FILTERING_ENABLED         ( 1 << 2 )
#define CAPABILITIES_HIGH_DUTY_SEARCH_ENABLED        ( 1 << 3 )
#define CAPABILITIES_SEARCH_SHARING_ENABLED          ( 1 << 4 )
#define CAPABILITIES_SELECTIVE_DATA_UPDATES_ENABLED  ( 1 << 6 )
#define CAPABILITIES_ENCRYPTED_CHANNEL_ENABLED       ( 1 << 7 )
// Advanced Options 4
#define CAPABILITIES_RFACTIVE_NOTIFICATION_ENABLED   ( 1 << 0 )

/**
 * Advanced Burst Capabilities Configuration Defines
 */
#define ADV_BURST_SUB_ID_CAPABILITIES                0
#define ADV_BURST_SUB_ID_CONFIGURATION               1
#define ADV_BURST_MAX_PACKET_LENGTH_8_BYTE           0x01
#define ADV_BURST_MAX_PACKET_LENGTH_16_BYTE          0x02
#define ADV_BURST_MAX_PACKET_LENGTH_24_BYTE          0x03
#define ADV_BURST_FREQUENCY_HOP_ENABLED              ( 1 << 0 )

/**
 * Driver Error Codes
 */
#define NO_ERROR                          0
#define CHECKSUM_FAILURE                  1
#define PACKET_EXCEEDS_BYTE_ARRAY_LENGTH  2
#define UNEXPECTED_START_BYTE             3

/**
 * Framework Defines
 */
#define NETWORK_KEY_SIZE                0x08
#define MESSAGE_SIZE                    0x08
#define INVALID_REQUEST                 0xFF
#define BITS_IN_BYTE                    0x08

/**
 * The super class of all Ant responses (RX packets)
 * Users should never attempt to create an instance of this class; instead
 * create an instance of a subclass
 * It is recommend to reuse subclasses to conserve memory
 */
class AntResponse {
public:
	//static const int MODEM_STATUS = 0x8a;
	/**
	 * Default constructor
	 */
	AntResponse();
	/**
	 * Returns msg Id of the response
	 */
	uint8_t getMsgId();
	void setMsgId(uint8_t msgId);
	/**
	 * Returns the MSB length of the packet
	 */
	uint8_t getLength();
	void setLength(uint8_t length);
	/**
	 * Returns the packet checksum
	 */
	uint8_t getChecksum();
	void setChecksum(uint8_t checksum);
	void setFrameData(uint8_t* frameDataPtr);
	/**
	 * Returns the buffer that contains the response.
	 * Starts with byte that follows MSG ID and includes all bytes prior to the checksum
	 * Length is specified by getFrameDataLength()
	 * Note: Unlike Dynasteam's definition of the frame data, this does not start with the MSG ID..
	 * The reason for this is all responses include an MSG ID, whereas my frame data
	 * includes only the MSG specific data.
	 */
	uint8_t* getFrameData();

	void setFrameLength(uint8_t frameLength);
	/**
	 * Returns the length of the packet
	 */
	uint8_t getPacketLength();
	/**
	 * Resets the response to default values
	 */
	void reset();
	/**
	 * Initializes the response
	 */
	void init();
	/**
	 * Call with instance of StartUpMessage class only if getMsgId() == START_UP_MESSAGE
	 * to populate response
	 */
	void getStartUpMsg(AntResponse &response);
	/**
	 * Call with instance of BroadcastData class only if getMsgId() == BROADCAST_DATA
	 * to populate response
	 */
	void getBroadcastDataMsg(AntResponse &response);
	/**
	 * Call with instance of AcknowledgedData class only if getMsgId() == ACKNOWLEDGED_DATA
	 * to populate response
	 */
	void getAcknowledgedDataMsg(AntResponse &response);
	/**
	 * Call with instance of BurstTransferData class only if getMsgId() == BURST_TRANSFER_DATA
	 * to populate response
	 */
	void getBurstTransferDataMsg(AntResponse &response);
	/**
	 * Call with instance of AdvancedBurstData only if getMsgId() == ADVANCED_BURST_DATA
	 */
	void getAdvancedBurstDataMsg(AntResponse &responses);
	/**
	 * Call with instance of ChannelEvent only if getMsgId() == CHANNEL_EVENT or getMsgId() == CHANNEL_RESPONSE
	 */
	void getChannelEventResponseMsg(AntResponse &response);
	/**
	 * Call with instance of ChannelStatus only if getMsgId() == CHANNEL_STATUS
	 */
	void getChannelStatusMsg(AntResponse &response);
	/**
	 * Call with instance of AntVersion only if getMsgId() == ANT_VERSION
	 */
	void getAntVersionMsg(AntResponse &response);
	/**
	 * Call with instance of Capabilities only if getMsgId() == CAPABILITIES
	 */
	void getCapabilitiesMsg(AntResponse &response);
	/**
	 * Call with instance of AdvancedBurstCapabilities only if getMsgId() == ADVANCED_BURST_CAPABILITES
	 */
	void getAdvancedBurstCapabilitiesConfigurationMsg(AntResponse &response);
	/**
	 * Call with instance of SerialNumber only if getMsgId() == SERIAL_NUMBER
	 */
	void getSerialNumberMsg(AntResponse &response);
	/**
	 * Returns true if the response has been successfully parsed and is complete and ready for use
	 */
	bool isAvailable();
	void setAvailable(bool complete);
	/**
	 * Returns true if the response contains errors
	 */
	bool isError();
	/**
	 * Returns an error code, or zero, if successful.
	 * Error codes include: CHECKSUM_FAILURE, PACKET_EXCEEDS_BYTE_ARRAY_LENGTH, UNEXPECTED_START_BYTE
	 */
	uint8_t getErrorCode();
	void setErrorCode(uint8_t errorCode);
protected:
	// pointer to frameData
	uint8_t* _frameDataPtr;
private:
	void setCommon(AntResponse &target);
	uint8_t _msgId;
	uint8_t _length;
	uint8_t _checksum;
	bool _complete;
	uint8_t _errorCode;
};

/**
 * Common functionality for Ant radios to get broadcast data
 */
class AntRxDataResponse : public AntResponse {
public:
	AntRxDataResponse();
	/**
	 * Returns the specified index of the payload.  The index may be 0 to getDataLength() - 1
	 * This method is deprecated; use uint8_t* getData()
	 */
	uint8_t getData(int index);
	/**
	 * Returns the payload array.  This may be accessed from index 0 to getDataLength() - 1
	 */
	uint8_t* getData();
	/**
	 * Returns the length of the payload
	 */
	virtual uint8_t getDataLength() = 0;
	/**
	 * Returns the position in the frame data where the data begins,
	 * its the same for all messages
	 */
	uint8_t getDataOffset();
};

/**
 * Represents a Startup message
 */
class StartUpMessage : public AntResponse {
public:
	StartUpMessage();
	uint8_t getMessage();

	static const uint8_t MSG_ID = START_UP_MESSAGE;
};

/**
 * Represents a BurstTransferData message
 */
class BurstTransferData : public AntRxDataResponse {
public:
	BurstTransferData();
	/**
	 * Returns source channel
	 */
	uint8_t getChanneNumber();
	/**
	 * Returns sepcified byte of data from payload
	 */
	uint8_t getData(uint8_t index);
	uint8_t getExtendedDataLength();
	uint8_t getExtendedData(uint8_t index);

	static const uint8_t MSG_ID = BURST_TRANSFER_DATA;
};

/**
 * Represents a AcknowledgedData message
 */
class AcknowledgedData : public AntRxDataResponse {
public:
	AcknowledgedData();
	/**
	 * Returns source channel
	 */
	uint8_t getChanneNumber();
	/**
	 * Returns sepcified byte of data from payload
	 */
	uint8_t getData(uint8_t index);
	uint8_t getExtendedDataLength();
	uint8_t getExtendedData(uint8_t index);

	static const uint8_t MSG_ID = ACKNOWLEDGED_DATA;
};


/**
 * Represents a Ant Broadcast data message
 */
class BroadcastData : public AntRxDataResponse {
public:
	BroadcastData();
	/**
	 * Returns source channel
	 */
	uint8_t getChannelNumber();
	/**
	 * Returns sepcified byte of data from payload
	 */
	uint8_t getData(uint8_t index);
	uint8_t* getData();
	uint8_t getExtendedDataLength();
	uint8_t getExtendedData(uint8_t index);
	uint8_t getDataLength();
	static const uint8_t MSG_ID = BROADCAST_DATA;
};

/**
 * Represents a Channel Event or Channel Response Message
 */
class ChannelEventResponse : public AntResponse {
public:
	ChannelEventResponse();
	uint8_t getChannelNumber();
	uint8_t getMsgId();
	uint8_t getCode();
	uint8_t getExtendedEventParameters();

	static const uint8_t MSG_ID = CHANNEL_RESPONSE;
};

/**
 * Represents a Channel Status message
 */
class ChannelStatus : public AntResponse {
public:
	ChannelStatus();
	uint8_t getChannelNumber();
	uint8_t getChannelState();
	uint8_t getNetworkNumber();
	uint8_t getChannelType();

	static const uint8_t MSG_ID = CHANNEL_STATUS;
};

/**
 * Represents a ANT Version message
 */
class AntVersion : public AntResponse {
public:
	AntVersion();
	uint8_t getVersionByte(uint8_t pos);

	static const uint8_t MSG_ID = ANT_VERSION;
};

/**
 * Represents a Capabilities message
 */
class Capabilities : public AntResponse {
public:
	Capabilities();
	uint8_t getMaxChannels();
	uint8_t getMaxNetworks();
	uint8_t getStandardOptions();
	uint8_t getAdvancedOptions(uint8_t pos); //note, this is 1 indexed to match the spec sheet
	uint8_t getMaxSensRcoreChannels();

	static const uint8_t MSG_ID = CAPABILITIES;
};

/**
 * Represents a Advanced Burst Capabilities or Current Configuration message
 */
class AdvancedBurstCapabilitiesConfiguration : public AntResponse {
public:
	AdvancedBurstCapabilitiesConfiguration();
	uint8_t getMsgType();
	// Capabilities Methods
	uint8_t getSupportedMaxPacketLength();
	uint32_t getSupportedFeatures();
	// Current Configuration Methods
	bool enable();
	uint8_t getMaxPacketLength();
	uint32_t getRequiredFeatures();
	uint32_t getOptionalFeatures();

	static const uint8_t MSG_ID = ADVANCED_BURST_CAPABILITES;
};

/**
 * Super class of all Ant requests (TX packets)
 * Users should never create an instance of this class; instead use an subclass of this class
 * It is recommended to reuse Subclasses of the class to conserve memory
 * <p/>
 * This class allocates a buffer to
 */
class AntRequest {
public:
	/**
	 * Constructor
	 * TODO make protected
	 */
	AntRequest(uint8_t msgId);
	/**
	 * Returns the Msg id
	 */
	uint8_t getMsgId();
	// setting = 0 makes this a pure virtual function, meaning the subclass must implement, like abstract in java
	/**
	 * Starting after the frame id (pos = 0) and up to but not including the checksum
	 * Note: Unlike Dynastream's definition of the frame data, this does not start with the MSG ID.
	 * The reason for this is the MSG ID and Frame ID are common to all requests, whereas my definition of
	 * frame data is only the MSG specific data.
	 */
	virtual uint8_t getData(uint8_t pos) = 0;
	/**
	 * Returns the size of the msg frame (not including frame id or msg id or checksum).
	 */
	virtual uint8_t getDataLength() = 0;
	//void reset();
protected:
	void setMsgId(uint8_t msgId);
private:
	uint8_t _msgId;
};

/*** CONFIG MESSAGES ****/

/**
 * Represents a unassign channel packet, which is used to disociate a channel
 *
 */
class UnAssignChannel : public AntRequest {
public:
	UnAssignChannel();
	UnAssignChannel(uint8_t channel);
	void setChannel(uint8_t channel);
	uint8_t getChannel();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
};

/**
 * Represents a assign channel packet, which is used to associate a channel
 *
 */
class AssignChannel : public AntRequest {
public:
	AssignChannel();
	void setChannel(uint8_t channel);
	void setChannelType(uint8_t channelType);
	void setChannelNetwork(uint8_t network);
	uint8_t getChannel();
	uint8_t getChannelType();
	uint8_t getChannelNetwork();
protected:
	// declare virtual functions
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint8_t _channelType = 0;
	uint8_t _network = 0;
	uint8_t _extended = 0;
};

/**
 * Represents a channel id message, it is used to
 * configure a channel connection on the ANT radio
 */
class ChannelId : public AntRequest {
public:
	ChannelId();
	void setChannel(uint8_t channel);
	void setDeviceNumber(uint16_t deviceNumber);
	void setDeviceType(uint8_t deviceType);
	void setPairingBit(bool paringBit);
	void setTransmissionType(uint8_t transmissionType);
	uint8_t getChannel();
	uint16_t getDeviceNumber();
	uint8_t getDeviceType();
	bool getPairingBit();
	uint8_t getTransmissionType();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint16_t _deviceNumber;
	uint8_t _deviceType;
	bool _pairingBit;
	uint8_t _transmissionType;
};

/**
 * Represents a channel period message, it is used to
 * configure a channel period on the ANT radio
 */
class ChannelPeriod : public AntRequest {
public:
	ChannelPeriod();
	void setChannel(uint8_t channel);
	void setPeriod(uint16_t period);
	uint8_t getChannel();
	uint16_t getPeriod();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint16_t _period;
};

/**
 * Represents a search timeout message, it is used
 * to configure a channel timeout on the ANT radio
 */
class SearchTimeout : public AntRequest {
public:
	SearchTimeout();
	void setChannel(uint8_t channel);
	void setTimeout(uint8_t timeout);
	uint8_t getChannel();
	uint8_t getTimeout();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint8_t _timeout;
};

/**
 * Represents a channel rf frequency message, it is used to
 * configure a channel period on the ANT radio
 */
class ChannelRfFrequency : public AntRequest {
public:
	ChannelRfFrequency();
	void setChannel(uint8_t channel);
	void setRfFrequency(uint8_t frequency);
	uint8_t getChannel();
	uint8_t getRfFrequency();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint8_t _frequency;
};

/**
 * Represents a set network key message, it is used to configure
 * a network key on the ANT radio
 */
class SetNetworkKey : public AntRequest {
public:
	SetNetworkKey();
	void setNetwork(uint8_t network);
	void setKey(uint8_t* key);
	void setKeyByte(uint8_t byte, uint8_t pos);
	uint8_t getNetwork();
	void getKey(uint8_t* arr);
	uint8_t getKeyByte(uint8_t pos);
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _network;
	uint8_t _key[NETWORK_KEY_SIZE];
};

/**
 * Represents a transmit power message, it is used to configure
 * the radios transmission characteristics
 */
class TransmitPower : public AntRequest {
public:
	TransmitPower();
	void setTxPower(uint8_t power);
	uint8_t getTxPower();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _power;
};

/**
 * Represents a search waveform message, it is used to configure
 * the ...?
 */
class SearchWaveform : public AntRequest {
public:
	SearchWaveform();
	void setChannel(uint8_t channel);
	void setWaveform(uint16_t waveform);
	uint8_t getChannel();
	uint16_t getWaveform();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint16_t _waveform;
};

/**
 * Represents Add Channel Id To List message, it is used to add
 * a channel to a specified list
 */
class AddChannelIdToList : public AntRequest {
public:
	AddChannelIdToList();
	void setChannel(uint8_t channel);
	void setDeviceNumber(uint16_t deviceNumber);
	void setDeviceType(uint8_t deviceType);
	void setTransmissionType(uint8_t transmissionType);
	void setListIndex(uint8_t listIndex);
	uint8_t getChannel();
	uint16_t getDeviceNumber();
	uint8_t getDeviceType();
	uint8_t getTransmissionType();
	uint8_t getListIndex();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint16_t _deviceNumber;
	uint8_t _deviceType;
	uint8_t _transmissionType;
	uint8_t _listIndex;
};

/**
 * Represents a Add Encryption Id To List message, it is used to add
 * an encryption id to a list
 */
class AddEncryptionIdToList : public AntRequest {
public:
	AddEncryptionIdToList();
	void setChannel(uint8_t channel);
	void setEncryptionId(uint32_t encryptionId);
	void setListIndex(uint8_t listIndex);
	uint8_t getChannel();
	uint32_t getEncryptionId();
	uint8_t getListIndex();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
	uint32_t _encryptionId;
};

/*** CONTROL MESSAGES ****/

/**
 * Represents a reset system message, it is used to reset the ANT radio
 */
class ResetSystem : public AntRequest {
public:
	ResetSystem();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
};

/**
 * Represents a open channel message, it is used to open a configured channel the ANT radio
 */
class OpenChannel : public AntRequest {
public:
	OpenChannel();
	OpenChannel(uint8_t channel);
	void setChannel(uint8_t channel);
	uint8_t getChannel();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
};

/**
 * Represents a close channel message, it is used to close a open channel the ANT radio
 */
class CloseChannel : public AntRequest {
public:
	CloseChannel();
	CloseChannel(uint8_t channel);
	void setChannel(uint8_t channel);
	uint8_t getChannel();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _channel;
};

/**
 * Represents a request message, it is used to request a message from the ANT radio
 */
class RequestMessage : public AntRequest {
public:
	RequestMessage();
	void setRequestedMessage(uint8_t msgId);
	void setSubId(uint8_t subId);
	uint8_t getRequestedMessage();
	uint8_t getSubId();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _msgId;
	uint8_t _subId;
};

/**
 * Represents a Open Rx Scan Mode message, it is used to put the ANT radio into open rx scan mode
 */
class OpenRxScanMode : public AntRequest {
public:
	OpenRxScanMode();
	void setSynchronousChannelPacketsOnly(bool synchronousOnly);
	bool getSynchronousChannelPacketsOnly();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	bool _synchronousChannelPacketsOnly;
};

/**
 * Represents a Broadcast Tx message, it is used to send a message from the ANT radio
 */
class BroadcastMsg : public AntRequest {
public:
	BroadcastMsg();
	void setData(uint8_t* data);
	void getData(uint8_t* data);
	void setByte(uint8_t index, uint8_t data);
	uint8_t getByte(uint8_t index);
	void setChannel(uint8_t channel);
	uint8_t getChannel();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _data[MESSAGE_SIZE];
	uint8_t _channel;
};

/**
 * Represents a Acknowledged Tx message, it is used to send a message from the ANT radio
 */
class AcknowledgedMsg : public AntRequest {
public:
	AcknowledgedMsg();
	void setData(uint8_t* data);
	void getData(uint8_t* data);
	void setByte(uint8_t index, uint8_t data);
	uint8_t getByte(uint8_t index);
	void setChannel(uint8_t channel);
	uint8_t getChannel();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _data[MESSAGE_SIZE];
	uint8_t _channel;
};

/**
 * Represents a Burst Transfer Data Tx message, it is used to send a message from the ANT radio
 */
class BurstTransferDataMsg : public AntRequest {
public:
	BurstTransferDataMsg();
	void setData(uint8_t* data);
	void getData(uint8_t* data);
	void setByte(uint8_t index, uint8_t data);
	uint8_t getByte(uint8_t index);
	void setChannelSequence(uint8_t channel);
	uint8_t getChannelSequence();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _data[MESSAGE_SIZE];
	uint8_t _channel;
};

/**
 * Represents a Advanced Burst Data Tx message, it is used to send a message from the ANT radio
 */
class AdvancedBurstDataMsg : public AntRequest {
public:
	AdvancedBurstDataMsg();
	void setData(uint8_t* data);
	void getData(uint8_t* data);
	void setByte(uint8_t index, uint8_t data);
	uint8_t getByte(uint8_t index);
	void setChannelSequence(uint8_t channel);
	uint8_t getChannelSequence();
private:
	uint8_t getData(uint8_t pos);
	uint8_t getDataLength();
	uint8_t _data[MESSAGE_SIZE];
	uint8_t _channel;
};

// TODO add reset/clear method since responses are often reused
/**
 * Primary interface for communicating with an Ant Radio.
 * This class provides methods for sending and receiving packets with an Ant radio via the serial port.
 * The Ant radio must be configured with the network stack
 * in order to use this software.
 * <p/>
 * Since this code is designed to run on a microcontroller, with only one thread, you are responsible for reading the
 * data off the serial buffer in a timely manner.  This involves a call to a variant of readPacket(...).
 * If your serial port is receiving data faster than you are reading, you can expect to lose packets.
 * Arduino only has a 128 byte serial buffer so it can overflow if many packets arrive
 * without a call to readPacket(...)
 * <p/>
 * In order to conserve resources, this class only supports storing one response packet in memory at a time.
 * This means that you must fully consume the packet prior to calling readPacket(...), because calling
 * readPacket(...) overwrites the previous response.
 * <p/>
 * This class creates an array of size MAX_FRAME_DATA_SIZE for storing the response packet.  You may want
 * to adjust this value to conserve memory.
 *
 * \author Andrew Rapp
 * \edited by Curtis Malainey
 */
class Ant {
public:
	Ant();
	/**
	 * Reads all available serial bytes until a packet is parsed, an error occurs, or the buffer is empty.
	 * You may call <i>xbee</i>.getResponse().isAvailable() after calling this method to determine if
	 * a packet is ready, or <i>xbee</i>.getResponse().isError() to determine if
	 * a error occurred.
	 * <p/>
	 * This method should always return quickly since it does not wait for serial data to arrive.
	 * You will want to use this method if you are doing other timely stuff in your loop, where
	 * a delay would cause problems.
	 * NOTE: calling this method resets the current response, so make sure you first consume the
	 * current response
	 */
	void readPacket();
	/**
	 * Waits a maximum of <i>timeout</i> milliseconds for a response packet before timing out; returns true if packet is read.
	 * Returns false if timeout or error occurs.
	 */
	bool readPacket(int timeout);
	/**
	 * Reads until a packet is received or an error occurs.
	 * Caution: use this carefully since if you don't get a response, your Arduino code will hang on this
	 * call forever!! often it's better to use a timeout: readPacket(int)
	 */
	void readPacketUntilAvailable();
	/**
	 * Starts the serial connection on the specified serial port
	 */
	void begin(Stream &serial);
	void getResponse(AntResponse &response);
	/**
	 * Returns a reference to the current response
	 * Note: once readPacket is called again this response will be overwritten!
	 */
	AntResponse& getResponse();
	/**
	 * Sends a AntRequest (TX packet) out the serial port
	 */
	void send(AntRequest &request);
	//uint8_t sendAndWaitForResponse(AntRequest &request, int timeout);
	/**
	 * Specify the serial port.  Only relevant for Arduinos that support multiple serial ports (e.g. Mega)
	 */
	void setSerial(Stream &serial);
private:
	bool available();
	uint8_t read();
	void flush();
	void write(uint8_t val);
	void resetResponse();
	AntResponse _response;
	// current packet position for response.  just a state variable for packet parsing and has no relevance for the response otherwise
	uint8_t _pos;
	// last byte read
	uint8_t b;
	uint8_t _checksumTotal;
	// buffer for incoming RX packets.  holds only the msg specific frame data, starting after the msg id byte and prior to checksum
	uint8_t _responseFrameData[ANT_MAX_MSG_DATA_SIZE];
	Stream* _serial;
};


#endif //ANT_h
