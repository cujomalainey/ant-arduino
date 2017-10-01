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

    static const uint8_t MSG_ID = SELECTIVE_DATA_UPDATE_MASK_SETTING;
};

#endif // ANT_SELECTIVEDATAUPDATEMASKSETTING_h