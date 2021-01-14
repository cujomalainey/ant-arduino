#include <TX/Test/ANT_CWInit.h>

#include <ANT_private_defines.h>

CWInit::CWInit() : AntRequest(CW_INIT) {}

uint8_t CWInit::getData(uint8_t pos) {
    return 0;
}

uint8_t CWInit::getDataLength() {
    return CW_INIT_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t CWInit::execute() {
    return sd_ant_cw_test_mode_init();
}

#endif // NATIVE_API_AVAILABLE
