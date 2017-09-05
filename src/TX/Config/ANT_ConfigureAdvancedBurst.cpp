#include <TX/Config/ANT_ConfigureAdvancedBurst.h>

#include <ANT_private_defines.h>

ConfigureAdvancedBurst::ConfigureAdvancedBurst() {

}

ConfigureAdvancedBurst::ConfigureAdvancedBurst(uint8_t enable, uint8_t maxPacketLength) {
    setEnable(enable);
    setMaxPacketLength(maxPacketLength);
}

void ConfigureAdvancedBurst::setEnable(uint8_t enable) {
    _enable = enable;
}

void ConfigureAdvancedBurst::setMaxPacketLength(uint8_t maxPacketLength) {
    _maxPacketLength = maxPacketLength;
}

void ConfigureAdvancedBurst::setRequiredFeatures(uint32_t requiredFeatures) {
    _requiredFeatures = requiredFeatures;
}

void ConfigureAdvancedBurst::setOptionalFeatures(uint32_t optionalFeatures) {
    _optionalFeatures = optionalFeatures;
}

void ConfigureAdvancedBurst::setStallCount(uint16_t stallCount) {
    // TODO handle extentions
    _stallCount = stallCount;
}

void ConfigureAdvancedBurst::setRetryCount(uint8_t retryCount) {
    // TODO handle extentions
    _retryCount = retryCount;
}

uint8_t ConfigureAdvancedBurst::getEnable() {
    return enable;
}

uint8_t ConfigureAdvancedBurst::getMaxPacketLength() {
    return maxPacketLength;
}

uint32_t ConfigureAdvancedBurst::getRequiredFeatures() {
    return _requiredFeatures;
}

uint32_t ConfigureAdvancedBurst::getOptionalFeatures() {
    return _optionalFeatures;
}

uint16_t ConfigureAdvancedBurst::getStallCount() {
    return _stallCount;
}

uint8_t ConfigureAdvancedBurst::getRetryCount() {
    return _retryCount;
}

uint8_t ConfigureAdvancedBurst::getData(uint8_t pos) {
    // TODO
    return 0;
}

uint8_t ConfigureAdvancedBurst::getDataLength() {
    // TODO
    return 0;
}

#ifdef NATIVE_API_AVAILABLE

uint8_t ConfigureAdvancedBurst::execute() {
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE