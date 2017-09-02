#ifndef ANT_DEFINES_h
#define ANT_DEFINES_h

#include <inttypes.h>

// This value is determined by the largest message size available
#define ANT_MAX_MSG_DATA_SIZE 28

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
#define STATUS_RESPONSE_NO_ERROR               0x00
#define STATUS_EVENT_RX_SEARCH_TIMEOUT         0x01
#define STATUS_EVENT_RX_FAIL                   0x02
#define STATUS_EVENT_TX                        0x03
#define STATUS_EVENT_TRANSFER_RX_FAILED        0x04
#define STATUS_EVENT_TRANSFER_TX_COMPLETED     0x05
#define STATUS_EVENT_TRANSFER_TX_FAILED        0x06
#define STATUS_EVENT_CHANNEL_CLOSED            0x07
#define STATUS_EVENT_RX_FAIL_GO_TO_SEARCH      0x08
#define STATUS_EVENT_CHANNEL_COLLISION         0x09
#define STATUS_EVENT_TRANSFER_TX_START         0x0A
#define STATUS_EVENT_TRANSFER_NEXT_DATA_BLOCK  0x11
#define STATUS_CHANNEL_IN_WRONG_STATE          0x15
#define STATUS_CHANNEL_NOT_OPENED              0x16
#define STATUS_CHANNEL_ID_NOT_SET              0x18
#define STATUS_CLOSE_ALL_CHANNELS              0x19
#define STATUS_TRANSFER_IN_PROGRESS            0x1F
#define STATUS_TRANSFER_SEQUENCE_NUMBER_ERROR  0x20
#define STATUS_TRANSFER_IN_ERROR               0x21
#define STATUS_MESSAGE_SIZE_EXCEEDS_LIMIT      0x27
#define STATUS_INVALID_MESSAGE                 0x28
#define STATUS_INVALID_NETWORK_NUMBER          0x29
#define STATUS_INVALID_LIST_ID                 0x30
#define STATUS_INVALID_SCAN_TX_CHANNEL         0x31
#define STATUS_INVALID_PARAMETER_PROVIDED      0x33
#define STATUS_EVENT_SERIAL_QUE_OVERFLOW       0x34
#define STATUS_EVENT_QUE_OVERFLOW              0x35
#define STATUS_ENCRYPT_NEGOTIATION_SUCCESS     0x38
#define STATUS_ENCRYPT_NEGOTIATION_FAIL        0x39
#define STATUS_NVM_FULL_ERROR                  0x40
#define STATUS_NVM_WRITE_ERROR                 0x41
#define STATUS_USB_STRING_WRITE_FAIL           0x70
#define STATUS_MESG_SERIAL_ERROR_ID            0xAE

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
#define CHANNEL_STATUS_UNASSIGNED       0
#define CHANNEL_STATUS_ASSIGNED         1
#define CHANNEL_STATUS_SEARCHING        2
#define CHANNEL_STATUS_TRACKING         3

/**
 * Capabilities Defines
 */
// Standard Options
#define CAPABILITY_NO_RECEIVE_CHANNELS             ( 1 << 0 )
#define CAPABILITY_NO_TRANSMIT_CHANNELS            ( 1 << 1 )
#define CAPABILITY_NO_RECEIVE_MESSAGES             ( 1 << 2 )
#define CAPABILITY_NO_TRANSMIT_MESSAGES            ( 1 << 3 )
#define CAPABILITY_NO_ACKD_MESSAGES                ( 1 << 4 )
#define CAPABILITY_NO_BURST_MESSAGES               ( 1 << 5 )
// Advanced Options
#define CAPABILITY_NETWORK_ENABLED                 ( 1 << 1 )
#define CAPABILITY_SERIAL_NUMBER_ENABLED           ( 1 << 3 )
#define CAPABILITY_PER_CHANNEL_TX_POWER_ENABLED    ( 1 << 4 )
#define CAPABILITY_LOW_PRIORITY_SEARCH_ENABLED     ( 1 << 5 )
#define CAPABILITY_SCRIPT_ENABLED                  ( 1 << 6 )
#define CAPABILITY_SEARCH_LIST_ENABLED             ( 1 << 7 )
// Advanced Options 2
#define CAPABILITY_LED_ENABLED                     ( 1 << 0 )
#define CAPABILITY_EXT_MESSAGE_ENABLED             ( 1 << 1 )
#define CAPABILITY_SCAN_MODE_ENABLED               ( 1 << 2 )
#define CAPABILITY_PROX_SEARCH_ENABLED             ( 1 << 4 )
#define CAPABILITY_EXT_ASSIGN_ENABLED              ( 1 << 5 )
#define CAPABILITY_FS_ANTFS_ENABLED                ( 1 << 6 )
#define CAPABILITY_FIT1_ENABLED                    ( 1 << 7 )
// Advanced Options 3
#define CAPABILITY_ADVANCED_BURST_ENABLED          ( 1 << 0 )
#define CAPABILITY_EVENT_BUFFERING_ENABLED         ( 1 << 1 )
#define CAPABILITY_EVENT_FILTERING_ENABLED         ( 1 << 2 )
#define CAPABILITY_HIGH_DUTY_SEARCH_ENABLED        ( 1 << 3 )
#define CAPABILITY_SEARCH_SHARING_ENABLED          ( 1 << 4 )
#define CAPABILITY_SELECTIVE_DATA_UPDATES_ENABLED  ( 1 << 6 )
#define CAPABILITY_ENCRYPTED_CHANNEL_ENABLED       ( 1 << 7 )
// Advanced Options 4
#define CAPABILITY_RFACTIVE_NOTIFICATION_ENABLED   ( 1 << 0 )

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
 * Lib Config Bit Definitions
 */
#define LIB_CONFIG_DISABLED      0
#define LIB_CONFIG_RX_TIMESTAMP  0x20
#define LIB_CONFIG_RSSI          0x40
#define LIB_CONFIG_CHANNEL_ID    0x80

/**
 * Channel Search Sharing Definitions
 */
#define CHANNEL_SEARCH_SHARING_DISABLED 0

/**
 * Config Encryption Id List Definitions
 */
#define CONFIG_ENCRYPTION_ID_LIST_TYPE_WHITELIST 0x00
#define CONFIG_ENCRYPTION_ID_LIST_TYPE_BLACKLIST 0x01
#define CONFIG_ENCRYPTION_ID_LIST_MAX_LIST_SIZE  4

/**
 * Config Encryption Id List Definitions
 */
#define CONFIG_ID_LIST_EXCLUSION_INCLUSION 0x00
#define CONFIG_ID_LIST_EXCLUSION_EXCLUSION 0x01

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
 * SoftDevice API available, build native ant
 */
// #if (defined(S332) || defined(S212))
    #define NATIVE_API_AVAILABLE
// #endif

#endif // ANT_DEFINES_h