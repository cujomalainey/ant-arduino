#ifndef ANT_OPENRXSCANMODE_h
#define ANT_OPENRXSCANMODE_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Open Rx Scan Mode message, it is used to put the ANT radio into open rx scan mode
 */
class OpenRxScanMode : public AntRequest {
public:
    OpenRxScanMode();
    OpenRxScanMode(uint8_t synchronousOnly);
    void setSynchronousChannelPacketsOnly(uint8_t synchronousOnly);
    uint8_t getSynchronousChannelPacketsOnly();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _extendLength = 0;
    uint8_t _synchronousChannelPacketsOnly;
};

#endif // ANT_OPENRXSCANMODE_h