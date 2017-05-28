#include <RX/Status/ANT_Capabilities.h>

Capabilities::Capabilities() : AntResponse() {

}

uint8_t Capabilities::getMaxChannels() {
    return getFrameData()[0];
}

uint8_t Capabilities::getMaxNetworks() {
    return getFrameData()[1];
}

uint8_t Capabilities::getStandardOptions() {
    return getFrameData()[2];
}

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

uint8_t Capabilities::getMaxSensRcoreChannels() {
    return getFrameData()[5];
}