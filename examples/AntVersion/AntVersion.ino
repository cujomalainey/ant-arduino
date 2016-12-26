/***********************************
 * Ant Version Example
 *
 * Writes the ANT radios version and
 * capabilities to the serial port
 *
 * NOTE: THIS EXAMPLE IS INCOMPLETE
 *
 * Author Curtis Malainey
 ************************************/

#include "ANT.h"
#define BAUD_RATE 9600
Ant ant = Ant();

void parseMessage();

void setup()
{
	ResetSystem rs;
	RequestMessage rm;
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
				if ( cap.getStandardOptions() & CAPABILITIES_NO_RECEIVE_CHANNELS  )
				{
					Serial.println("No Receive Channels");
				}
				if ( cap.getStandardOptions() & CAPABILITIES_NO_TRANSMIT_CHANNELS )
				{
					Serial.println("No Transmit Channels");
				}
				if ( cap.getStandardOptions() & CAPABILITIES_NO_RECEIVE_MESSAGES  )
				{
					Serial.println("No Receive Messages");
				}
				if ( cap.getStandardOptions() & CAPABILITIES_NO_TRANSMIT_MESSAGES )
				{
					Serial.println("No Transmit Messages");
				}
				if ( cap.getStandardOptions() & CAPABILITIES_NO_ACKD_MESSAGES     )
				{
					Serial.println("No Ackd Messages");
				}
				if ( cap.getStandardOptions() & CAPABILITIES_NO_BURST_MESSAGES    )
				{
					Serial.println("No Burst Messages");
				}

				Serial.println("Advanced Options:");
				if ( cap.getAdvancedOptions(0) & CAPABILITIES_NETWORK_ENABLED              )
				{
					Serial.println("Network Enabled");
				}
				if ( cap.getAdvancedOptions(0) & CAPABILITIES_SERIAL_NUMBER_ENABLED        )
				{
					Serial.println("Serial Number Enabled");
				}
				if ( cap.getAdvancedOptions(0) & CAPABILITIES_PER_CHANNEL_TX_POWER_ENABLED )
				{
					Serial.println("Per Channel Tx Power Enabled");
				}
				if ( cap.getAdvancedOptions(0) & CAPABILITIES_LOW_PRIORITY_SEARCH_ENABLED  )
				{
					Serial.println("Low Priority Search Enabled");
				}
				if ( cap.getAdvancedOptions(0) & CAPABILITIES_SCRIPT_ENABLED               )
				{
					Serial.println("Script Enabled");
				}
				if ( cap.getAdvancedOptions(0) & CAPABILITIES_SEARCH_LIST_ENABLED          )
				{
					Serial.println("Search List Enabled");
				}

				Serial.println("Advanced Options 2:");
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_LED_ENABLED         )
				{
					Serial.println("LED Enabled");
				}
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_EXT_MESSAGE_ENABLED )
				{
					Serial.println("Ext Message Enabled");
				}
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_SCAN_MODE_ENABLED   )
				{
					Serial.println("Scan Mode Enabled");
				}
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_PROX_SEARCH_ENABLED )
				{
					Serial.println("Prox Search Enabled");
				}
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_EXT_ASSIGN_ENABLED  )
				{
					Serial.println("Ext Assign Enabled");
				}
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_FS_ANTFS_ENABLED    )
				{
					Serial.println("FS ANTFS Enabled");
				}
				if ( cap.getAdvancedOptions(1) & CAPABILITIES_FIT1_ENABLED        )
				{
					Serial.println("FIT1 Enabled");
				}

				Serial.println("Advanced Options 3:");
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_ADVANCED_BURST_ENABLED         )
				{
					Serial.println("Advanced Burst Enabled");
				}
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_EVENT_BUFFERING_ENABLED        )
				{
					Serial.println("Event Buffering Enabled");
				}
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_EVENT_FILTERING_ENABLED        )
				{
					Serial.println("Event Filtering Enabled");
				}
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_HIGH_DUTY_SEARCH_ENABLED       )
				{
					Serial.println("High Duty Search Enabled");
				}
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_SEARCH_SHARING_ENABLED         )
				{
					Serial.println("Search Sharing Enabled");
				}
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_SELECTIVE_DATA_UPDATES_ENABLED )
				{
					Serial.println("Selective Data Updates Enabled");
				}
				if ( cap.getAdvancedOptions(2) & CAPABILITIES_ENCRYPTED_CHANNEL_ENABLED      )
				{
					Serial.println("Encrypted Channel Enabled");
				}

				Serial.println("Advanced Options 4:");
				if ( cap.getAdvancedOptions(3) & CAPABILITIES_RFACTIVE_NOTIFICATION_ENABLED )
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
				break;
		}
	}
	else if (ant.getResponse().isError())
	{
		Serial.print("ANT MSG ERROR: ");
		Serial.println(ant.getResponse().getErrorCode());
	}
}