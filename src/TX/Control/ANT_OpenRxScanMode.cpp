#include <TX/Control/ANT_OpenRxScanMode.h>

#include <ANT_private_defines.h>


OpenRxScanMode::OpenRxScanMode() : AntRequest(OPEN_RX_SCAN_MODE) {

}

OpenRxScanMode::OpenRxScanMode(bool synchronousOnly) : AntRequest(OPEN_RX_SCAN_MODE) {
    setSynchronousChannelPacketsOnly(synchronousOnly);
}

void OpenRxScanMode::setSynchronousChannelPacketsOnly(bool synchronousOnly) {
    _synchronousChannelPacketsOnly = synchronousOnly;
}

bool OpenRxScanMode::getSynchronousChannelPacketsOnly() {
    return _synchronousChannelPacketsOnly;
}

uint8_t OpenRxScanMode::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t OpenRxScanMode::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t OpenRxScanMode::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE