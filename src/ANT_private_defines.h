#define ANT_START_BYTE 0xA4

// start/length/msg/checksum bytes
#define ANT_MSG_OVERHEAD_LENGTH 4
// msg is always the third byte in packet
#define ANT_MSG_ID_INDEX 3
#define ANT_MSG_FRONT_OVERHEAD 3

/**
 * Message Length Defines
 */
#define CLOSE_CHANNEL_LENGTH                 0x01
#define REQUEST_MESSAGE_LENGTH               0x02

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
#define BROADCAST_DATA_LENGTH                0x09
#define ACKNOWLEDGE_DATA_LENGTH              0x09
