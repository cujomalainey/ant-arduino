/***********************************
 * Ant Open Channel Example
 *
 * Opens a channel with a preset
 * network key, period and frequncy.
 * All other fields are wildcarded.
 * Radio output is parsed and
 * transmitted to the serial monitor
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#define BAUD_RATE 9600
Ant ant = Ant();

// Arbitrary key, if you want to connect to ANT+, you must get the key from thisisant.com
const uint8_t NETWORK_KEY[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

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
	Serial.println("Running");

	snk = SetNetworkKey();
	snk.setNetwork(0);
	snk.setKey((uint8_t*)NETWORK_KEY);
	ant.send(snk);
	parseMessage();

	ac = AssignChannel();
	ac.setChannel(0);
	ac.setChannelType(0);
	ac.setChannelNetwork(0);
	ant.send(ac);
	parseMessage();

	ci = ChannelId();
	ci.setChannel(0);
	ci.setDeviceNumber(0);
	ci.setDeviceType(0);
	ci.setTransmissionType(0);
	ant.send(ci);
	parseMessage();

	cp = ChannelPeriod();
	cp.setChannel(0);
	cp.setPeriod(1234);
	ant.send(cp);
	parseMessage();

	crf = ChannelRfFrequency();
	crf.setChannel(0);
	crf.setRfFrequency(0);
	ant.send(crf);
	parseMessage();

	oc = OpenChannel();
	oc.setChannel(0);
	ant.send(oc);
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

			case START_UP_MESSAGE:
			{
				StartUpMessage sum = StartUpMessage();
				ant.getResponse().getStartUpMsg(sum);
				Serial.println("Received Msg: StartupMessage");
				Serial.print("Message: ");
				Serial.println(sum.getMessage());
				break;
			}

			case BROADCAST_DATA:
			{
				BroadcastData bd = BroadcastData();
				ant.getResponse().getBroadcastDataMsg(bd);
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