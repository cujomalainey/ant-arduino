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

uint32_t SelectiveDataUpdateMaskSetting::backFill(uint8_t subId, ANT_MESSAGE &buf) {
    buf.ANT_MESSAGE_ucMesgID = MSG_ID;
    buf.ANT_MESSAGE_aucMesgData[0] = subId;
    buf.ANT_MESSAGE_ucSize = MESG_ANT_MAX_PAYLOAD_SIZE + MESG_CHANNEL_NUM_SIZE;
    return sd_ant_sdu_mask_get(subId, &buf.ANT_MESSAGE_aucMesgData[1]);
}

#endif // NATIVE_API_AVAILABLE
