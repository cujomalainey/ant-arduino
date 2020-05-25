#ifndef ANT_ARDUINONATIVEANT_h
#define ANT_ARDUINONATIVEANT_h

#include <BaseClasses/ANT_BaseNativeAnt.h>

#include <RX/ANT_AntResponse.h>
#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

#ifdef NATIVE_API_AVAILABLE

/**
 * Native adapter interface for communicating with an Ant softdevice.
 * This class provides methods for sending and receiving packets with an Ant radio via the native api.
 * This class must run on an nRF device with an ANT enabled soft device.
 * <p/>
 * Since this code is designed to run on a microcontroller, you are responsible for reading the
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

class ArduinoNativeAnt : public virtual BaseNativeAnt {
public:
    ArduinoNativeAnt();
protected:
    uint32_t getMs() override;
};

#endif // NATIVE_API_AVAILABLE

#endif // ANT_ARDUINONATIVEANT_h
