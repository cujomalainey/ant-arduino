#include <BaseClasses/ANT_BaseANT.h>

#include <RX/ANT_AntResponse.h>
#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>
#include <ANT_private_defines.h>

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

// TODO add reset/clear method since responses are often reused
/**
 * Primary interface for communicating with an Ant Radio.
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

class Ant {
public:
    Ant();
    /**
     * Reads all available serial bytes until a packet is parsed, an error occurs, or the buffer is empty.
     * You may call <i>xbee</i>.getResponse().isAvailable() after calling this method to determine if
     * a packet is ready, or <i>xbee</i>.getResponse().isError() to determine if
     * a error occurred.
     * <p/>
     * This method should always return quickly since it does not wait for serial data to arrive.
     * You will want to use this method if you are doing other timely stuff in your loop, where
     * a delay would cause problems.
     * NOTE: calling this method resets the current response, so make sure you first consume the
     * current response
     */
    void readPacket();
    /**
     * Waits a maximum of <i>timeout</i> milliseconds for a response packet before timing out; returns true if packet is read.
     * Returns false if timeout or error occurs.
     */
    bool readPacket(int timeout);
    /**
     * Reads until a packet is received or an error occurs.
     * Caution: use this carefully since if you don't get a response, your Arduino code will hang on this
     * call forever!! often it's better to use a timeout: readPacket(int)
     */
    void readPacketUntilAvailable();
    /**
     * Starts the serial connection on the specified serial port
     */
    void begin(Stream &serial);
    void getResponse(AntResponse &response);
    /**
     * Returns a reference to the current response
     * Note: once readPacket is called again this response will be overwritten!
     */
    AntResponse& getResponse();
    /**
     * Sends a AntRequest (TX packet) out the serial port
     */
    void send(AntRequest &request);
    //uint8_t sendAndWaitForResponse(AntRequest &request, int timeout);
    /**
     * Specify the serial port.  Only relevant for Arduinos that support multiple serial ports (e.g. Mega)
     */
    void setSerial(Stream &serial);
private:
    bool available();
    uint8_t read();
    void flush();
    void write(uint8_t val);
    void resetResponse();
    AntResponse _response;
    // current packet position for response.  just a state variable for packet parsing and has no relevance for the response otherwise
    uint8_t _pos;
    // last byte read
    uint8_t b;
    uint8_t _checksumTotal;
    // buffer for incoming RX packets.  holds only the msg specific frame data, starting after the msg id byte and prior to checksum
    uint8_t _responseFrameData[ANT_MAX_MSG_DATA_SIZE];
    Stream* _serial;
};