#include <ANT_defines.h>

#ifndef ANT_PRIVATE_DEFINES_h
#define ANT_PRIVATE_DEFINES_h

#define ANT_START_BYTE 0xA4

// start/length/msg/checksum bytes
#define ANT_MSG_OVERHEAD_LENGTH 4
// msg is always the third byte in packet
#define ANT_MSG_ID_INDEX        3
#define ANT_MSG_FRONT_OVERHEAD  3

/**
 * Message Length Defines
 */
#define ACKNOWLEDGED_DATA_LENGTH             0x09
#define ADVANCED_BURST_DATA_LENGTH           0x09
#define ASSIGN_CHANNEL_LENGTH                0x03
#define BROADCAST_DATA_LENGTH                0x09
#define BURST_DATA_TRANSFER_LENGTH           0x09
#define BURST_TRANSFER_DATA_LENGTH           0x09
#define CHANNEL_ID_LENGTH                    0x05
#define CHANNEL_PERIOD_LENGTH                0x03
#define CHANNEL_RF_FREQUENCY_LENGTH          0x02
#define CHANNEL_SEARCH_SHARING_LENGTH        0x02
#define CLOSE_CHANNEL_LENGTH                 0x01
#define LIB_CONFIG_LENGTH                    0x02
#define OPEN_CHANNEL_LENGTH                  0x01
#define OPEN_RX_SCAN_MODE_LENGTH             0x01
#define REQUEST_MESSAGE_LENGTH               0x02
#define RESET_SYSTEM_LENGTH                  0x01
#define SEARCH_WAVEFORM_LENGTH               0x03
#define SET_NETWORK_KEY_LENGTH               0x09
#define TRANSMIT_POWER_LENGTH                0x02
#define UNASSIGN_CHANNEL_LENGTH              0x01

/**
 * Channel Status BitField Defines
 */
#define CHANNEL_STATUS_STATE_MASK            0x03
#define CHANNEL_STATUS_NETWORK_NUMBER_SHIFT  0x02
#define CHANNEL_STATUS_NETWORK_NUMBER_MASK   0x03
#define CHANNEL_STATUS_CHANNEL_TYPE_SHIFT    0x04


#endif // ANT_PRIVATE_DEFINES_h
