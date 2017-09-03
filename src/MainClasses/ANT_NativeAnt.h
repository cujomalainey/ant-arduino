#ifndef ANT_NATIVEANT_h
#define ANT_NATIVEANT_h

#include <BaseClasses/ANT_BaseAnt.h>

#include <RX/ANT_AntResponse.h>
#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

#ifdef NATIVE_API_AVAILABLE

#include "ant_parameters.h"

/**
 * Native adapter interface for communicating with an Ant softdevice.
 * This class provides methods for sending and receiving packets with an Ant radio via the native api.
 * This class must run on an nRF device with an ANT enabled soft device.
 * <p/>
 * Since this code is designed to run on a microcontroller, with only one thread, you are responsible for reading the
 * data off the system buffer in a timely manner.  This involves a call to a variant of readPacket(...).
 * If your system is receiving data faster than you are reading, you can expect to lose packets.
 * <p/>
 * In order to conserve resources, this class only supports storing one response packet in memory at a time.
 * This means that you must fully consume the packet prior to calling readPacket(...), because calling
 * readPacket(...) overwrites the previous response.
 * <p/>
 * This class creates an array of size MAX_SD_DATA_SIZE for storing the response packet.
 * Unlike the other classes, DO NOT MODIFY THIS VALUE.
 *
 * \author Curtis Malainey
 */

class NativeAnt : public virtual BaseAnt {
public:
    NativeAnt();
    /**
     * Configures the api and starts the soft device
     */
    void begin();
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
    void readPacket();
    /**
     * Sends a AntRequest (TX packet) out the api
     */
    void send(AntRequest &request);
private:
    uint8_t _responseFrameData[MESG_BUFFER_SIZE];
};

#endif // NATIVE_API_AVAILABLE

#endif // ANT_NATIVEANT_h