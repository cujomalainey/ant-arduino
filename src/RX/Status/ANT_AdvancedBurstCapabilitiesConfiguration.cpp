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