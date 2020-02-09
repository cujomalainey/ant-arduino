#ifndef ANT_CWINIT_h
#define ANT_CWINIT_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a cw init packet
 *
 */
class CWInit : public AntRequest {
public:
    CWInit();
    uint8_t getData(uint8_t pos) override;
    uint8_t getDataLength() override;
#ifdef NATIVE_API_AVAILABLE
    uint32_t execute() override;
#endif // NATIVE_API_AVAILABLE
};

#endif // ANT_CWINIT_h
