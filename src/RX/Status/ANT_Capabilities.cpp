#include <RX/Status/ANT_Capabilities.h>

Capabilities::Capabilities() : AntResponse() {}

// cppcheck-suppress unusedFunction
uint8_t Capabilities::getMaxChannels() {
    return getFrameData()[0];
}

// cppcheck-suppress unusedFunction
uint8_t Capabilities::getMaxNetworks() {
    return getFrameData()[1];
}

// cppcheck-suppress unusedFunction
uint8_t Capabilities::getStandardOptions() {
    return getFrameData()[2];
}

// cppcheck-suppress unusedFunction
uint8_t Capabilities::getAdvancedOptions(uint8_t pos) {
    if ( pos == 0 )
    {
        return getFrameData()[3];
    }
    else if ( pos == 1 )
    {
        return getFrameData()[4];
    }
    else if ( pos == 2 )
    {
        return getFrameData()[6];
    }
    else
    {
        return getFrameData()[7];
    }
}

// cppcheck-suppress unusedFunction
uint8_t Capabilities::getMaxSensRcoreChannels() {
    return getFrameData()[5];
}

#ifdef NATIVE_API_AVAILABLE

uint32_t Capabilities::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_ucSize = MESG_CAPABILITIES_SIZE;
    return sd_ant_capabilities_get(buf.ANT_MESSAGE_aucMesgData);
}

#endif // NATIVE_API_AVAILABLE
