/***********************************
 * Ant Version Example
 *
 * Writes the ANT radios version and
 * capabilities to the serial port
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#define BAUD_RATE 9600
ArduinoSerialAnt ant;

void parseMessage();
void parseEventMessage(uint8_t code);

void setup()
{
    ResetSystem rs;
    RequestMessage rm = RequestMessage();
    Serial1.begin(BAUD_RATE);
    ant.setSerial(Serial1);
    ant.send(rs);
    // Delay after resetting the radio to give the user time to connect on serial
    delay(10000);
    Serial.begin(BAUD_RATE);
    Serial.println("Running");

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
}

void loop()
{
    parseMessage();
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
                Serial.println("Received Msg: ChannelEventResponse");
                Serial.print("Channel: ");
                Serial.println(cer.getChannelNumber());
                parseEventMessage(cer.getCode());
                break;
            }

            case ANT_VERSION:
            {
                AntVersion av = AntVersion();
                uint64_t version = 0;
                ant.getResponse().getAntVersionMsg(av);
                Serial.print("Version: ");
                for (uint8_t i = 0; i < av.getPacketLength(); i++)
                {
                    version += (((uint64_t)av.getVersionByte(i)) << i*8);
                }

                uint64_t xx = version/1000000000ULL;
                if (xx >0) Serial.print((long)xx);
                    Serial.print((long)(version-xx*1000000000));

                Serial.println("");
                break;
            }

            case START_UP_MESSAGE:
            {
                StartUpMessage sum = StartUpMessage();
                ant.getResponse().getStartUpMsg(sum);
                Serial.println("Received Msg: StartupMessage");
                Serial.print("Message: ");
                Serial.println(sum.getMessage());
                break;
            }

            case CAPABILITIES:
            {
                Capabilities cap = Capabilities();
                ant.getResponse().getCapabilitiesMsg(cap);

                Serial.print("Max Channels:");
                Serial.println(cap.getMaxChannels());

                Serial.print("Max Networks:");
                Serial.println(cap.getMaxNetworks());

                Serial.println("Standard Options:");
                if ( cap.getStandardOptions() & CAPABILITY_NO_RECEIVE_CHANNELS  )
                {
                    Serial.println("No Receive Channels");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_TRANSMIT_CHANNELS )
                {
                    Serial.println("No Transmit Channels");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_RECEIVE_MESSAGES  )
                {
                    Serial.println("No Receive Messages");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_TRANSMIT_MESSAGES )
                {
                    Serial.println("No Transmit Messages");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_ACKD_MESSAGES     )
                {
                    Serial.println("No Ackd Messages");
                }
                if ( cap.getStandardOptions() & CAPABILITY_NO_BURST_MESSAGES    )
                {
                    Serial.println("No Burst Messages");
                }

                Serial.println("Advanced Options:");
                if ( cap.getAdvancedOptions(0) & CAPABILITY_NETWORK_ENABLED              )
                {
                    Serial.println("Network Enabled");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_SERIAL_NUMBER_ENABLED        )
                {
                    Serial.println("Serial Number Enabled");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_PER_CHANNEL_TX_POWER_ENABLED )
                {
                    Serial.println("Per Channel Tx Power Enabled");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_LOW_PRIORITY_SEARCH_ENABLED  )
                {
                    Serial.println("Low Priority Search Enabled");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_SCRIPT_ENABLED               )
                {
                    Serial.println("Script Enabled");
                }
                if ( cap.getAdvancedOptions(0) & CAPABILITY_SEARCH_LIST_ENABLED          )
                {
                    Serial.println("Search List Enabled");
                }

                Serial.println("Advanced Options 2:");
                if ( cap.getAdvancedOptions(1) & CAPABILITY_LED_ENABLED         )
                {
                    Serial.println("LED Enabled");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_EXT_MESSAGE_ENABLED )
                {
                    Serial.println("Ext Message Enabled");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_SCAN_MODE_ENABLED   )
                {
                    Serial.println("Scan Mode Enabled");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_PROX_SEARCH_ENABLED )
                {
                    Serial.println("Prox Search Enabled");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_EXT_ASSIGN_ENABLED  )
                {
                    Serial.println("Ext Assign Enabled");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_FS_ANTFS_ENABLED    )
                {
                    Serial.println("FS ANTFS Enabled");
                }
                if ( cap.getAdvancedOptions(1) & CAPABILITY_FIT1_ENABLED        )
                {
                    Serial.println("FIT1 Enabled");
                }

                Serial.println("Advanced Options 3:");
                if ( cap.getAdvancedOptions(2) & CAPABILITY_ADVANCED_BURST_ENABLED         )
                {
                    Serial.println("Advanced Burst Enabled");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_EVENT_BUFFERING_ENABLED        )
                {
                    Serial.println("Event Buffering Enabled");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_EVENT_FILTERING_ENABLED        )
                {
                    Serial.println("Event Filtering Enabled");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_HIGH_DUTY_SEARCH_ENABLED       )
                {
                    Serial.println("High Duty Search Enabled");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_SEARCH_SHARING_ENABLED         )
                {
                    Serial.println("Search Sharing Enabled");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_SELECTIVE_DATA_UPDATES_ENABLED )
                {
                    Serial.println("Selective Data Updates Enabled");
                }
                if ( cap.getAdvancedOptions(2) & CAPABILITY_ENCRYPTED_CHANNEL_ENABLED      )
                {
                    Serial.println("Encrypted Channel Enabled");
                }

                Serial.println("Advanced Options 4:");
                if ( cap.getAdvancedOptions(3) & CAPABILITY_RFACTIVE_NOTIFICATION_ENABLED )
                {
                    Serial.println("RfActive Notification Enabled");
                }
                break;
            }

            case ADVANCED_BURST_CAPABILITES:
            {
                uint8_t packet_length = 0;
                AdvancedBurstCapabilitiesConfiguration abc = AdvancedBurstCapabilitiesConfiguration();
                ant.getResponse().getAdvancedBurstCapabilitiesConfigurationMsg(abc);
                Serial.print("Supported Max Packet Length:");
                packet_length = abc.getSupportedMaxPacketLength();
                switch ( packet_length )
                {
                    case ADV_BURST_MAX_PACKET_LENGTH_8_BYTE:
                        Serial.println("8-byte");
                        break;

                    case ADV_BURST_MAX_PACKET_LENGTH_16_BYTE:
                        Serial.println("16-byte");
                        break;

                    case ADV_BURST_MAX_PACKET_LENGTH_24_BYTE:
                        Serial.println("24-byte");
                        break;
                }

                Serial.println("Supported Features:");
                if ( abc.getSupportedFeatures() & ADV_BURST_FREQUENCY_HOP_ENABLED )
                {
                    Serial.println("Frequency Hop Enabled");
                }
                break;
            }

            default:
                Serial.print("Undefined Message: ");
                Serial.println(msgId, HEX);
                break;
        }
    }
    else if (ant.getResponse().isError())
    {
        Serial.print("ANT MSG ERROR: ");
        Serial.println(ant.getResponse().getErrorCode());
    }
}


void parseEventMessage(uint8_t code)
{
    Serial.print("Code: ");
    switch (code)
    {
        case STATUS_RESPONSE_NO_ERROR:
            Serial.println("RESPONSE_NO_ERROR");
            break;

        case STATUS_EVENT_CHANNEL_CLOSED:
            Serial.println("EVENT_CHANNEL_CLOSED");
            break;

        case STATUS_EVENT_TX:
            Serial.println("EVENT_TX");
            break;

        case STATUS_INVALID_MESSAGE:
            Serial.println("INVALID_MESSAGE");
            break;

        default:
            Serial.println(code);
            break;
    }
}
