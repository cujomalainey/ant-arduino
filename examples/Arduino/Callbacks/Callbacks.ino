/***********************************
 * Callbacks Example
 *
 * Opens a channel and writes all
 * data out using callbacks
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#define BAUD_RATE 9600
ArduinoSerialAntWithCallbacks ant;

// Arbitrary key, if you want to connect to ANT+, you must get the key from thisisant.com
const uint8_t NETWORK_KEY[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

void handleMessageWithNoCallback(AntResponse& response, uintptr_t data);
void handleBroadcastMessage(BroadcastData& bd, uintptr_t data);
void handleAntError(uint8_t code, uintptr_t data);
void handleStartUpMessage(StartUpMessage& sum, uintptr_t data);
void handleChannelEventResponse(ChannelEventResponse& cer, uintptr_t data);
bool itsAlive(StartUpMessage& sm, uintptr_t data);

void setup()
{
    AssignChannel ac;
    ResetSystem rs;
    SetNetworkKey snk;
    ChannelId ci;
    ChannelPeriod cp;
    ChannelRfFrequency crf;
    OpenChannel oc;
    StartUpMessage sm;

    Serial1.begin(BAUD_RATE);
    ant.onBroadcastData(handleBroadcastMessage);
    ant.onStartUpMessage(handleStartUpMessage);
    ant.onPacketError(handleAntError);
    ant.onChannelEventResponse(handleChannelEventResponse);
    ant.onOtherResponse(handleMessageWithNoCallback);
    ant.begin(Serial1);

    Serial.begin(9600);
    delay(10000);
    // Delay to give the user time to connect on serial

    Serial.println("Running");

    ant.send(rs);
    ant.waitFor(sm, 2000, itsAlive); // wait 2s for device to start

    snk = SetNetworkKey();
    snk.setNetwork(0);
    snk.setKey((uint8_t*)NETWORK_KEY);
    ant.send(snk);
    if(ant.waitForStatus(snk.getMsgId(), 1000)) {
        Serial.println("No Response for setting network key");
    } else {
        ChannelEventResponse cer = ChannelEventResponse();
        ant.getResponse().getChannelEventResponseMsg(cer);
        handleChannelEventResponse(cer, 0);
    }

    ac = AssignChannel();
    ac.setChannel(0);
    ac.setChannelType(CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE); //can't wildcard this
    ac.setChannelNetwork(0);
    if (ant.sendAndWait(ac, 2000)) {
        Serial.println("No Response for assigning channel");
    } else {
        ChannelEventResponse cer = ChannelEventResponse();
        ant.getResponse().getChannelEventResponseMsg(cer);
        handleChannelEventResponse(cer, 0);
    }

    ci = ChannelId();
    ci.setChannel(0);
    ci.setDeviceNumber(0);
    ci.setDeviceType(0);
    ci.setTransmissionType(0);
    ant.send(ci);
    ant.loop();

    cp = ChannelPeriod();
    cp.setChannel(0);
    cp.setPeriod(1234); //can't wildcard this
    ant.send(cp);
    ant.loop();

    crf = ChannelRfFrequency();
    crf.setChannel(0);
    crf.setRfFrequency(0); //can't wildcard this
    ant.send(crf);
    ant.loop();

    oc = OpenChannel();
    oc.setChannel(0);
    ant.send(oc);
    ant.loop();
}

void loop()
{
    ant.loop();
}

void handleMessageWithNoCallback(AntResponse& response, uintptr_t data) {
    Serial.print("Unhandled Message: ");
    Serial.println(response.getMsgId(), HEX);
}

void handleBroadcastMessage(BroadcastData& bd, uintptr_t data) {
    Serial.println("Received Msg: BroadcastData");
    Serial.print("Channel: ");
    Serial.println(bd.getChannelNumber());
    Serial.print("Data:[");
    Serial.print(bd.getData(0), HEX);
    for (uint8_t i = 1; i < 8; i++)
    {
        Serial.print(", ");
        Serial.print(bd.getData(i), HEX);
    }
    Serial.println("]");
}

void handleAntError(uint8_t code, uintptr_t data) {
    Serial.print("ANT MSG ERROR: ");
    Serial.println(code);
}

void handleStartUpMessage(StartUpMessage& sum, uintptr_t data) {
    Serial.println("Received Msg: StartupMessage");
    Serial.print("Message: ");
    Serial.println(sum.getMessage());
}

void handleChannelEventResponse(ChannelEventResponse& cer, uintptr_t data) {
    Serial.println("Received Msg: ChannelEventResponse");
    Serial.print("Channel: ");
    Serial.println(cer.getChannelNumber());
    uint8_t code = cer.getCode();
    Serial.print("Code: ");
    switch (code) {
        case STATUS_RESPONSE_NO_ERROR:
            Serial.println("RESPONSE_NO_ERROR");
            break;

        case STATUS_EVENT_RX_FAIL:
            Serial.println("EVENT_RX_FAIL");
            break;

        case STATUS_EVENT_RX_SEARCH_TIMEOUT:
            Serial.println("EVENT_RX_SEARCH_TIMEOUT");
            break;

        case STATUS_EVENT_CHANNEL_CLOSED:
            Serial.println("EVENT_CHANNEL_CLOSED");
            break;

        default:
            Serial.println(code);
            break;
    }
}

bool itsAlive(StartUpMessage& sm, uintptr_t data) {
    Serial.println("Radio Reset!");
    return true;
}
