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
    return ( frame[2] ) + ( frame[3] << 8 ) + ( frame[4] << 16 );
}

uint8_t AdvancedBurstCapabilitiesConfiguration::enable() {
    return getFrameData()[1];
}

uint8_t AdvancedBurstCapabilitiesConfiguration::getMaxPacketLength() {
    return getFrameData()[2];
}

uint32_t AdvancedBurstCapabilitiesConfiguration::getRequiredFeatures() {
    uint32_t features = getFrameData()[3];
    features |= getFrameData()[4] << 8;
    features |= getFrameData()[5] << 16;
    return features;
}

uint32_t AdvancedBurstCapabilitiesConfiguration::getOptionalFeatures() {
    uint32_t features = getFrameData()[6];
    features |= getFrameData()[7] << 8;
    features |= getFrameData()[8] << 16;
    return features;
}
