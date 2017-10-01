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
#define ACKNOWLEDGED_DATA_LENGTH                0x09
#define ADD_CHANNEL_ID_TO_LIST_LENGTH           0x06
#define ADD_ENCRYPTION_ID_TO_LIST_LENGTH        0x06
#define ADVANCED_BURST_DATA_LENGTH              0x09
#define ASSIGN_CHANNEL_LENGTH                   0x03
#define BROADCAST_DATA_LENGTH                   0x09
#define BURST_DATA_TRANSFER_LENGTH              0x09
#define BURST_TRANSFER_DATA_LENGTH              0x09
#define CHANNEL_ID_LENGTH                       0x05
#define CHANNEL_PERIOD_LENGTH                   0x03
#define CHANNEL_RF_FREQUENCY_LENGTH             0x02
#define CHANNEL_SEARCH_PRIORITY_LENGTH          0x02
#define CHANNEL_SEARCH_SHARING_LENGTH           0x02
#define CLOSE_CHANNEL_LENGTH                    0x01
#define CONFIG_ENCRYPTION_ID_LIST_LENGTH        0x03
#define CONFIG_ID_LIST_LENGTH                   0x03
#define CONFIGURE_ADVANCED_BURST_LENGTH         0x0C
#define CONFIGURE_EVENT_FILTER_LENTGH           0x03
#define CONFIGURE_SELECTIVE_DATA_UPDATES_LENGTH 0x02
#define CW_INIT_LENGTH                          0x01
#define ENABLE_EXT_RX_MESSAGES_LENGTH           0x02
#define ENABLE_SINGLE_CHANNEL_ENCRYPTION_LENGTH 0x04
#define FREQUENCY_AGILITY_LENGTH                0x04
#define LIB_CONFIG_LENGTH                       0x02
#define LOW_PRIORITY_SEARCH_TIMEOUT_LENGTH      0x02
#define OPEN_CHANNEL_LENGTH                     0x01
#define OPEN_RX_SCAN_MODE_LENGTH                0x01
#define PROXIMITY_SEARCH_LENGTH                 0x02
#define REQUEST_MESSAGE_LENGTH                  0x02
#define RESET_SYSTEM_LENGTH                     0x01
#define SEARCH_TIMEOUT_LENGTH                   0x02
#define SEARCH_WAVEFORM_LENGTH                  0x03
#define SERIAL_NUMBER_SET_CHANNEL_ID_LENGTH     0x03
#define SET_CHANNEL_TRANSMIT_POWER_LENGTH       0x02
#define SET_NETWORK_KEY_LENGTH                  0x09
#define TRANSMIT_POWER_LENGTH                   0x02
#define UNASSIGN_CHANNEL_LENGTH                 0x01

/**
 * Channel Status BitField Defines
 */
#define CHANNEL_STATUS_STATE_MASK            0x03
#define CHANNEL_STATUS_NETWORK_NUMBER_SHIFT  0x02
#define CHANNEL_STATUS_NETWORK_NUMBER_MASK   0x03
#define CHANNEL_STATUS_CHANNEL_TYPE_SHIFT    0x04

/**
 * Config ID List Defines
 */
#define CONFIG_ID_LIST_LIST_MAX_SIZE         0x04

/**
 * Advanced burst defines
 */
#define ADVANCED_BURST_DATA_CHANNEL_MASK     0x1F
#define ADVANCED_BURST_DATA_SEQUENCENUMBER_SHIFT 5

/**
 * Configure Selective Data Updates defines
 */
#define CONFIGURE_SELECTIVE_DATA_UPDATES_SDU_DISABLE 0xFF
#define CONFIGURE_SELECTIVE_DATA_UPDATES_SDU_NUMBER_MASK 0x1F
#define CONFIGURE_SELECTIVE_DATA_UPDATES_FILTER_BIT_MASK 0x80

#endif // ANT_PRIVATE_DEFINES_h
