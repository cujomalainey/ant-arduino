#include <RX/Status/ANT_AdvancedBurstCapabilitiesConfiguration.h>

AdvancedBurstCapabilitiesConfiguration::AdvancedBurstCapabilitiesConfiguration() : AntResponse () {

}

// cppcheck-suppress unusedFunction
uint8_t AdvancedBurstCapabilitiesConfiguration::getMsgType() {
    return getFrameData()[0];
}

// cppcheck-suppress unusedFunction
uint8_t AdvancedBurstCapabilitiesConfiguration::getSupportedMaxPacketLength() {
    return getFrameData()[1];
}

// cppcheck-suppress unusedFunction
uint32_t AdvancedBurstCapabilitiesConfiguration::getSupportedFeatures() {
    uint8_t* frame = getFrameData();
    return ( frame[2] ) + ( frame[3] << BITS_IN_BYTE ) + ( frame[4] << BITS_IN_SHORT );
}

uint8_t AdvancedBurstCapabilitiesConfiguration::enable() {
    return getFrameData()[1];
}

// cppcheck-suppress unusedFunction
uint8_t AdvancedBurstCapabilitiesConfiguration::getMaxPacketLength() {
    return getFrameData()[2];
}

// cppcheck-suppress unusedFunction
uint32_t AdvancedBurstCapabilitiesConfiguration::getRequiredFeatures() {
    uint32_t features = getFrameData()[3];
    features |= getFrameData()[4] << BITS_IN_BYTE;
    features |= getFrameData()[5] << BITS_IN_SHORT;
    return features;
}

// cppcheck-suppress unusedFunction
uint32_t AdvancedBurstCapabilitiesConfiguration::getOptionalFeatures() {
    uint32_t features = getFrameData()[6];
    features |= getFrameData()[7] << BITS_IN_BYTE;
    features |= getFrameData()[8] << BITS_IN_SHORT;
    return features;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t AdvancedBurstCapabilitiesConfiguration::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_ucSize = subId ? MESG_CONFIG_ADV_BURST_REQ_CONFIG_SIZE : MESG_CONFIG_ADV_BURST_REQ_CAPABILITIES_SIZE;
    // TODO verify sizes might need to be increased by 1
    buf.ANT_MESSAGE_aucMesgData[0] = subId;
    return sd_ant_adv_burst_config_get(subId, &buf.ANT_MESSAGE_aucMesgData[1]);
}

#endif // NATIVE_API_AVAILABLE
