#ifndef ANT_BASEANT_h
#define ANT_BASEANT_h

#include <RX/ANT_AntResponse.h>
#include <TX/ANT_AntRequest.h>

#include <ANT_defines.h>

#ifdef UNIT_TEST
// Includes a mock stream object for unit testing
#include "Util/Testing.h"
#else
#include "Arduino.h"
#endif

class BaseAnt {
public:
    BaseAnt();
    /**
     * Checks to see if a packet is available
     * You may call <i>ant</i>.getResponse().isAvailable() after calling this method to determine if
     * a packet is ready, or <i>ant</i>.getResponse().isError() to determine if
     * a error occurred.
     * <p/>
     * This method will always return quickly with the native interface.
     * You will want to use this method if you are doing other timely stuff in your loop, where
     * a delay would cause problems.
     * NOTE: calling this method resets the current response, so make sure you first consume the
     * current response
     */
    virtual void readPacket() = 0;
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
    void getResponse(AntResponse &response);
    /**
     * Returns a reference to the current response
     * Note: once readPacket is called again this response will be overwritten!
     */
    AntResponse& getResponse();
    /**
     * Sends a AntRequest (TX packet)
     */
    virtual void send(AntRequest &request) = 0;
private:
    AntResponse _response;
};

#endif // ANT_BASEANT_h