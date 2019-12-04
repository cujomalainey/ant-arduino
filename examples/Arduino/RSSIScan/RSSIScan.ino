/***********************************
 * Ant RSSI Scan Example
 *
 * Opens a channel in rx scan mode
 * then reports all found devices
 * and their RSSI values
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#define BAUD_RATE 9600
Ant ant = Ant();

const uint8_t NETWORK_KEY[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

void parseMessage();
void parseEventMessage(uint8_t code);

void setup()
{
    AssignChannel ac;
    ResetSystem rs;
    SetNetworkKey snk;
    ChannelId ci;
    ChannelRfFrequency crf;
    LibConfig lb;
    OpenRxScanMode osm;

    Serial1.begin(BAUD_RATE);
    ant.setSerial(Serial1);
    ant.send(rs);
    // Delay after resetting the radio to give the user time to connect on serial
    delay(10000);
    Serial.begin(9600);
    Serial.println("Running");
    parseMessage();

    snk.setNetwork(0);
    snk.setKey((uint8_t*)NETWORK_KEY);
    ant.send(snk);
    parseMessage();

    ac.setChannel(OPEN_RX_SCAN_MODE_CHANNEL);
    ac.setChannelType(CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE); //can't wildcard this
    ac.setChannelNetwork(0);
    ant.send(ac);
    parseMessage();

    ci.setChannel(OPEN_RX_SCAN_MODE_CHANNEL);
    ci.setDeviceNumber(0);
    ci.setDeviceType(0);
    ci.setTransmissionType(0);
    ant.send(ci);
    parseMessage();

    lb.setConfig(LIB_CONFIG_RSSI | LIB_CONFIG_CHANNEL_ID);
    ant.send(lb);
    parseMessage();

    crf.setChannel(OPEN_RX_SCAN_MODE_CHANNEL);
    crf.setRfFrequency(0); //can't wildcard this
    ant.send(crf);
    parseMessage();

    ant.send(osm);
    parseMessage();
}

void loop()
{
    parseMessage();
}

void parseMessage() {
    ant.readPacket();
    if(ant.getResponse().isAvailable())
    {
        uint8_t msgId = ant.getResponse().getMsgId();
        switch (msgId) {
            case CHANNEL_EVENT:
            {
                ChannelEventResponse cer;
                ant.getResponse().getChannelEventResponseMsg(cer);
                Serial.println("Received Msg: ChannelEventResponse");
                Serial.print("Channel: ");
                Serial.println(cer.getChannelNumber());
                parseEventMessage(cer.getCode());
                break;
            }

            case START_UP_MESSAGE:
            {
                StartUpMessage sum;
                ant.getResponse().getStartUpMsg(sum);
                Serial.println("Received Msg: StartupMessage");
                Serial.print("Message: ");
                Serial.println(sum.getMessage());
                break;
            }

            case BROADCAST_DATA:
            {
                BroadcastData bd;
                ant.getResponse().getBroadcastDataMsg(bd);
                if ((bd.getFlagByte() & LIB_CONFIG_RSSI) && (bd.getFlagByte() & LIB_CONFIG_CHANNEL_ID)) {
                    Serial.print("Device Number: ");
                    Serial.print(bd.getDeviceNumber());
                    Serial.print(", Device Type: ");
                    Serial.print(bd.getDeviceType());
                    Serial.print(", RSSI: ");
                    Serial.println(bd.getRSSIValue());
                }
                break;
            }

            case ACKNOWLEDGED_DATA:
            {
                AcknowledgedData ad;
                ant.getResponse().getAcknowledgedDataMsg(ad);
                if ((ad.getFlagByte() & LIB_CONFIG_CHANNEL_ID) && (ad.getFlagByte() & LIB_CONFIG_RSSI)) {
                    Serial.print("Device Number: ");
                    Serial.print(ad.getDeviceNumber());
                    Serial.print(", Device Type: ");
                    Serial.print(ad.getDeviceType());
                    Serial.print(", RSSI: ");
                    Serial.println(ad.getRSSIValue());
                }
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
    BroadcastDataMsg bm;
    Serial.print("Code: ");
    switch (code)
    {
        case STATUS_RESPONSE_NO_ERROR:
            Serial.println("RESPONSE_NO_ERROR");
            break;

        case STATUS_EVENT_CHANNEL_CLOSED:
            Serial.println("EVENT_CHANNEL_CLOSED");
            break;

        default:
            Serial.println(code);
            break;
    }
}
