#include <TX/Config/ANT_ConfigureAdvancedBurst.h>

#include <ANT_private_defines.h>

ConfigureAdvancedBurst::ConfigureAdvancedBurst() : AntRequest(CONFIGURE_ADVANCED_BURST) {

}

ConfigureAdvancedBurst::ConfigureAdvancedBurst(uint8_t enable, uint8_t maxPacketLength) : AntRequest(CONFIGURE_ADVANCED_BURST) {
    setEnable(enable);
    setMaxPacketLength(maxPacketLength);
}

void ConfigureAdvancedBurst::setEnable(uint8_t enable) {
    _enable = enable;
}

void ConfigureAdvancedBurst::setMaxPacketLength(uint8_t maxPacketLength) {
    _maxPacketLength = maxPacketLength;
}

// cppcheck-suppress unusedFunction
void ConfigureAdvancedBurst::setRequiredFeatures(uint32_t requiredFeatures) {
    _requiredFeatures = requiredFeatures;
}

// cppcheck-suppress unusedFunction
void ConfigureAdvancedBurst::setOptionalFeatures(uint32_t optionalFeatures) {
    _optionalFeatures = optionalFeatures;
}

// cppcheck-suppress unusedFunction
void ConfigureAdvancedBurst::setStallCount(uint16_t stallCount) {
    // TODO handle extentions
    _stallCount = stallCount;
}

// cppcheck-suppress unusedFunction
void ConfigureAdvancedBurst::setRetryCount(uint8_t retryCount) {
    // TODO handle extentions
    _retryCount = retryCount;
}

// cppcheck-suppress unusedFunction
uint8_t ConfigureAdvancedBurst::getEnable() {
    return _enable;
}

uint8_t ConfigureAdvancedBurst::getMaxPacketLength() {
    return _maxPacketLength;
}

uint32_t ConfigureAdvancedBurst::getRequiredFeatures() {
    return _requiredFeatures;
}

uint32_t ConfigureAdvancedBurst::getOptionalFeatures() {
    return _optionalFeatures;
}

// cppcheck-suppress unusedFunction
uint16_t ConfigureAdvancedBurst::getStallCount() {
    return _stallCount;
}

// cppcheck-suppress unusedFunction
uint8_t ConfigureAdvancedBurst::getRetryCount() {
    return _retryCount;
}

uint8_t ConfigureAdvancedBurst::getData(uint8_t pos) {
    if (pos == 0) {
        return 0;
    } else if (pos == 1) {
        return _enable;
    } else if (pos == 2) {
        return _maxPacketLength;
    } else if (pos == 3) {
        return _requiredFeatures & 0xFF;
    } else if (pos == 4) {
        return (_requiredFeatures >> 8) & 0xFF;
    } else if (pos == 5) {
        return (_requiredFeatures >> 16) & 0xFF;
    } else if (pos == 6) {
        return _optionalFeatures & 0xFF;
    } else if (pos == 7) {
        return (_optionalFeatures >> 8) & 0xFF;
    } else {
        return (_optionalFeatures >> 16) & 0xFF;
    }
}

uint8_t ConfigureAdvancedBurst::getDataLength() {
    return CONFIGURE_ADVANCED_BURST_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t ConfigureAdvancedBurst::execute() {
    // TODO arguments need to be packed into an array
    // return sd_ant_adv_burst_config_set();
    return 0;
}

#endif // NATIVE_API_AVAILABLE
