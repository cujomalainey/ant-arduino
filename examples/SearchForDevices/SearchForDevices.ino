/***********************************
 * Search for Devices
 *
 * Searches and prints out all
 * visible devices, their type
 * and RSSI.
 *
 * TODOs RSSI information
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#define BAUD_RATE 9600
Ant ant = Ant();

// Arbitrary key, if you want to connect to ANT+, you must get the key from thisisant.com
const uint8_t NETWORK_KEY[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

uint8_t maxChannels = 0;

void parseMessage();
void parseEventMessage(uint8_t code);

void setup()
{
    AssignChannel ac;
    ResetSystem rs;
    SetNetworkKey snk;
    ChannelId ci;
    ChannelPeriod cp;
    ChannelRfFrequency crf;
    OpenChannel oc;

    Serial1.begin(BAUD_RATE);
    // this will be moved into the driver eventually
    #if defined(CORE_TEENSY)
        Serial1.attachCts(20);
    #else
        // ant.attachCts()
    #endif
    ant.setSerial(Serial1);
    ant.send(rs);
    // Delay after resetting the radio to give the user time to connect on serial
    delay(10000);
    Serial.begin(9600);
    Serial.println("Running");

    Serial.println("Getting Max Channels");
    do {
        rm.setRequestedMessage(CAPABILITIES);
        ant.send(rm);
        delay(100);
        parseMessage();
    } while(0 == maxChannels);
    Serial.print("Max Channels: ");
    Serial.println(maxChannels);

    snk = SetNetworkKey();
    snk.setNetwork(0);
    snk.setKey((uint8_t*)NETWORK_KEY);
    ant.send(snk);
    parseMessage();

    for (uint8_t i = 0; i < maxChannels; i++) {
        ac = AssignChannel();
        ac.setChannel(i);
        ac.setChannelType(CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE); //can't wildcard this
        ac.setChannelNetwork(0);
        ant.send(ac);
        parseMessage();

        ci = ChannelId();
        ci.setChannel(i);
        ci.setDeviceNumber(0);
        ci.setDeviceType(0);
        ci.setTransmissionType(0);
        ant.send(ci);
        parseMessage();

        cp = ChannelPeriod();
        cp.setChannel(i);
        cp.setPeriod(1234); //can't wildcard this
        ant.send(cp);
        parseMessage();

        crf = ChannelRfFrequency();
        crf.setChannel(i);
        crf.setRfFrequency(0); //can't wildcard this
        ant.send(crf);
        parseMessage();

        oc = OpenChannel();
        oc.setChannel(i);
        ant.send(oc);
        parseMessage();
        delay(50);
    }
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

            case START_UP_MESSAGE:
            {
                StartUpMessage sum = StartUpMessage();
                ant.getResponse().getStartUpMsg(sum);
                Serial.println("Received Msg: StartupMessage");
                Serial.print("Message: ");
                Serial.println(sum.getMessage());
                break;
            }

            case CHANNEL_ID:
            {
                ChannelIdResponse cir = ChannelIdResponse();
                ant.getResponse().getChannelIdResponseMsg(cir);
                Serial.println("Received Msg: StartupMessage");
                Serial.print("Message: ");
                Serial.println(sum.getMessage());
                break;
            }

            default:
                break;
        }
    }
    else if (ant.getResponse().isError())
    {
        Serial.print("ANT MSG ERROR: ");
        Serial.println(ant.getResponse().getErrorCode());
    }
}

void parseEventMessage(uint8_t code) {
    Serial.print("Code: ");
    switch (code) {
        case RESPONSE_NO_ERROR:
            Serial.println("RESPONSE_NO_ERROR");
            break;

        case EVENT_RX_FAIL:
            Serial.println("EVENT_RX_FAIL");
            break;

        case EVENT_RX_SEARCH_TIMEOUT:
            Serial.println("EVENT_RX_SEARCH_TIMEOUT");
            break;

        case EVENT_CHANNEL_CLOSED:
            Serial.println("EVENT_CHANNEL_CLOSED");
            break;

        default:
            Serial.println(code);
            break;
    }
}