/***********************************
 * Ant Version Example
 *
 * Writes the ANT radios version and
 * capabilities to the serial port
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#include "mbed.h"
#define BAUD_RATE 9600
Serial pc(USBTX, USBRX);
UARTSerial Serial1(D1, D0);
MbedSerialAnt ant;

void parseMessage();
void parseEventMessage(uint8_t code);

int main()
{
    ResetSystem rs;
    RequestMessage rm = RequestMessage();
    ant.setSerial(Serial1);
    ant.send(rs);
    // Delay after resetting the radio to give the user time to connect on serial
    wait_ms(10000);
    pc.printf("Running\n");

    parseMessage();

    rm.setRequestedMessage(ANT_VERSION);
    ant.send(rm);
    parseMessage();

    rm.setRequestedMessage(CAPABILITIES);
    ant.send(rm);
    parseMessage();

    rm.setRequestedMessage(ADVANCED_BURST_CAPABILITES);
    ant.send(rm);
    parseMessage();

    while(1) {
        parseMessage();
    }
}

void parseMessage() {
    ant.readPacket();
    if (ant.getResponse().isAvailable()) {
        uint8_t msgId = ant.getResponse().getMsgId();
        switch (msgId) {
            case CHANNEL_EVENT:
            {
                ChannelEventResponse cer = ChannelEventResponse();
                ant.getResponse().getChannelEventResponseMsg(cer);
                pc.printf("Received Msg: ChannelEventResponse\n");
                pc.printf("Channel: %d\n", cer.getChannelNumber());
                parseEventMessage(cer.getCode());
                break;
            }

            case ANT_VERSION:
            {
                AntVersion av = AntVersion();
                uint64_t version = 0;
                ant.getResponse().getAntVersionMsg(av);
                pc.printf("Version: ");
                for (uint8_t i = 0; i < av.getPacketLength(); i++)
                {
                    version += (((uint64_t)av.getVersionByte(i)) << i*8);
                }

                uint64_t xx = version/1000000000ULL;
                if (xx >0) pc.printf("%ld", (long)xx);
                    pc.printf("%ld", (long)(version-xx*1000000000));

                pc.printf("\n");
                break;
            }

            case START_UP_MESSAGE:
            {
                StartUpMessage sum = StartUpMessage();
                ant.getResponse().getStartUpMsg(sum);
                pc.printf("Received Msg: StartupMessage\n");
                pc.printf("Message: %d", sum.getMessage());
                break;
            }

            case CAPABILITIES:
            {
                Capabilities cap = Capabilities();
                ant.getResponse().getCapabilitiesMsg(cap);

                pc.printf("Max Channels: %d\n", cap.getMaxChannels());

                pc.printf("Max Networks: %d\n", cap.getMaxNetworks());

                pc.printf("Standard Options:\n");
                if ( cap.getStandardOptions() & CAPABILITY_NO_RECEIVE_CHANNELS  )
                {
                    pc.printf("No Receive Channels\n");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_TRANSMIT_CHANNELS )
                {
                    pc.printf("No Transmit Channels\n");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_RECEIVE_MESSAGES  )
                {
                    pc.printf("No Receive Messages\n");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_TRANSMIT_MESSAGES )
                {
                    pc.printf("No Transmit Messages");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_ACKD_MESSAGES     )
                {
                    pc.printf("No Ackd Messages\n");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_BURST_MESSAGES    )
                {
                    pc.printf("No Burst Messages\n");
                }

                pc.printf("Advanced Options:\n");
                if ( cap.getAdvancedOptions(0) & CAPABILITY_NETWORK_ENABLED              )
                {
                    pc.printf("Network Enabled\n");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_SERIAL_NUMBER_ENABLED        )
                {
                    pc.printf("Serial Number Enabled\n");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_PER_CHANNEL_TX_POWER_ENABLED )
                {
                    pc.printf("Per Channel Tx Power Enabled\n");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_LOW_PRIORITY_SEARCH_ENABLED  )
                {
                    pc.printf("Low Priority Search Enabled\n");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_SCRIPT_ENABLED               )
                {
                    pc.printf("Script Enabled\n");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_SEARCH_LIST_ENABLED          )
                {
                    pc.printf("Search List Enabled\n");
                }

                pc.printf("Advanced Options 2:\n");
                if ( cap.getAdvancedOptions(1) & CAPABILITY_LED_ENABLED         )
                {
                    pc.printf("LED Enabled\n");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_EXT_MESSAGE_ENABLED )
                {
                    pc.printf("Ext Message Enabled\n");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_SCAN_MODE_ENABLED   )
                {
                    pc.printf("Scan Mode Enabled\n");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_PROX_SEARCH_ENABLED )
                {
                    pc.printf("Prox Search Enabled\n");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_EXT_ASSIGN_ENABLED  )
                {
                    pc.printf("Ext Assign Enabled\n");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_FS_ANTFS_ENABLED    )
                {
                    pc.printf("FS ANTFS Enabled\n");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_FIT1_ENABLED        )
                {
                    pc.printf("FIT1 Enabled\n");
                }

                pc.printf("Advanced Options 3:\n");
                if ( cap.getAdvancedOptions(2) & CAPABILITY_ADVANCED_BURST_ENABLED         )
                {
                    pc.printf("Advanced Burst Enabled\n");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_EVENT_BUFFERING_ENABLED        )
                {
                    pc.printf("Event Buffering Enabled\n");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_EVENT_FILTERING_ENABLED        )
                {
                    pc.printf("Event Filtering Enabled\n");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_HIGH_DUTY_SEARCH_ENABLED       )
                {
                    pc.printf("High Duty Search Enabled\n");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_SEARCH_SHARING_ENABLED         )
                {
                    pc.printf("Search Sharing Enabled\n");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_SELECTIVE_DATA_UPDATES_ENABLED )
                {
                    pc.printf("Selective Data Updates Enabled\n");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_ENCRYPTED_CHANNEL_ENABLED      )
                {
                    pc.printf("Encrypted Channel Enabled\n");
                }

                pc.printf("Advanced Options 4:\n");
                if ( cap.getAdvancedOptions(3) & CAPABILITY_RFACTIVE_NOTIFICATION_ENABLED )
                {
                    pc.printf("RfActive Notification Enabled\n");
                }
                break;
            }

            case ADVANCED_BURST_CAPABILITES:
            {
                uint8_t packet_length = 0;
                AdvancedBurstCapabilitiesConfiguration abc = AdvancedBurstCapabilitiesConfiguration();
                ant.getResponse().getAdvancedBurstCapabilitiesConfigurationMsg(abc);
                pc.printf("Supported Max Packet Length:");
                packet_length = abc.getSupportedMaxPacketLength();
                switch ( packet_length )
                {
                    case ADV_BURST_MAX_PACKET_LENGTH_8_BYTE:
                        pc.printf("8-byte\n");
                        break;

                    case ADV_BURST_MAX_PACKET_LENGTH_16_BYTE:
                        pc.printf("16-byte\n");
                        break;

                    case ADV_BURST_MAX_PACKET_LENGTH_24_BYTE:
                        pc.printf("24-byte\n");
                        break;
                }

                pc.printf("Supported Features:\n");
                if ( abc.getSupportedFeatures() & ADV_BURST_FREQUENCY_HOP_ENABLED )
                {
                    pc.printf("Frequency Hop Enabled\n");
                }
                break;
            }

            default:
                pc.printf("Undefined Message: %x\n", msgId);
                break;
        }
    }
    else if (ant.getResponse().isError())
    {
        pc.printf("ANT MSG ERROR: %d\n", ant.getResponse().getErrorCode());
    }
}


void parseEventMessage(uint8_t code)
{
    pc.printf("Code: ");
    switch (code)
    {
        case STATUS_RESPONSE_NO_ERROR:
            pc.printf("RESPONSE_NO_ERROR\n");
            break;

        case STATUS_EVENT_CHANNEL_CLOSED:
            pc.printf("EVENT_CHANNEL_CLOSED\n");
            break;

        case STATUS_EVENT_TX:
            pc.printf("EVENT_TX\n");
            break;

        case STATUS_INVALID_MESSAGE:
            pc.printf("INVALID_MESSAGE\n");
            break;

        default:
            pc.printf("%d\n", code);
            break;
    }
}
