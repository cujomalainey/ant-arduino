#ifndef ANT_OPENRXSCANMODE_h
#define ANT_OPENRXSCANMODE_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a Open Rx Scan Mode message, it is used to put the ANT radio into open rx scan mode
 */
class OpenRxScanMode : public AntRequest {
public:
    OpenRxScanMode();
    explicit OpenRxScanMode(uint8_t synchronousOnly);
    void setSynchronousChannelPacketsOnly(uint8_t synchronousOnly);
    uint8_t getSynchronousChannelPacketsOnly();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t _extendLength = 0;
    uint8_t _synchronousChannelPacketsOnly = 0;
};

#endif // ANT_OPENRXSCANMODE_h
