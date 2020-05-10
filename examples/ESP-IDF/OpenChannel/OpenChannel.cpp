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
#define BUF_SIZE 128

EspIdfSerialAnt ant;

// Arbitrary key, if you want to connect to ANT+, you must get the key from thisisant.com
const uint8_t NETWORK_KEY[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};

void parseMessage();
void parseEventMessage(uint8_t code);

extern "C" {
    void app_main(void);
}

void app_main(void)
{
    AssignChannel ac;
    ResetSystem rs;
    SetNetworkKey snk;
    ChannelId ci;
    ChannelPeriod cp;
    ChannelRfFrequency crf;
    OpenChannel oc;
    uart_port_t port = UART_NUM_0;

    uart_config_t uart_config = {
        .baud_rate = BAUD_RATE,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    };
    uart_driver_install(UART_NUM_1, BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(port, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    ant.setSerial(port);
    ant.send(rs);
    // Delay after resetting the radio to give the user time to connect on serial
    vTaskDelay(10000 / portTICK_PERIOD_MS);
    printf("Running\n");

    snk = SetNetworkKey();
    snk.setNetwork(0);
    snk.setKey((uint8_t*)NETWORK_KEY);
    ant.send(snk);
    parseMessage();

    ac = AssignChannel();
    ac.setChannel(0);
    ac.setChannelType(CHANNEL_TYPE_BIDIRECTIONAL_RECEIVE); //can't wildcard this
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
    cp.setPeriod(1234); //can't wildcard this
    ant.send(cp);
    parseMessage();

    crf = ChannelRfFrequency();
    crf.setChannel(0);
    crf.setRfFrequency(0); //can't wildcard this
    ant.send(crf);
    parseMessage();

    oc = OpenChannel();
    oc.setChannel(0);
    ant.send(oc);

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
                printf("Received Msg: ChannelEventResponse\n");
                printf("Channel: %d\n", cer.getChannelNumber());
                parseEventMessage(cer.getCode());
                break;
            }

            case START_UP_MESSAGE:
            {
                StartUpMessage sum = StartUpMessage();
                ant.getResponse().getStartUpMsg(sum);
                printf("Received Msg: StartupMessage\n");
                printf("Message: %d\n", sum.getMessage());
                break;
            }

            case BROADCAST_DATA:
            {
                BroadcastData bd = BroadcastData();
                uint8_t *data = bd.getData();
                ant.getResponse().getBroadcastDataMsg(bd);
                printf("Received Msg: BroadcastData\n");
                printf("Channel: %d\n", bd.getChannelNumber());
                printf("Data:[%x, %x, %x, %x, %x, %x, %x, %x]\n",
                        data[0], data[1], data[2], data[3],
                        data[4], data[5], data[6], data[7]);
                break;
                }

            default:
                printf("Unhandled Message: %d\n", msgId);
                break;
        }
    }
    else if (ant.getResponse().isError())
    {
        printf("ANT MSG ERROR: %d\n", ant.getResponse().getErrorCode());
    }
}

void parseEventMessage(uint8_t code) {
    const char *msg;
    char buf[10];
    switch (code) {
        case STATUS_RESPONSE_NO_ERROR:
            msg = "RESPONSE_NO_ERROR";
            break;

        case STATUS_EVENT_RX_FAIL:
            msg = "EVENT_RX_FAIL";
            break;

        case STATUS_EVENT_RX_SEARCH_TIMEOUT:
            msg = "EVENT_RX_SEARCH_TIMEOUT";
            break;

        case STATUS_EVENT_CHANNEL_CLOSED:
            msg = "EVENT_CHANNEL_CLOSED";
            break;

        default:
            sprintf(buf, "%d", code);
            msg = buf;
            break;
    }
    printf("Code: %s", msg);
}
