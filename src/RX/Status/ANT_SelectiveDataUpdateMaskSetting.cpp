#include <RX/Status/ANT_SelectiveDataUpdateMaskSetting.h>

SelectiveDataUpdateMaskSetting::SelectiveDataUpdateMaskSetting() : AntResponse() {

}

uint8_t SelectiveDataUpdateMaskSetting::getSDUMaskNumber() {
    return getFrameData()[0];
}

uint8_t* SelectiveDataUpdateMaskSetting::getSDUMask() {
    return getFrameData() + 1;
}

#ifdef NATIVE_API_AVAILABLE

uint32_t SelectiveDataUpdateMaskSetting::backFill(uint8_t subId, uint8_t *buf) {
    buf[0] = subId;
    return sd_ant_sdu_mask_get(subId, &buf[1]);
}

#endif // NATIVE_API_AVAILABLE
