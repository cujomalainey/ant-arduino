#include <TX/Config/ANT_LibConfig.h>

#include <ANT_private_defines.h>

LibConfig::LibConfig() : AntRequest(LIB_CONFIG) {}

LibConfig::LibConfig(uint8_t config) : AntRequest(LIB_CONFIG) {
    setConfig(config);
}

void LibConfig::setConfig(uint8_t config) {
    _config = config;
}

// cppcheck-suppress unusedFunction
uint8_t LibConfig::getConfig() {
    return _config;
}

uint8_t LibConfig::getData(uint8_t pos) {
    if (pos == 0) {
        return 0;
    } else {
        return _config;
    }
}

uint8_t LibConfig::getDataLength() {
    return LIB_CONFIG_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t LibConfig::execute() {
    sd_ant_lib_config_clear(ANT_LIB_CONFIG_MASK_ALL);
    return sd_ant_lib_config_set(_config | ANT_LIB_CONFIG_RADIO_CONFIG_ALWAYS);
}

#endif // NATIVE_API_AVAILABLE
