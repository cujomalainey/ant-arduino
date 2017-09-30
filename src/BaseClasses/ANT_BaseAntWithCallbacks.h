#ifndef ANT_BASEANTWITHCALLBACKS_h
#define ANT_BASEANTWITHCALLBACKS_h

#include <BaseClasses/ANT_BaseAnt.h>
#include <RX/ANT_messages.h>
#include <inttypes.h>

/**
 * This class can be used instead of the Ant class and allows
 * user-specified callback functions to be called when responses are
 * received, simplifying the processing code and reducing boilerplate.
 *
 * To use it, first register your callback functions using the onXxx
 * methods. Each method has a uintptr_t data argument, that can be used to
 * pass arbitrary data to the callback (useful when using the same
 * function for multiple callbacks, or have a generic function that can
 * behave differently in different circumstances). Supplying the data
 * parameter is optional, but the callback must always accept it (just
 * ignore it if it's unused). The uintptr_t type is an integer type
 * guaranteed to be big enough to fit a pointer (it is 16-bit on AVR,
 * 32-bit on ARM), so it can also be used to store a pointer to access
 * more data if required (using proper casts).
 *
 * There can be only one callback of each type registered at one time,
 * so registering callback overwrites any previously registered one. To
 * unregister a callback, pass NULL as the function.
 *
 * To ensure that the callbacks are actually called, call the loop()
 * method regularly (in your loop() function, for example). This takes
 * care of calling readPacket() and getResponse() other methods on the
 * Ant class, so there is no need to do so directly (though it should
 * not mess with this class if you do, it would only mean some callbacks
 * aren't called).
 *
 * Inside callbacks, you should generally not be blocking / waiting.
 * Since callbacks can be called from inside waitFor() and friends, a
 * callback that doesn't return quickly can mess up the waitFor()
 * timeout.
 *
 * Sending packets is not a problem inside a callback, but avoid
 * receiving a packet (e.g. calling readPacket(), loop() or waitFor()
 * and friends) inside a callback (since that would overwrite the
 * current response, messing up any pending callbacks and waitFor() etc.
 * methods already running).
 */

template <typename Arg> struct Callback {
    void (*func)(Arg, uintptr_t);
    uintptr_t data;
    void set(void (*func)(Arg, uintptr_t), uintptr_t data) {
        this->func = func;
        this->data = data;
    }
    bool call(Arg arg) {
        if (this->func) {
            this->func(arg, this->data);
            return true;
        }
        return false;
    }
};

class BaseAntWithCallbacks : virtual public BaseAnt {
public:

    /**
     * Register a packet error callback. It is called whenever an
     * error occurs in the packet reading process. Arguments to the
     * callback will be the error code (as returned by
     * XBeeResponse::getErrorCode()) and the data parameter.  while
     * registering the callback.
     */
    void onPacketError(void (*func)(uint8_t, uintptr_t), uintptr_t data = 0) { _onPacketError.set(func, data); }

    /**
     * Register a response received callback. It is called whenever
     * a response was succesfully received, before a response
     * specific callback (or onOtherResponse) below is called.
     *
     * Arguments to the callback will be the received response and
     * the data parameter passed while registering the callback.
     */
    void onResponse(void (*func)(AntResponse&, uintptr_t), uintptr_t data = 0) { _onResponse.set(func, data); }

    /**
     * Register an other response received callback. It is called
     * whenever a response was succesfully received, but no response
     * specific callback was registered using the functions below
     * (after the onResponse callback is called).
     *
     * Arguments to the callback will be the received response and
     * the data parameter passed while registering the callback.
     */
    void onOtherResponse(void (*func)(AntResponse&, uintptr_t), uintptr_t data = 0) { _onOtherResponse.set(func, data); }

    /** These functions register a response specific callback. They
     * are called whenever a response of the appropriate type was
     * succesfully received (after the onResponse callback is
     * called).
     *
     * Arguments to the callback will be the received response
     * (already converted to the appropriate type) and the data
     * parameter passed while registering the callback.
     */
    void onAcknowledgedData(void (*func)(AcknowledgedData&, uintptr_t), uintptr_t data = 0) { _onAcknowledgedData.set(func, data); }
    void onAdvancedBurstData(void (*func)(AdvancedBurstData&, uintptr_t), uintptr_t data = 0) { _onAdvancedBurstData.set(func, data); }
    void onBroadcastData(void (*func)(BroadcastData&, uintptr_t), uintptr_t data = 0) { _onBroadcastData.set(func, data); }
    void onBurstTransferData(void (*func)(BurstTransferData&, uintptr_t), uintptr_t data = 0) { _onBurstTransferData.set(func, data); }
    void onAdvancedBurstCapabilitiesConfiguration(void (*func)(AdvancedBurstCapabilitiesConfiguration&, uintptr_t), uintptr_t data = 0) { _onAdvancedBurstCapabilitiesConfiguration.set(func, data); }
    void onAntVersion(void (*func)(AntVersion&, uintptr_t), uintptr_t data = 0) { _onAntVersion.set(func, data); }
    void onCapabilities(void (*func)(Capabilities&, uintptr_t), uintptr_t data = 0) { _onCapabilities.set(func, data); }
    void onChannelEventResponse(void (*func)(ChannelEventResponse&, uintptr_t), uintptr_t data = 0) { _onChannelEventResponse.set(func, data); }
    void onChannelIdResponse(void (*func)(ChannelIdResponse&, uintptr_t), uintptr_t data = 0) { _onChannelIdResponse.set(func, data); }
    void onChannelStatus(void (*func)(ChannelStatus&, uintptr_t), uintptr_t data = 0) { _onChannelStatus.set(func, data); }
    void onEncryptionModeParameters(void (*func)(EncryptionModeParameters&, uintptr_t), uintptr_t data = 0) { _onEncryptionModeParameters.set(func, data); }
    void onEventFilter(void (*func)(EventFilter&, uintptr_t), uintptr_t data = 0) { _onEventFilter.set(func, data); }
    void onSelectiveDataUpdateMaskSetting(void (*func)(SelectiveDataUpdateMaskSetting&, uintptr_t), uintptr_t data = 0) { _onSelectiveDataUpdateMaskSetting.set(func, data); }
    void onStartUpMessage(void (*func)(StartUpMessage&, uintptr_t), uintptr_t data = 0) { _onStartUpMessage.set(func, data); }

