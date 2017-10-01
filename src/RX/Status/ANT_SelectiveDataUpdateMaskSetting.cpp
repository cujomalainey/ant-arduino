#include <RX/Status/ANT_SelectiveDataUpdateMaskSetting.h>

SelectiveDataUpdateMaskSetting::SelectiveDataUpdateMaskSetting() : AntResponse() {

}

uint8_t SelectiveDataUpdateMaskSetting::getSDUMaskNumber() {
    return getFrameData()[0];
}

uint8_t* SelectiveDataUpdateMaskSetting::getSDUMask() {
    return getFrameData() + 1;
}
