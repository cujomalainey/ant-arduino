#ifndef ANT_SETENCRYPTIONINFO_h
#define ANT_SETENCRYPTIONINFO_h

#include <TX/ANT_AntRequest.h>

/**
 * Represents a set encryption info message
 *
 * it is used to configure the ...?
 */
class SetEncryptionInfo : public AntRequest {
public:
    SetEncryptionInfo();
    SetEncryptionInfo(uint8_t param, uint8_t* data);
    void setParameter(uint8_t param);
    void setDataString(uint8_t* data);
    void setDataStringByte(uint8_t byte, uint8_t pos);
    uint8_t getParameter();
    void getDataString(uint8_t* arr);
    uint8_t getDataStringByte(uint8_t pos);
    uint8_t getData(uint8_t pos);
    uint8_t getDataLength();
#ifdef NATIVE_API_AVAILABLE
    uint8_t execute();
#endif // NATIVE_API_AVAILABLE
private:
    uint8_t getDataStringSize();
    uint8_t _setParameter;
    uint8_t _dataString[SET_ENCRYPTION_INFO_DATA_STRING_USER_INFORMATION_STRING_SIZE];
    // USER_INFORMATION_STRING is the largest among the possible configurations, can be used for other modes
};

#endif // ANT_SETENCRYPTIONINFO_h