    /**
     * Regularly call this method, which ensures that the serial
     * buffer is processed and the appropriate callbacks are called.
     */
    void loop();

    /**
     * Wait for a API response of the given type, optionally
     * filtered by the given match function.
     *
     * If a match function is given it is called for every response
     * of the right type received, passing the response and the data
     * parameter passed to this method. If the function returns true
     * (or if no function was passed), waiting stops and this method
     * returns 0. If the function returns false, waiting
     * continues. After the given timeout passes, this method
     * returns ANT_WAIT_TIMEOUT.
     *
     * If a valid frameId is passed (e.g. 0-255 inclusive) and a
     * status API response frame is received while waiting, that has
     * a *non-zero* status, waiting stops and that status is
     * received. This is intended for when a TX packet was sent and
     * you are waiting for an RX reply, which will most likely never
     * arrive when TX failed. However, since the status reply is not
     * guaranteed to arrive before the RX reply (a remote module can
     * send a reply before the ACK), first calling waitForStatus()
     * and then waitFor() can sometimes miss the reply RX packet.
     *
     * Note that when the intended response is received *before* the
     * status reply, the latter will not be processed by this
     * method and will be subsequently processed by e.g. loop()
     * normally.
     *
     * While waiting, any other responses received are passed to the
     * relevant callbacks, just as if calling loop() continuously
     * (except for the response sought, that one is only passed to
     * the OnResponse handler and no others).
     *
     * After this method returns, the response itself can still be
     * retrieved using getResponse() as normal.
     */
    template <typename Response>
    uint8_t waitFor(Response& response, uint16_t timeout, bool (*func)(Response&, uintptr_t) = NULL, uintptr_t data = 0) {
        return waitForInternal(Response::MSG_ID, &response, timeout, (void*)func, data);
    }

    /**
     * Sends a AntRequest (TX packet) out the serial port, and wait
     * for a status response API frame (up until the given timeout).
     * Essentially this just calls send() and waitForStatus().
     * See waitForStatus for the meaning of the return value and
     * more details.
     */
    uint8_t sendAndWait(AntRequest &request, uint16_t timeout) {
        send(request);
        return waitForStatus(request.getMsgId(), timeout);
    }

    /**
     * Wait for a API response to respond and
     * return the status from the packet i.e. the ChannelEventResponse
     *
     * While waiting, any other responses received are passed to the
     * relevant callbacks, just as if calling loop() continuously
     * (except for the status response sought, that one is only
     * passed to the OnResponse handler and no others).
     *
     * After this method returns, the response itself can still be
     * retrieved using getResponse() as normal.
     */
    uint8_t waitForStatus(uint8_t msgId, uint16_t timeout);
private:
    /**
     * Internal version of waitFor that does not need to be
     * templated (to prevent duplication the implementation for
     * every response type you might want to wait for). Instead of
     * using templates, this accepts the apiId to wait for and will
     * cast the given response object and the argument to the given
     * function to the corresponding type. This means that the
     * void* given must match the api id!
     */
    uint8_t waitForInternal(uint8_t msgId, void *response, uint16_t timeout, void *func, uintptr_t data);

    /**
     * Helper that checks if the current response is a status
     * response with the given msg id. If so, returns the status
     * byte from the response, otherwise returns 0xff.
     */
    uint8_t matchStatus(uint8_t msgId);

    /**
     * Top half of a typical loop(). Calls readPacket(), calls
     * onPacketError on error, calls onResponse when a response is
     * available. Returns in the true in the latter case, after
     * which a caller should typically call loopBottom().
     */
    bool loopTop();

    /**
     * Bottom half of a typical loop. Call only when a valid
     * response was read, will call all response-specific callbacks.
     */
    void loopBottom();

    Callback<uint8_t> _onPacketError;
    Callback<AntResponse&> _onResponse;
    Callback<AntResponse&> _onOtherResponse;
    Callback<AcknowledgedData&> _onAcknowledgedData;
    Callback<AdvancedBurstData&> _onAdvancedBurstData;
    Callback<BroadcastData&> _onBroadcastData;
    Callback<BurstTransferData&> _onBurstTransferData;
    Callback<AdvancedBurstCapabilitiesConfiguration&> _onAdvancedBurstCapabilitiesConfiguration;
    Callback<AntVersion&> _onAntVersion;
    Callback<Capabilities&> _onCapabilities;
    Callback<ChannelEventResponse&> _onChannelEventResponse;
    Callback<ChannelIdResponse&> _onChannelIdResponse;
    Callback<ChannelStatus&> _onChannelStatus;
    Callback<EncryptionModeParameters&> _onEncryptionModeParameters;
    Callback<EventFilter&> _onEventFilter;
    Callback<SelectiveDataUpdateMaskSetting&> _onSelectiveDataUpdateMaskSetting;
    Callback<StartUpMessage&> _onStartUpMessage;
};

#endif // ANT_BASEANTWITHCALLBACKS_h