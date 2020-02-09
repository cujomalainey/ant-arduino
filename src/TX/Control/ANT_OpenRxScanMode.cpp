#include <TX/Control/ANT_OpenRxScanMode.h>

#include <ANT_private_defines.h>


OpenRxScanMode::OpenRxScanMode() : AntRequest(OPEN_RX_SCAN_MODE) {

}

OpenRxScanMode::OpenRxScanMode(uint8_t synchronousOnly) : AntRequest(OPEN_RX_SCAN_MODE) {
    setSynchronousChannelPacketsOnly(synchronousOnly);
}

void OpenRxScanMode::setSynchronousChannelPacketsOnly(uint8_t synchronousOnly) {
    _extendLength = 1;
    _synchronousChannelPacketsOnly = synchronousOnly;
}

uint8_t OpenRxScanMode::getSynchronousChannelPacketsOnly() {
    return _synchronousChannelPacketsOnly;
}

uint8_t OpenRxScanMode::getData(uint8_t pos) {
    if (pos == 0) {
        return 0;
    } else {
        return _synchronousChannelPacketsOnly ? 1 : 0;
    }
}

uint8_t OpenRxScanMode::getDataLength() {
    return OPEN_RX_SCAN_MODE_LENGTH + _extendLength;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t OpenRxScanMode::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
