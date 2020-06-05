#ifndef ANT_BASENATIVEANT_h
#define ANT_BASENATIVEANT_h

#include <BaseClasses/ANT_BaseAnt.h>

#ifdef NATIVE_API_AVAILABLE

/**
 * Primary interface for communicating with an Ant Radio via serial.
 * This class provides methods for sending and receiving packets with an Ant radio via the serial port.
 * The Ant radio must be configured with the network stack
 * in order to use this software.
 * <p/>
 * Since this code is designed to run on a microcontroller, with only one thread, you are responsible for reading the
 * data off the serial buffer in a timely manner.  This involves a call to a variant of readPacket(...).
 * If your serial port is receiving data faster than you are reading, you can expect to lose packets.
 * Arduino only has a 128 byte serial buffer so it can overflow if many packets arrive
 * without a call to readPacket(...)
 * <p/>
 * In order to conserve resources, this class only supports storing one response packet in memory at a time.
 * This means that you must fully consume the packet prior to calling readPacket(...), because calling
 * readPacket(...) overwrites the previous response.
 * <p/>
 * This class creates an array of size MAX_FRAME_DATA_SIZE for storing the response packet.  You may want
 * to adjust this value to conserve memory.
 *
 * \author Andrew Rapp
 * \edited by Curtis Malainey
 */

class BaseNativeAnt : virtual public BaseAnt {
public:
    BaseNativeAnt();
    /**
     * Will read as much data on the serial port as possible till either it has a packet, gets an error or runs out of data
     * You may call <i>ant</i>.getResponse().isAvailable() after calling this method to determine if
     * a packet is ready, or <i>ant</i>.getResponse().isError() to determine if
     * a error occurred.
     * <p/>
     * This method should return quickly as it only works with what is available
     * You will want to use this method if you are doing other timely stuff in your loop, where
     * a delay would cause problems.
     * NOTE: calling this method resets the current response, so make sure you first consume the
     * current response
     */
    void readPacket() override;
    /**
     * Starts the serial connection on the specified serial port
     */
    uint8_t begin(uint8_t total_chan, uint8_t encrypted_chan);
    /**
     * Sends a AntRequest (TX packet) out the serial port
     */
    uint32_t send(AntRequest &request) override;
private:
    void resetResponse();
    uint32_t handleRequest(AntRequest &request);
    bool _backFillReady = false;
    bool _returnFillReady = false;
    // buffer for incoming RX packets. Backfill data structures for message reuse.
    ANT_MESSAGE _responseFrameData;
    // used for TX requests so TX won't overwrite RX state
    uint8_t _backFillBuffer[ANT_MAX_MSG_DATA_SIZE];
    // used to store response message
    uint8_t _returnFillBuffer[ANT_MAX_MSG_DATA_SIZE];
    // softdevice buffer
    uint8_t *_sd_buffer = NULL;
};

#endif // NATIVE_API_AVAILABLE

#endif // ANT_BASENATIVEANT_h
