#include <TX/Config/ANT_EnableSingleChannelEncryption.h>

#include <ANT_private_defines.h>

EnableSingleChannelEncryption::EnableSingleChannelEncryption() : AntRequest(ENABLE_SINGLE_CHANNEL_ENCRYPTION) {}

EnableSingleChannelEncryption::EnableSingleChannelEncryption(uint8_t channel) : AntRequest(ENABLE_SINGLE_CHANNEL_ENCRYPTION) {
    setChannel(channel);
}

void EnableSingleChannelEncryption::setChannel(uint8_t channel) {
    _channel = channel;
}

// cppcheck-suppress unusedFunction
void EnableSingleChannelEncryption::setEncryptionMode(uint8_t encryptionMode) {
    _encryptionMode = encryptionMode;
}

// cppcheck-suppress unusedFunction
void EnableSingleChannelEncryption::setVolatileKeyIndex(uint8_t index) {
    _volatileKeyIndex = index;
}

// cppcheck-suppress unusedFunction
void EnableSingleChannelEncryption::setDecimationRate(uint8_t rate) {
    _decimationRate = rate;
}

uint8_t EnableSingleChannelEncryption::getChannel() {
    return _channel;
}

// cppcheck-suppress unusedFunction
uint8_t EnableSingleChannelEncryption::getEncryptionMode() {
    return _encryptionMode;
}

// cppcheck-suppress unusedFunction
uint8_t EnableSingleChannelEncryption::getVolatileKeyIndex() {
    return _volatileKeyIndex;
}

// cppcheck-suppress unusedFunction
uint8_t EnableSingleChannelEncryption::getDecimationRate() {
    return _decimationRate;
}

uint8_t EnableSingleChannelEncryption::getData(uint8_t pos) {
    if (pos == 0) {
        return _channel;
    } else if (pos == 1) {
        return _encryptionMode;
    } else if (pos == 2) {
        return _volatileKeyIndex;
    } else {
        return _decimationRate;
    }
}

uint8_t EnableSingleChannelEncryption::getDataLength() {
    return ENABLE_SINGLE_CHANNEL_ENCRYPTION_LENGTH;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t EnableSingleChannelEncryption::execute() {
    return sd_ant_crypto_channel_enable(_channel, _encryptionMode, _volatileKeyIndex, _decimationRate);
}

#endif // NATIVE_API_AVAILABLE
