#include <RX/Status/ANT_AdvancedBurstCapabilitiesConfiguration.h>

AdvancedBurstCapabilitiesConfiguration::AdvancedBurstCapabilitiesConfiguration() : AntResponse () {

}

uint8_t AdvancedBurstCapabilitiesConfiguration::getMsgType() {
    return getFrameData()[0];
}

uint8_t AdvancedBurstCapabilitiesConfiguration::getSupportedMaxPacketLength() {
    return getFrameData()[1];
}

uint32_t AdvancedBurstCapabilitiesConfiguration::getSupportedFeatures() {
    uint8_t* frame = getFrameData();
    return ( frame[2] ) + ( frame[3] << BITS_IN_BYTE ) + ( frame[4] << BITS_IN_SHORT );
}

uint8_t AdvancedBurstCapabilitiesConfiguration::enable() {
    return getFrameData()[1];
}

uint8_t AdvancedBurstCapabilitiesConfiguration::getMaxPacketLength() {
    return getFrameData()[2];
}

uint32_t AdvancedBurstCapabilitiesConfiguration::getRequiredFeatures() {
    uint32_t features = getFrameData()[3];
    features |= getFrameData()[4] << BITS_IN_BYTE;
    features |= getFrameData()[5] << BITS_IN_SHORT;
    return features;
}

uint32_t AdvancedBurstCapabilitiesConfiguration::getOptionalFeatures() {
    uint32_t features = getFrameData()[6];
    features |= getFrameData()[7] << BITS_IN_BYTE;
    features |= getFrameData()[8] << BITS_IN_SHORT;
    return features;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t AdvancedBurstCapabilitiesConfiguration::backFill(uint8_t subId, uint8_t *buf) {
    return sd_ant_adv_burst_config_get(subId, buf);
}

#endif // NATIVE_API_AVAILABLE
