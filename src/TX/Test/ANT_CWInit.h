#ifndef ANT_CWINIT_h
#define ANT_CWINIT_h

/**
 * Represents a cw init packet
 *
 */
class CWInit : public AntRequest {
public:
    CWInit();
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
};

#endif // ANT_CWINIT_h