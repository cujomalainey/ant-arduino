#ifndef ANT_SELECTIVEDATAUPDATEMASKSETTING_h
#define ANT_SELECTIVEDATAUPDATEMASKSETTING_h

#include <RX/ANT_AntResponse.h>

#include <ANT_defines.h>

class SelectiveDataUpdateMaskSetting : public AntResponse {
public:
    SelectiveDataUpdateMaskSetting();

    uint8_t getSDUMaskNumber();
    /**
     * An array of length 8
     */
    uint8_t* getSDUMask();

#ifdef NATIVE_API_AVAILABLE

    static uint32_t backFill(uint8_t subId, uint8_t *buf);

#endif // NATIVE_API_AVAILABLE

    static const uint8_t MSG_ID = SELECTIVE_DATA_UPDATE_MASK_SETTING;
};

#endif // ANT_SELECTIVEDATAUPDATEMASKSETTING_h
