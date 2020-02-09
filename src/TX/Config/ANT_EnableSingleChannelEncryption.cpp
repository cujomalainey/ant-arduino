#include <TX/Config/ANT_EnableSingleChannelEncryption.h>

#include <ANT_private_defines.h>

EnableSingleChannelEncryption::EnableSingleChannelEncryption() : AntRequest(ENABLE_SINGLE_CHANNEL_ENCRYPTION) {

}

EnableSingleChannelEncryption::EnableSingleChannelEncryption(uint8_t channel) : AntRequest(ENABLE_SINGLE_CHANNEL_ENCRYPTION) {
    setChannel(channel);
}

void EnableSingleChannelEncryption::setChannel(uint8_t channel) {
    _channel = channel;
}

void EnableSingleChannelEncryption::setEncryptionMode(uint8_t encryptionMode) {
    _encryptionMode = encryptionMode;
}

void EnableSingleChannelEncryption::setVolatileKeyIndex(uint8_t index) {
    _volatileKeyIndex = index;
}

void EnableSingleChannelEncryption::setDecimationRate(uint8_t rate) {
    _decimationRate = rate;
}

uint8_t EnableSingleChannelEncryption::getChannel() {
    return _channel;
}

uint8_t EnableSingleChannelEncryption::getEncryptionMode() {
    return _encryptionMode;
}

uint8_t EnableSingleChannelEncryption::getVolatileKeyIndex() {
    return _volatileKeyIndex;
}

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
    // TODO
    return 0;
}

#endif // NATIVE_API_AVAILABLE
