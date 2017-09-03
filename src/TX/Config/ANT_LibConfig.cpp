#include <TX/Config/ANT_LibConfig.h>

#include <ANT_private_defines.h>

LibConfig::LibConfig() : AntRequest(LIB_CONFIG) {

}

LibConfig::LibConfig(uint8_t config) : AntRequest(LIB_CONFIG) {
    setConfig(config);
}

void LibConfig::setConfig(uint8_t config) {
    _config = config;
}

uint8_t LibConfig::getConfig() {
    return _config;
}

uint8_t LibConfig::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t LibConfig::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t LibConfig::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE